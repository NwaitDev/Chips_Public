#!/usr/bin/env python3
import sys
import os
import math
import random
import tkinter as tk
from tkinter import ttk, filedialog, messagebox
import xml.etree.ElementTree as ET

XSI_TYPE = "{http://www.w3.org/2001/XMLSchema-instance}type"
XMI_ID = "{http://www.omg.org/XMI}id"
DECLARATIONS = {"logical_declaration": "logical", "physical_declaration": "physical", "object_declaration": "object"}
OPERATORS = {"plus": "+", "minus": "-", "mult": "*", "div": "/", "mod": "%"}

BG = "#f4f5f7"
FILL = {"logical": "#dbe9ff", "physical": "#ffe8cc", "object": "#d9f2d9"}
OUTLINE = {"logical": "#2f5d9e", "physical": "#b26a00", "object": "#2e7d32"}
EDGE_STYLE = {
    "link": {"fill": "#555555", "dash": (6, 4)},
    "io": {"fill": "#d62728", "dash": ()},
    "sa": {"fill": "#000000", "dash": ()},
    "chan": {"fill": "#1f77b4", "dash": (2, 3)},
}


def local_type(el):
    t = el.get(XSI_TYPE)
    return t.split(":")[-1] if t else el.tag


class Block:
    def __init__(self, key, name, kind, defname, dims):
        self.key = key
        self.name = name
        self.kind = kind
        self.defname = defname
        self.dims = dims

    @property
    def title(self):
        return self.name + "".join(f"[{d}]" for d in self.dims)

    def size(self):
        w = max(len(self.title), len(self.defname)) * 7.5 + 26
        if self.kind == "object":
            r = max(34.0, w / 2)
            return r, r
        return max(55.0, w / 2), 27.0


class Edge:
    def __init__(self, src, dst, kind, slabel, tlabel):
        self.src = src
        self.dst = dst
        self.kind = kind
        self.slabel = slabel
        self.tlabel = tlabel


class ChipsModel:
    def __init__(self, path):
        self.path = path
        self.root = ET.parse(path).getroot()
        self.ids = {}
        self.parent = {}
        for el in self.root.iter():
            i = el.get(XMI_ID)
            if i is not None:
                self.ids[i] = el
            for c in el:
                self.parent[c] = el
        self.blocks = []
        self.block_of = {}
        self.alias = {}
        self.edges = []
        self._seen = set()
        system = self.root.find("system")
        if system is None:
            return
        decls = [el for el in system.iter() if local_type(el) in DECLARATIONS]
        for d in decls:
            if d.tag != "iterator":
                self._declare(d)
        for d in decls:
            if d.tag == "iterator":
                self._alias(d)
        for st in system.iter():
            t = local_type(st)
            if t == "link":
                self._link(st)
            elif t == "channel_plugging":
                self._plugging(st)
            elif t.startswith("feeding_"):
                self._feeding(st, "sa" if t.startswith("feeding_physical") else "io")

    def resolve(self, ref):
        if not ref:
            return None
        ref = ref.split()[0]
        if "#" in ref:
            ref = ref.split("#", 1)[1]
        if ref in self.ids:
            return self.ids[ref]
        if ref.startswith("//"):
            cur = self.root
            for seg in ref[2:].split("/"):
                if not seg.startswith("@"):
                    return None
                name, _, idx = seg[1:].partition(".")
                kids = [c for c in cur if c.tag == name]
                i = int(idx) if idx else 0
                if i >= len(kids):
                    return None
                cur = kids[i]
            return cur
        return None

    def _name(self, el, default="?"):
        if el is None:
            return default
        return el.get("name") or el.get("identifier") or default

    def _expr(self, el):
        if el is None:
            return "?"
        t = local_type(el)
        if t.startswith("direct_"):
            return el.get("value", "?")
        if t.endswith("variable_expression") or t.startswith("contextual_"):
            v = self.resolve(el.get("variable"))
            if v in self.alias:
                return self.alias[v][1]
            return self._name(v)
        if t in OPERATORS:
            return f"{self._expr(el.find('left_operand'))}{OPERATORS[t]}{self._expr(el.find('right_operand'))}"
        if t == "function":
            args = ",".join(self._expr(p) for p in el.findall("parameters"))
            return f"{el.get('name', 'f')}({args})"
        if t.startswith("cast_as"):
            return self._expr(el.find("numeric"))
        return "…"

    def _declare(self, decl):
        var = decl.find("variable")
        if var is None:
            return
        definition = self.resolve(decl.get("def"))
        dims = [self._expr(d) for d in var.findall("dimensions")]
        b = Block(len(self.blocks), self._name(var), DECLARATIONS[local_type(decl)], self._name(definition, ""), dims)
        self.blocks.append(b)
        self.block_of[var] = b
        self.block_of[decl] = b

    def _alias(self, decl):
        var = decl.find("variable")
        fe = self.parent.get(decl)
        if var is None or fe is None:
            return
        b, label = self._target(fe.find("iterable_expr"))
        if b is None:
            return
        name = self._name(var)
        self.alias[var] = (b, f"{label}[{name}]")
        self.alias[decl] = self.alias[var]

    def _target(self, expr):
        if expr is None:
            return None, ""
        tgt = self.resolve(expr.get("variable"))
        if tgt is None:
            return None, ""
        idx = "".join(f"[{self._expr(i)}]" for i in expr.findall("index"))
        if tgt in self.block_of:
            b = self.block_of[tgt]
            return b, b.name + idx
        if tgt in self.alias:
            b, label = self.alias[tgt]
            return b, label + idx
        return None, ""

    def _add(self, src, dst, kind, slabel, tlabel):
        if src is None or dst is None:
            return
        key = (src.key, dst.key, kind, slabel, tlabel)
        if key in self._seen:
            return
        self._seen.add(key)
        self.edges.append(Edge(src, dst, kind, slabel, tlabel))

    def _link(self, st):
        src, sl = self._target(st.find("linked_component"))
        dst, tl = self._target(st.find("support_node"))
        self._add(src, dst, "link", f"{sl}  (linked)", f"{tl}  (support)")

    def _plugging(self, st):
        eater = st.find("eater")
        feeder = st.find("feeder")
        if eater is None or feeder is None:
            return
        src, sl = self._target(feeder.find("node"))
        dst, dl = self._target(eater.find("node"))
        self._add(src, dst, "chan", f"{sl}.{self._channel(feeder.get('feeding_channel'))}",
                  f"{dl}.{self._channel(eater.get('eating_channel'))}")

    def _channel(self, ref):
        ch = self.resolve(ref)
        if ch is None:
            return "?"
        t = ch.get("type_identifier")
        return f"{self._name(ch)} ({t})" if t else self._name(ch)

    def _feeding(self, st, kind):
        eater = st.find("eater")
        feeder = st.find("feeder")
        if eater is None or feeder is None:
            return
        dst, dl = self._target(eater.find("variable_expression"))
        pname = self._name(self.resolve(eater.get("parameter")))
        casts = []
        self._collect_feeders(feeder, casts, dst, f"{dl}.{pname}", kind)

    def _collect_feeders(self, el, casts, dst, tlabel, kind):
        t = local_type(el)
        if t.endswith("_collective_cast"):
            casts = casts + [self._name(self.resolve(el.get("collective_function")))]
        if t.endswith("_logical_output") or t.endswith("_physical_output"):
            src, sl = self._target(el.find("variable_expression"))
            oname = self._name(self.resolve(el.get("output")))
            via = "".join(f"  ⟶ ({c})" for c in reversed(casts))
            self._add(src, dst, kind, f"{sl}.{oname}{via}", tlabel)
            return
        for c in el:
            self._collect_feeders(c, casts, dst, tlabel, kind)


def compute_layout(blocks, edges, seed=7):
    n = len(blocks)
    if n == 0:
        return {}
    rnd = random.Random(seed)
    side = 260 * math.sqrt(n)
    order = {"logical": 0.2, "physical": 0.5, "object": 0.8}
    pos = {b.key: [side * order[b.kind] + rnd.uniform(-side / 6, side / 6), rnd.uniform(0, side)] for b in blocks}
    k = side / math.sqrt(n) * 0.9
    pairs = {(e.src.key, e.dst.key) for e in edges if e.src is not e.dst}
    keys = list(pos)
    temp = side / 8
    for _ in range(450):
        disp = {i: [0.0, 0.0] for i in keys}
        for a in range(n):
            pa = pos[keys[a]]
            for b in range(a + 1, n):
                pb = pos[keys[b]]
                dx, dy = pa[0] - pb[0], pa[1] - pb[1]
                d = math.hypot(dx, dy) or 0.01
                f = k * k / d
                disp[keys[a]][0] += dx / d * f
                disp[keys[a]][1] += dy / d * f
                disp[keys[b]][0] -= dx / d * f
                disp[keys[b]][1] -= dy / d * f
        for u, v in pairs:
            dx, dy = pos[u][0] - pos[v][0], pos[u][1] - pos[v][1]
            d = math.hypot(dx, dy) or 0.01
            f = d * d / k
            disp[u][0] -= dx / d * f
            disp[u][1] -= dy / d * f
            disp[v][0] += dx / d * f
            disp[v][1] += dy / d * f
        for i in keys:
            disp[i][0] -= (pos[i][0] - side / 2) * 0.02
            disp[i][1] -= (pos[i][1] - side / 2) * 0.02
            dx, dy = disp[i]
            d = math.hypot(dx, dy) or 0.01
            step = min(d, temp)
            pos[i][0] += dx / d * step
            pos[i][1] += dy / d * step
        temp = max(temp * 0.985, 1.0)
    by_key = {b.key: b for b in blocks}
    for _ in range(60):
        moved = False
        for a in range(n):
            for b in range(a + 1, n):
                ka, kb = keys[a], keys[b]
                wa, ha = by_key[ka].size()
                wb, hb = by_key[kb].size()
                dx = pos[kb][0] - pos[ka][0]
                dy = pos[kb][1] - pos[ka][1]
                ox = wa + wb + 30 - abs(dx)
                oy = ha + hb + 40 - abs(dy)
                if ox > 0 and oy > 0:
                    moved = True
                    if ox < oy:
                        s = (1 if dx >= 0 else -1) * ox / 2
                        pos[ka][0] -= s
                        pos[kb][0] += s
                    else:
                        s = (1 if dy >= 0 else -1) * oy / 2
                        pos[ka][1] -= s
                        pos[kb][1] += s
        if not moved:
            break
    return pos


class Switch(tk.Frame):
    def __init__(self, master, text, command, value=True):
        super().__init__(master, bg=master["bg"])
        self.value = value
        self.command = command
        self.cv = tk.Canvas(self, width=46, height=24, bg=master["bg"], highlightthickness=0, cursor="hand2")
        self.cv.pack(side="left")
        lbl = tk.Label(self, text=text, bg=master["bg"], cursor="hand2", font=("Helvetica", 10))
        lbl.pack(side="left", padx=(2, 0))
        for w in (self.cv, lbl):
            w.bind("<Button-1>", self.toggle)
        self.draw()

    def draw(self):
        c = self.cv
        c.delete("all")
        c.create_line(12, 12, 34, 12, width=20, capstyle="round", fill="#2e7d32" if self.value else "#b5b5b5")
        x = 34 if self.value else 12
        c.create_oval(x - 8, 4, x + 8, 20, fill="white", outline="")

    def toggle(self, _=None):
        self.value = not self.value
        self.draw()
        self.command(self.value)


class App:
    def __init__(self, root, path=None):
        self.root = root
        root.title("Chips Graph Viewer")
        root.geometry("1250x820")
        root.configure(bg=BG)
        self.model = None
        self.pos = {}
        self.scale = 1.0
        self.ox = 0.0
        self.oy = 0.0
        self.show_nodes = True
        self.show_funcs = True
        self.drag_node = None
        self.last = None
        self.hover = None
        self.label_pos = {}

        bar = tk.Frame(root, bg=BG, padx=8, pady=6)
        bar.pack(fill="x")
        ttk.Button(bar, text="Open…", command=self.open).pack(side="left")
        ttk.Button(bar, text="Re-layout", command=self.relayout).pack(side="left", padx=4)
        ttk.Button(bar, text="Fit", command=self.fit).pack(side="left")
        Switch(bar, "Nodes (objects, physicals)", self.set_nodes, True).pack(side="left", padx=(22, 10))
        Switch(bar, "Functions (logicals, physicals)", self.set_funcs, True).pack(side="left", padx=10)

        bottom = tk.Frame(root, bg=BG, padx=8, pady=2)
        bottom.pack(side="bottom", fill="x")
        self.status = tk.Label(bottom, anchor="w", bg=BG, font=("Helvetica", 9))
        self.status.pack(side="left", fill="x", expand=True)
        self.draw_legend(bottom)
        self.canvas = tk.Canvas(root, bg="white", highlightthickness=0)
        self.canvas.pack(fill="both", expand=True)

        c = self.canvas
        c.bind("<ButtonPress-1>", self.on_press)
        c.bind("<B1-Motion>", self.on_drag)
        c.bind("<ButtonRelease-1>", self.on_release)
        c.bind("<Motion>", self.on_motion)
        c.bind("<MouseWheel>", lambda e: self.zoom(e, 1.1 if e.delta > 0 else 1 / 1.1))
        c.bind("<Button-4>", lambda e: self.zoom(e, 1.1))
        c.bind("<Button-5>", lambda e: self.zoom(e, 1 / 1.1))
        c.bind("<Configure>", lambda e: self.redraw())

        if path:
            root.after(80, lambda: self.load(path))
        else:
            self.redraw()

    def draw_legend(self, bar):
        lg = tk.Canvas(bar, width=690, height=30, bg=BG, highlightthickness=0)
        lg.pack(side="right")
        f = ("Helvetica", 9)
        lg.create_rectangle(4, 8, 26, 22, fill=FILL["logical"], outline=OUTLINE["logical"])
        lg.create_text(30, 15, text="logical", anchor="w", font=f)
        self.rounded(lg, 80, 8, 102, 22, 6, fill=FILL["physical"], outline=OUTLINE["physical"])
        lg.create_text(106, 15, text="physical", anchor="w", font=f)
        lg.create_oval(162, 7, 178, 23, fill=FILL["object"], outline=OUTLINE["object"])
        lg.create_text(182, 15, text="object", anchor="w", font=f)
        x = 236
        for kind, text in (("link", "link"), ("io", "input/output"), ("sa", "actuator/sensor"), ("chan", "channel")):
            st = EDGE_STYLE[kind]
            lg.create_line(x, 15, x + 30, 15, fill=st["fill"], dash=st["dash"], width=2, arrow="last")
            lg.create_text(x + 34, 15, text=text, anchor="w", font=f)
            x += 34 + len(text) * 6.5 + 18

    @staticmethod
    def rounded(c, x1, y1, x2, y2, r, **kw):
        r = min(r, (x2 - x1) / 2, (y2 - y1) / 2)
        pts = [x1 + r, y1, x1 + r, y1, x2 - r, y1, x2 - r, y1, x2, y1, x2, y1 + r, x2, y1 + r,
               x2, y2 - r, x2, y2 - r, x2, y2, x2 - r, y2, x2 - r, y2, x1 + r, y2, x1 + r, y2,
               x1, y2, x1, y2 - r, x1, y2 - r, x1, y1 + r, x1, y1 + r, x1, y1]
        return c.create_polygon(pts, smooth=True, **kw)

    def open(self):
        p = filedialog.askopenfilename(title="Open chips.xmi", filetypes=[("XMI", "*.xmi"), ("All files", "*")])
        if p:
            self.load(p)

    def load(self, path):
        try:
            self.model = ChipsModel(path)
        except Exception as ex:
            messagebox.showerror("Chips Graph Viewer", f"Cannot load {path}:\n{ex}")
            return
        self.pos = compute_layout(self.model.blocks, self.model.edges)
        self.root.title(f"Chips Graph Viewer — {os.path.basename(path)}")
        self.fit()

    def relayout(self):
        if self.model:
            vis = self.visible_blocks()
            keys = {b.key for b in vis}
            eds = [e for e in self.model.edges if e.src.key in keys and e.dst.key in keys]
            self.pos.update(compute_layout(vis, eds, seed=random.randint(0, 10 ** 6)))
            self.fit()

    def set_nodes(self, v):
        self.show_nodes = v
        self.redraw()

    def set_funcs(self, v):
        self.show_funcs = v
        self.redraw()

    def is_visible(self, b):
        if b.kind == "object":
            return self.show_nodes
        if b.kind == "logical":
            return self.show_funcs
        return self.show_nodes or self.show_funcs

    def visible_blocks(self):
        return [b for b in self.model.blocks if self.is_visible(b)] if self.model else []

    def visible_edges(self):
        if not self.model:
            return []
        return [e for e in self.model.edges if self.is_visible(e.src) and self.is_visible(e.dst)
                and (e.kind != "chan" or self.show_nodes)]

    def w2s(self, p):
        return p[0] * self.scale + self.ox, p[1] * self.scale + self.oy

    def fit(self):
        vis = self.visible_blocks()
        if not vis:
            self.redraw()
            return
        self.root.update_idletasks()
        W = max(self.canvas.winfo_width(), 200)
        H = max(self.canvas.winfo_height(), 200)
        xs, ys = [], []
        for b in vis:
            x, y = self.pos[b.key]
            hw, hh = b.size()
            xs += [x - hw, x + hw]
            ys += [y - hh - 70, y + hh]
        w = max(xs) - min(xs) or 1
        h = max(ys) - min(ys) or 1
        self.scale = min((W - 80) / w, (H - 80) / h, 1.6)
        self.ox = W / 2 - self.scale * (min(xs) + max(xs)) / 2
        self.oy = H / 2 - self.scale * (min(ys) + max(ys)) / 2
        self.redraw()

    def boundary(self, b, center, toward):
        dx, dy = toward[0] - center[0], toward[1] - center[1]
        if abs(dx) < 1e-9 and abs(dy) < 1e-9:
            return center
        hw, hh = b.size()
        hw *= self.scale
        hh *= self.scale
        if b.kind == "object":
            d = math.hypot(dx, dy)
            return center[0] + hw * dx / d, center[1] + hw * dy / d
        t = min(hw / abs(dx) if dx else float("inf"), hh / abs(dy) if dy else float("inf"))
        return center[0] + t * dx, center[1] + t * dy

    @staticmethod
    def bezier(p0, p1, p2, t):
        a, b, c = (1 - t) ** 2, 2 * (1 - t) * t, t * t
        return a * p0[0] + b * p1[0] + c * p2[0], a * p0[1] + b * p1[1] + c * p2[1]

    def redraw(self):
        c = self.canvas
        c.delete("all")
        self.hover = None
        self.label_pos = {}
        if not self.model:
            c.create_text(c.winfo_width() / 2, c.winfo_height() / 2, fill="#888",
                          text="Open a chips.xmi file (Open… or pass it as argument)", font=("Helvetica", 13))
            self.status.config(text="")
            return
        blocks = self.visible_blocks()
        edges = self.visible_edges()
        groups = {}
        for i, e in enumerate(edges):
            groups.setdefault(tuple(sorted((e.src.key, e.dst.key))), []).append(i)
        s = self.scale
        width = max(1.2, 1.8 * min(s, 1.5))
        ashape = (10 * min(s, 1.5) + 2, 12 * min(s, 1.5) + 2, 4 * min(s, 1.5) + 1)
        for key, idxs in groups.items():
            n = len(idxs)
            for k, i in enumerate(idxs):
                e = edges[i]
                st = EDGE_STYLE[e.kind]
                tags = ("edge", f"e:{i}")
                pa = self.w2s(self.pos[e.src.key])
                if e.src is e.dst:
                    hw, hh = e.src.size()
                    y0 = pa[1] - hh * s
                    h = (45 + 22 * k) * s
                    w = (20 + 9 * k) * s
                    pts = [pa[0] - w * 0.6, y0, pa[0] - w * 1.5, y0 - h, pa[0] + w * 1.5, y0 - h, pa[0] + w * 0.6, y0]
                    c.create_line(*pts, smooth=True, arrow="last", arrowshape=ashape, fill=st["fill"],
                                  dash=st["dash"], width=width, tags=tags)
                    self.label_pos[i] = ((pa[0] - w * 1.6, y0 - h * 0.75, "e"), (pa[0] + w * 1.6, y0 - h * 0.75, "w"))
                    continue
                pb = self.w2s(self.pos[e.dst.key])
                lo, hi = (pa, pb) if e.src.key < e.dst.key else (pb, pa)
                dx, dy = hi[0] - lo[0], hi[1] - lo[1]
                L = math.hypot(dx, dy) or 1
                nx, ny = -dy / L, dx / L
                off = (k - (n - 1) / 2) * 34 * min(s, 1.5) * 2
                mid = ((pa[0] + pb[0]) / 2 + nx * off, (pa[1] + pb[1]) / 2 + ny * off)
                p0 = self.boundary(e.src, pa, mid)
                p2 = self.boundary(e.dst, pb, mid)
                c.create_line(*p0, *mid, *p2, smooth=True, arrow="last", arrowshape=ashape, fill=st["fill"],
                              dash=st["dash"], width=width, tags=tags)
                sp = self.bezier(p0, mid, p2, 0.16)
                tp = self.bezier(p0, mid, p2, 0.84)
                self.label_pos[i] = ((sp[0], sp[1] - 14, "center"), (tp[0], tp[1] - 14, "center"))
        fs = max(6, int(10 * min(s, 1.6)))
        for b in blocks:
            x, y = self.w2s(self.pos[b.key])
            hw, hh = b.size()
            hw *= s
            hh *= s
            tags = ("node", f"n:{b.key}")
            kw = dict(fill=FILL[b.kind], outline=OUTLINE[b.kind], width=1.6, tags=tags)
            if b.kind == "logical":
                c.create_rectangle(x - hw, y - hh, x + hw, y + hh, **kw)
            elif b.kind == "physical":
                self.rounded(c, x - hw, y - hh, x + hw, y + hh, 14 * s, **kw)
            else:
                c.create_oval(x - hw, y - hh, x + hw, y + hh, **kw)
            dy = 7 * min(s, 1.6) if b.defname else 0
            c.create_text(x, y - dy, text=b.title, font=("Helvetica", fs, "bold"), tags=tags)
            if b.defname:
                c.create_text(x, y + dy + 1, text=b.defname, font=("Helvetica", max(6, fs - 1), "italic"),
                              fill="#444", tags=tags)
        m = self.model
        self.status.config(text=f"{os.path.basename(m.path)} — {len(blocks)}/{len(m.blocks)} blocks, "
                                f"{len(edges)}/{len(m.edges)} relations shown  |  drag: move node / pan, wheel: zoom")
        self._edges = edges

    def item_tag(self, x, y, prefix, halo=0):
        for it in reversed(self.canvas.find_overlapping(x - halo, y - halo, x + halo, y + halo)):
            for t in self.canvas.gettags(it):
                if t.startswith(prefix):
                    return int(t[len(prefix):])
        return None

    def on_press(self, ev):
        self.drag_node = self.item_tag(ev.x, ev.y, "n:")
        self.last = (ev.x, ev.y)

    def on_drag(self, ev):
        if not self.last:
            return
        dx, dy = ev.x - self.last[0], ev.y - self.last[1]
        self.last = (ev.x, ev.y)
        if self.drag_node is not None:
            p = self.pos[self.drag_node]
            p[0] += dx / self.scale
            p[1] += dy / self.scale
        else:
            self.ox += dx
            self.oy += dy
        self.redraw()

    def on_release(self, _):
        self.drag_node = None
        self.last = None

    def zoom(self, ev, f):
        wx = (ev.x - self.ox) / self.scale
        wy = (ev.y - self.oy) / self.scale
        self.scale = max(0.08, min(6.0, self.scale * f))
        self.ox = ev.x - wx * self.scale
        self.oy = ev.y - wy * self.scale
        self.redraw()

    def on_motion(self, ev):
        if not self.model or self.last:
            return
        i = None
        if self.item_tag(ev.x, ev.y, "n:") is None:
            i = self.item_tag(ev.x, ev.y, "e:", halo=4)
        if i == self.hover:
            return
        c = self.canvas
        c.delete("hover")
        if self.hover is not None:
            c.itemconfig(f"e:{self.hover}", width=max(1.2, 1.8 * min(self.scale, 1.5)))
        self.hover = i
        if i is None:
            c.config(cursor="")
            return
        c.config(cursor="hand2")
        e = self._edges[i]
        c.itemconfig(f"e:{i}", width=max(3.0, 4 * min(self.scale, 1.5)))
        color = EDGE_STYLE[e.kind]["fill"]
        (sx, sy, sa), (tx, ty, ta) = self.label_pos[i]
        self.badge(sx, sy, sa, "source: " + e.slabel, color)
        self.badge(tx, ty, ta, "target: " + e.tlabel, color)

    def badge(self, x, y, anchor, text, color):
        c = self.canvas
        t = c.create_text(x, y, text=text, anchor=anchor, font=("Helvetica", 10, "bold"), fill=color, tags="hover")
        x1, y1, x2, y2 = c.bbox(t)
        r = c.create_rectangle(x1 - 5, y1 - 3, x2 + 5, y2 + 3, fill="#fffbe6", outline=color, tags="hover")
        c.tag_lower(r, t)


def main():
    root = tk.Tk()
    try:
        ttk.Style().theme_use("clam")
    except tk.TclError:
        pass
    App(root, sys.argv[1] if len(sys.argv) > 1 else None)
    root.mainloop()


if __name__ == "__main__":
    main()