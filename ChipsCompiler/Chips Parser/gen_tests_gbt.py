#!/usr/bin/env python3
"""
Grammar-based test generator (subset): system { declarations; expressions; }

It generates:
  - Valid syntax tests  -> unitTestFilesForCompiler/ShouldCompileSyntax/
  - Invalid syntax tests-> unitTestFilesForCompiler/ShouldNotCompileSyntax/

Design goals:
  - Quick, pragmatic grammar-based testing (paper-inspired)
  - Depth-limited expression generation to avoid infinite recursion
  - "Almost valid" mutations for negative tests

Usage:
    python3 gen_tests_gbt.py --out-root . --valid 200 --invalid 200 --seed 123

By default, out-root is current directory. It will create:
  ./unitTestFilesForCompiler/ShouldCompileSyntax/
  ./unitTestFilesForCompiler/ShouldNotCompileSyntax/

Tip:
  Run your existing test harness afterwards:
    ./CompilerTests.sh

Cleaning:
    Add --clean to remove previously generated files matching:
        unitTestFilesForCompiler/ShouldCompileSyntax/gbt_valid_*.chips
        unitTestFilesForCompiler/ShouldNotCompileSyntax/gbt_invalid_*.chips
"""

from __future__ import annotations
import argparse
import glob
import os
import random
from dataclasses import dataclass
from typing import List, Tuple, Literal


IDENT_CHARS = "abcdefghijklmnopqrstuvwxyz"

# Identifiers must not collide with lexer keywords. Some keywords are currently
# *swallowed* by the lexer (they have an empty action), which is even worse than
# being tokenized as a keyword.
RESERVED_IDENTIFIERS = {
    # literals
    "true",
    "false",
    # types / decl keywords
    "int",
    "float",
    "bool",
    "logical",
    "physical",
    "object",
    "with",
    "implementation",
    "by",
    "default",
    "using",
    "actuator",
    "sensor",
    "ctx",
    # control/system keywords
    "system",
    "for",
    "in",
    "if",
    "to",
    "else",
    "init",
    "then",
    "as",
    "link",
    "implements",
    "having",
    "input",
    "stop",
    "channel",
    "channels",
    "among",
    "spread",
    "collect",
    # lexer rules present but currently commented out (empty action => token is eaten)
    "pure",
    "import",
    "this",
    "at",
    "dimensions",
    "dim",
}

DFType = Literal["int", "float", "bool"]


@dataclass
class BlockInst:
    type_name: str
    inst_name: str
    suffix: str

def ident(rng: random.Random) -> str:
    while True:
        n = rng.randint(1, 8)
        s = rng.choice(IDENT_CHARS)
        for _ in range(n - 1):
            s += rng.choice(IDENT_CHARS + "0123456789_")
        # Avoid reserved keywords and also prefixes that would interact badly
        # with lexer rules like ".in" and ".out" (currently swallowed).
        if s in RESERVED_IDENTIFIERS:
            continue
        if s.startswith("in") or s.startswith("out"):
            continue
        if s not in RESERVED_IDENTIFIERS:
            return s

def choose_weighted(rng: random.Random, items: List[Tuple[object, float]]):
    total = sum(w for _, w in items)
    if total <= 0:
        return items[0][0]
    x = rng.random() * total
    acc = 0.0
    for v, w in items:
        acc += w
        if x <= acc:
            return v
    return items[-1][0]


ARITH_OPS = [("+", 1.0), ("-", 1.0), ("*", 1.0), ("/", 0.8)]
INT_ONLY_OPS = [("%", 0.6)]
REL_OPS = [("<", 0.6), (">", 0.6), ("<=", 0.6), (">=", 0.6)]
EQ_OPS = [("==", 0.6), ("!=", 0.6)]
BOOL_OPS = [("&&", 0.6), ("||", 0.6)]
CASTS: List[DFType] = ["int", "float", "bool"]

@dataclass
class GenCtx:
    rng: random.Random
    vars_int: List[str]
    vars_float: List[str]
    vars_bool: List[str]
    ctx_vars: List[str]
    blocks: List[BlockInst]
    known_block_types: List[str]

    def push_temp_var(self, typ: DFType, name: str) -> None:
        self.vars_for(typ).append(name)

    def pop_temp_var(self, typ: DFType, name: str) -> None:
        pool = self.vars_for(typ)
        for i in range(len(pool) - 1, -1, -1):
            if pool[i] == name:
                del pool[i]
                return

    def vars_for(self, typ: DFType) -> List[str]:
        if typ == "int":
            return self.vars_int
        if typ == "float":
            return self.vars_float
        return self.vars_bool

def gen_literal(ctx: GenCtx, typ: DFType) -> str:
    r = ctx.rng
    if typ == "int":
        v = r.randint(-50, 200)
        # The lexer does not tokenize signed integers (it matches only {DIGIT}+),
        # so emitting "-12" would produce MINUS INT(12). That is not accepted
        # everywhere by the current parser (e.g. after '*' or '/').
        # Emit negative literals as parenthesized expressions so they start with
        # '(' and are valid as an expr2 anywhere.
        if v < 0:
            return f"(-{abs(v)})"
        return str(v)
    if typ == "float":
        iv = r.randint(-50, 200)
        frac = r.randint(0, 99)
        if iv < 0:
            return f"(-{abs(iv)}.{frac:02d})"
        return f"{iv}.{frac:02d}"
    if typ == "bool":
        return r.choice(["true", "false"])
    return "0"

def gen_atom_typed(ctx: GenCtx, depth: int, typ: DFType) -> str:
    r = ctx.rng
    choices: List[Tuple[str, float]] = [
        ("literal", 2.0),
        ("var", 2.2),
        ("paren", 1.0),
        ("cast", 0.5),
    ]
    kind = choose_weighted(r, choices)

    if kind == "literal":
        return gen_literal(ctx, typ)

    if kind == "var":
        pool = ctx.vars_for(typ)
        if pool:
            return r.choice(pool)
        return gen_literal(ctx, typ)

    if kind == "paren" and depth > 0:
        inner = gen_expr_typed(ctx, depth - 1, typ)
        # Avoid generating parenthesized bare identifiers like "(x)" which can
        # be mis-parsed as a collective operation "(IDENTIFIER)" in s_expr
        # contexts (plugging statements) due to grammar ambiguity.
        if inner.isidentifier():
            if typ == "bool":
                return f"({inner} && true)"
            return f"({inner} + 0)"
        return f"({inner})"

    if kind == "cast" and depth > 0:
        # Grammar: '(' df_type ')' expr
        # Keep it simple: cast from a different type occasionally.
        src = r.choice([t for t in CASTS if t != typ] or CASTS)
        inner = gen_expr_typed(ctx, depth - 1, src)
        return f"({typ}) {inner}"

    return gen_literal(ctx, typ)


def gen_numeric_expr(ctx: GenCtx, depth: int, want: Literal["int", "float"]) -> str:
    r = ctx.rng
    if depth <= 0:
        return gen_atom_typed(ctx, 0, want)

    kind = choose_weighted(r, [("atom", 1.4), ("unary", 0.5), ("binary", 1.9), ("cast", 0.3)])
    if kind == "atom":
        return gen_atom_typed(ctx, depth, want)

    if kind == "unary":
        # Parenthesize unary minus so it can safely appear where an expr2 is
        # required (e.g. as the RHS of '*' or '/').
        return f"(-{gen_numeric_expr(ctx, depth - 1, want)})"

    if kind == "cast":
        other: DFType = "int" if want == "float" else "float"
        inner = gen_numeric_expr(ctx, depth - 1, other) if other in ("int", "float") else gen_atom_typed(ctx, 0, other)
        return f"({want}) {inner}"

    # binary
    op_items = ARITH_OPS + (INT_ONLY_OPS if want == "int" and r.random() < 0.4 else [])
    op = choose_weighted(r, op_items)
    if want == "float":
        # Ensure at least one operand can be float sometimes
        left = gen_numeric_expr(ctx, depth - 1, r.choice(["float", "int"]))
        right = gen_numeric_expr(ctx, depth - 1, r.choice(["float", "int"]))
        if r.random() < 0.7:
            left = gen_numeric_expr(ctx, depth - 1, "float")
        return f"{left} {op} {right}"

    left = gen_numeric_expr(ctx, depth - 1, "int")
    right = gen_numeric_expr(ctx, depth - 1, "int")
    return f"{left} {op} {right}"


def gen_bool_expr(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if depth <= 0:
        return gen_atom_typed(ctx, 0, "bool")

    kind = choose_weighted(
        r,
        [
            ("atom", 1.6),
            ("not", 0.6),
            ("andor", 1.3),
            ("rel", 1.2),
            ("eq", 0.9),
            ("paren", 0.7),
            ("cast", 0.2),
        ],
    )

    if kind == "atom":
        return gen_atom_typed(ctx, depth, "bool")
    if kind == "paren":
        inner = gen_bool_expr(ctx, depth - 1)
        # Avoid producing "(x)" (bare identifier) which can be interpreted as
        # collective_operation in s_expr contexts.
        if inner.isidentifier():
            return f"({inner} && true)"
        return f"({inner})"
    if kind == "not":
        # Parenthesize after '!' so it binds to the intended expression and to
        # prevent patterns like '!!true' (NOT NOT BOOL) which the parser rejects
        # because NOT expects an expr2.
        return f"!({gen_bool_expr(ctx, depth - 1)})"
    if kind == "andor":
        op = choose_weighted(r, BOOL_OPS)
        left = gen_bool_expr(ctx, depth - 1)
        right = gen_bool_expr(ctx, depth - 1)
        return f"{left} {op} {right}"
    if kind == "rel":
        op = choose_weighted(r, REL_OPS)
        # Comparisons require numeric operands
        ntyp = r.choice(["int", "float"])
        left = gen_numeric_expr(ctx, depth - 1, ntyp)
        right = gen_numeric_expr(ctx, depth - 1, ntyp)
        return f"{left} {op} {right}"
    if kind == "eq":
        op = choose_weighted(r, EQ_OPS)
        # Keep it semantically safe: only boolean equality.
        left = gen_bool_expr(ctx, depth - 1)
        right = gen_bool_expr(ctx, depth - 1)
        return f"{left} {op} {right}"
    if kind == "cast":
        # Cast a numeric expression to bool, then compare
        inner = gen_numeric_expr(ctx, depth - 1, r.choice(["int", "float"]))
        return f"(bool) {inner}"

    return gen_atom_typed(ctx, 0, "bool")


def gen_expr_typed(ctx: GenCtx, depth: int, typ: DFType) -> str:
    if typ == "bool":
        return gen_bool_expr(ctx, depth)
    return gen_numeric_expr(ctx, depth, typ)


TYPES: List[DFType] = ["int", "float", "bool"]


def gen_suffixes(ctx: GenCtx, depth: int, *, max_dims: int = 2, ensure_nonempty: bool = False) -> str:
    """Generate Chips 'suffixes' (e.g., [0][i]).

    In this grammar the same suffix syntax is used for:
    - df_type dimensions: int[10] x;
    - indexing: x[0] = 1;
    """
    r = ctx.rng
    if depth <= 0 and not ensure_nonempty:
        return ""

    dims = 0
    if ensure_nonempty:
        dims = r.randint(1, max_dims)
    else:
        dims = choose_weighted(r, [(0, 2.2), (1, 1.0), (2, 0.4)])
        dims = int(dims)
        dims = min(dims, max_dims)

    parts: List[str] = []
    for _ in range(dims):
        # Keep indices simple and int-typed.
        idx = gen_numeric_expr(ctx, max(depth - 1, 0), "int")
        parts.append(f"[{idx}]")
    return "".join(parts)


def gen_df_type(ctx: GenCtx, depth: int) -> Tuple[DFType, str]:
    t: DFType = ctx.rng.choice(TYPES)
    suff = gen_suffixes(ctx, depth, max_dims=2, ensure_nonempty=False)
    return t, suff

def gen_decl(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    t, tsuff = gen_df_type(ctx, depth)
    name = ident(r)

    # Generate initializer BEFORE registering the variable to avoid self-reference.
    if r.random() < 0.85:
        expr = gen_expr_typed(ctx, depth, t)
        stmt = f"{t}{tsuff} {name} = {expr};"
    else:
        stmt = f"{t}{tsuff} {name};"

    ctx.vars_for(t).append(name)
    return stmt

def gen_assign(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    pool = ctx.vars_int + ctx.vars_float + ctx.vars_bool
    if not pool:
        # Keep semantics valid: no assignment before any declaration.
        return gen_decl(ctx, depth)

    v = r.choice(pool)
    if v in ctx.vars_bool:
        expr = gen_expr_typed(ctx, depth, "bool")
    elif v in ctx.vars_float:
        expr = gen_expr_typed(ctx, depth, "float")
    else:
        expr = gen_expr_typed(ctx, depth, "int")
    # Optional indexing on assignment target (syntactic coverage).
    target_suffix = ""
    if r.random() < 0.15:
        target_suffix = gen_suffixes(ctx, depth, max_dims=2, ensure_nonempty=True)
    return f"{v}{target_suffix} = {expr};"


def gen_ctx_assignment(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if ctx.ctx_vars and r.random() < 0.85:
        name = r.choice(ctx.ctx_vars)
    else:
        name = ident(r)
        ctx.ctx_vars.append(name)

    # Context variables are expressions: ctx.<id> suffixes
    suffix = ""
    if r.random() < 0.2:
        suffix = gen_suffixes(ctx, depth, max_dims=2, ensure_nonempty=True)

    # We don't have type info for ctx vars; choose a numeric expression most of the time.
    typ: DFType = r.choice(["int", "float", "bool"])
    expr = gen_expr_typed(ctx, depth, typ)
    return f"ctx.{name}{suffix} = {expr};"


def gen_if_block(ctx: GenCtx, depth: int, *, is_system: bool) -> str:
    cond = gen_expr_typed(ctx, max(depth - 1, 0), "bool")
    body = gen_statements(ctx, max(depth - 1, 0), is_system=is_system)
    if ctx.rng.random() < 0.35:
        else_body = gen_statements(ctx, max(depth - 1, 0), is_system=is_system)
        return f"if ({cond}) {{\n{body}\n}} else {{\n{else_body}\n}}"
    return f"if ({cond}) {{\n{body}\n}}"


def gen_for_block(ctx: GenCtx, depth: int, *, is_system: bool) -> str:
    r = ctx.rng
    it_var = ident(r)
    loop_var = ident(r)
    # Try to iterate over an existing block or variable name if possible.
    if ctx.blocks and r.random() < 0.35:
        it_var = r.choice(ctx.blocks).inst_name
    elif (ctx.vars_int or ctx.vars_float or ctx.vars_bool) and r.random() < 0.6:
        it_var = r.choice(ctx.vars_int + ctx.vars_float + ctx.vars_bool)

    # Assume loop variable is int for expression generation.
    ctx.push_temp_var("int", loop_var)
    body = gen_statements(ctx, max(depth - 1, 0), is_system=is_system)
    ctx.pop_temp_var("int", loop_var)
    # Lexer maps keyword 'for' to FOREACH_KW.
    return f"for {loop_var} in {it_var} {{\n{body}\n}}"

def gen_stmt(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    # Weighted choice between decl and assign. If no variable exists yet,
    # force a declaration to keep semantic analysis happy.
    if not (ctx.vars_int or ctx.vars_float or ctx.vars_bool):
        return gen_decl(ctx, depth)
    kind = choose_weighted(r, [("decl", 1.2), ("assign", 1.6), ("ctx_assign", 0.5)])
    if kind == "decl":
        return gen_decl(ctx, depth)
    if kind == "ctx_assign":
        return gen_ctx_assignment(ctx, depth)
    return gen_assign(ctx, depth)


def gen_block_instantiation(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if ctx.known_block_types and r.random() < 0.8:
        type_name = r.choice(ctx.known_block_types)
    else:
        type_name = ident(r)
        if type_name not in ctx.known_block_types:
            ctx.known_block_types.append(type_name)

    inst_name = ident(r)
    suff = ""
    if r.random() < 0.25:
        suff = gen_suffixes(ctx, depth, max_dims=2, ensure_nonempty=True)
    ctx.blocks.append(BlockInst(type_name=type_name, inst_name=inst_name, suffix=suff))
    return f"{type_name}{suff} {inst_name};"


def gen_link_stmt(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if len(ctx.blocks) < 2:
        # Create at least two blocks.
        a = gen_block_instantiation(ctx, depth)
        b = gen_block_instantiation(ctx, depth)
        # Return both (as two lines) to keep caller simple.
        return f"{a}\n  {b}\n  link {ctx.blocks[-2].inst_name} to {ctx.blocks[-1].inst_name};"
    src, dst = r.sample(ctx.blocks, 2)
    return f"link {src.inst_name}{src.suffix} to {dst.inst_name}{dst.suffix};"


def gen_plugging_expr(ctx: GenCtx) -> str:
    r = ctx.rng
    if not ctx.blocks:
        # Fallback to a normal expression.
        return gen_expr_typed(ctx, 1, r.choice(TYPES))
    b = r.choice(ctx.blocks)
    port = ident(r)
    return f"{b.inst_name}{b.suffix}.{port}"


def gen_plugging_stmt(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if not ctx.blocks:
        return gen_block_instantiation(ctx, depth)

    b = r.choice(ctx.blocks)
    port = ident(r)
    # optional suffix on the port name
    psuff = ""
    if r.random() < 0.2:
        psuff = gen_suffixes(ctx, depth, max_dims=2, ensure_nonempty=True)

    # s_expr can be expr or another plugging expr or collective cast; keep it simple.
    if r.random() < 0.35 and len(ctx.blocks) >= 2:
        arg = gen_plugging_expr(ctx)
    else:
        arg = gen_expr_typed(ctx, max(depth - 1, 0), r.choice(TYPES))
    return f"{b.inst_name}{b.suffix}.{port}{psuff}({arg});"


def gen_implements_stmt(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    # Grammar: IDENT suffixes implements IDENT suffixes using IDENT;
    # We reuse existing block instances when possible.
    if len(ctx.blocks) >= 2:
        left, right = r.sample(ctx.blocks, 2)
        using = ident(r)
        return f"{left.inst_name}{left.suffix} implements {right.inst_name}{right.suffix} using {using};"
    # Fallback: syntactically valid random identifiers
    return f"{ident(r)} implements {ident(r)} using {ident(r)};"


def gen_s_statement(ctx: GenCtx, depth: int, *, allow_system_ops: bool, allow_control_flow: bool) -> str:
    r = ctx.rng
    choices: List[Tuple[str, float]] = [("stmt", 2.2)]
    if allow_system_ops:
        choices += [("block", 1.0), ("link", 0.7), ("plug", 1.0), ("impl", 0.3)]
    if allow_control_flow and depth > 0:
        choices += [("if", 0.6), ("for", 0.6)]

    kind = choose_weighted(r, choices)
    if kind == "stmt":
        return gen_stmt(ctx, depth)
    if kind == "block":
        return gen_block_instantiation(ctx, depth)
    if kind == "link":
        return gen_link_stmt(ctx, depth)
    if kind == "plug":
        return gen_plugging_stmt(ctx, depth)
    if kind == "impl":
        return gen_implements_stmt(ctx, depth)
    if kind == "if":
        return gen_if_block(ctx, depth, is_system=True)
    if kind == "for":
        return gen_for_block(ctx, depth, is_system=True)
    return gen_stmt(ctx, depth)


def gen_statements(ctx: GenCtx, depth: int, *, is_system: bool, max_stmts: int | None = None) -> str:
    r = ctx.rng
    n = r.randint(1, max_stmts or 4)
    lines: List[str] = []
    for _ in range(n):
        if is_system:
            lines.append("  " + gen_s_statement(ctx, depth, allow_system_ops=True, allow_control_flow=True).replace("\n", "\n  "))
        else:
            # In init/then/with blocks we stick to regular statements (and some control-flow).
            k = choose_weighted(r, [("stmt", 2.2), ("if", 0.5), ("for", 0.5)]) if depth > 0 else "stmt"
            if k == "stmt":
                lines.append("  " + gen_stmt(ctx, depth))
            elif k == "if":
                lines.append("  " + gen_if_block(ctx, depth, is_system=False).replace("\n", "\n  "))
            else:
                lines.append("  " + gen_for_block(ctx, depth, is_system=False).replace("\n", "\n  "))
    return "\n".join(lines)


def gen_with_section(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    if r.random() < 0.45:
        return ""
    n = r.randint(0, 3)
    lines: List[str] = []
    for _ in range(n):
        kind = choose_weighted(r, [("two_id", 0.8), ("ctx_decl", 0.8), ("stmt", 1.0)])
        if kind == "two_id":
            lines.append(f"  {ident(r)} {ident(r)};")
        elif kind == "ctx_decl":
            t, ts = gen_df_type(ctx, depth)
            v = ident(r)
            if r.random() < 0.5:
                expr = gen_expr_typed(ctx, depth, t)
                lines.append(f"  ctx {t}{ts} {v} = {expr};")
            else:
                lines.append(f"  ctx {t}{ts} {v};")
        else:
            lines.append(f"  {gen_stmt(ctx, depth)}")

    body = "\n".join(lines)
    return f"with {{\n{body}\n}}\n"


def gen_df_parameters(ctx: GenCtx, depth: int, max_params: int = 3) -> Tuple[str, List[Tuple[DFType, str]]]:
    r = ctx.rng
    n = r.randint(0, max_params)
    params: List[str] = []
    declared: List[Tuple[DFType, str]] = []
    for _ in range(n):
        t, ts = gen_df_type(ctx, depth)
        name = ident(r)
        declared.append((t, name))
        if r.random() < 0.35:
            expr = gen_expr_typed(ctx, depth, t)
            params.append(f"{t}{ts} {name} = {expr}")
        else:
            params.append(f"{t}{ts} {name}")
    return ", ".join(params), declared


def gen_named_outputs(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    n = r.randint(1, 2)
    outs: List[str] = []
    for _ in range(n):
        out_name = ident(r)
        # list_expr can be empty
        if r.random() < 0.25:
            outs.append(f"-> {out_name}()")
        else:
            k = r.randint(1, 2)
            exprs = ", ".join(gen_expr_typed(ctx, depth, r.choice(TYPES)) for _ in range(k))
            outs.append(f"-> {out_name}({exprs})")
    return "\n".join(outs) + "\n"


def gen_logical_function(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    name = ident(r)
    params_txt, declared = gen_df_parameters(ctx, depth)
    # Parameters are in scope inside init/then.
    for t, n in declared:
        ctx.push_temp_var(t, n)

    init_body = gen_statements(ctx, max(depth - 1, 0), is_system=False, max_stmts=3)
    then_body = gen_statements(ctx, max(depth - 1, 0), is_system=False, max_stmts=3)
    outs = gen_named_outputs(ctx, depth)

    for t, n in declared:
        ctx.pop_temp_var(t, n)

    ctx.known_block_types.append(name)
    return (
        f"logical {name}({params_txt})\n"
        f"init {{\n{init_body}\n}}\n"
        f"then {{\n{then_body}\n}}\n"
        f"{outs}"
    )


def gen_physical_function(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    name = ident(r)
    params_txt, declared = gen_df_parameters(ctx, depth)
    for t, n in declared:
        ctx.push_temp_var(t, n)

    with_sec = gen_with_section(ctx, depth)
    init_body = gen_statements(ctx, max(depth - 1, 0), is_system=False, max_stmts=3)
    then_body = gen_statements(ctx, max(depth - 1, 0), is_system=False, max_stmts=3)
    outs = gen_named_outputs(ctx, depth)

    for t, n in declared:
        ctx.pop_temp_var(t, n)

    ctx.known_block_types.append(name)
    return (
        f"physical {name}({params_txt})\n"
        f"{with_sec}"
        f"init {{\n{init_body}\n}}\n"
        f"then {{\n{then_body}\n}}\n"
        f"{outs}"
    )


def gen_object_def(ctx: GenCtx, depth: int) -> str:
    name = ident(ctx.rng)
    with_sec = gen_with_section(ctx, depth)
    return f"object {name} {with_sec}".rstrip() + "\n"


def gen_implementation_def(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    impl = ident(r)
    left = ident(r)
    right = ident(r)
    n = r.randint(0, 2)
    lines: List[str] = []
    for _ in range(n):
        lines.append(f"  having {ident(r)} as {ident(r)};")
    body = "\n".join(lines)
    return f"implementation {impl}: {left} by {right} {{\n{body}\n}}\n"


def gen_collective_op(ctx: GenCtx, depth: int) -> str:
    r = ctx.rng
    kw = r.choice(["spread", "collect"])
    name = ident(r)
    among = ident(r)
    group = ident(r)
    # Keep signature minimal: empty cdf_defaulted_decls
    # Keep body minimal: empty c_statements
    # Target list empty and output default empty.
    return (
        f"{kw}() {name} among {among} {{\n}}\n"
        f"-> @()\n"
        f"-> default()\n"
    )


def gen_preambles(ctx: GenCtx, depth: int, max_preambles: int) -> str:
    r = ctx.rng
    n = r.randint(0, max_preambles)
    pre: List[str] = []
    for _ in range(n):
        kind = choose_weighted(r, [("logical", 1.0), ("physical", 0.7), ("object", 0.4), ("impl", 0.3), ("collective", 0.2)])
        if kind == "logical":
            pre.append(gen_logical_function(ctx, depth))
        elif kind == "physical":
            pre.append(gen_physical_function(ctx, depth))
        elif kind == "object":
            pre.append(gen_object_def(ctx, depth))
        elif kind == "impl":
            pre.append(gen_implementation_def(ctx, depth))
        else:
            pre.append(gen_collective_op(ctx, depth))
    return "\n".join(p.rstrip() for p in pre if p.strip()) + ("\n\n" if pre else "")

def gen_program(
    rng: random.Random,
    max_stmts: int,
    expr_depth: int,
    *,
    with_preambles: bool = False,
    with_system_ops: bool = False,
    with_control_flow: bool = True,
    max_preambles: int = 2,
) -> str:
    ctx = GenCtx(
        rng=rng,
        vars_int=[],
        vars_float=[],
        vars_bool=[],
        ctx_vars=[],
        blocks=[],
        known_block_types=[],
    )

    pre = ""
    if with_preambles:
        pre = gen_preambles(ctx, expr_depth, max_preambles=max_preambles)

    # SYSTEM contains s_statements; s_statement includes 'statement', so this still covers decl/assign.
    n = rng.randint(1, max_stmts)
    stmts: List[str] = []
    for _ in range(n):
        stmts.append(gen_s_statement(ctx, expr_depth, allow_system_ops=with_system_ops, allow_control_flow=with_control_flow))

    body = "\n  ".join(s.replace("\n", "\n  ") for s in stmts)
    return pre + f"SYSTEM {{\n  {body}\n}}\n"


def mutate_to_invalid(rng: random.Random, s: str) -> Tuple[str, str]:
    muts: List[Tuple[str, float]] = []
    if ";" in s:
        muts.append(("drop_semicolon", 1.6))
    if "{" in s:
        muts.append(("drop_lbrace", 0.9))
    if "}" in s:
        muts.append(("drop_rbrace", 1.2))
    if ")" in s:
        muts.append(("drop_rparen", 1.0))
    if "(" in s:
        muts.append(("drop_lparen", 0.7))
    if "[" in s:
        muts.append(("drop_lsquare", 0.7))
    if "]" in s:
        muts.append(("drop_rsquare", 0.9))
    muts.append(("insert_stray_op", 0.8))
    muts.append(("insert_stray_keyword", 0.7))
    muts.append(("insert_extra_rparen", 0.7))
    muts.append(("insert_extra_comma", 0.6))
    if "=" in s:
        muts.append(("eq_to_eqeq", 0.9))
    if "==" in s:
        muts.append(("eqeq_to_eq", 0.8))
    # Strong pattern-based syntax breakers (prefer these over semantic-only mutations).
    if "if (" in s:
        muts.append(("break_if_paren", 0.9))
    if "for " in s and " in " in s:
        muts.append(("break_for_in", 0.9))
    if "(int)" in s or "(float)" in s or "(bool)" in s:
        muts.append(("break_cast", 0.8))
    if "." in s and "(" in s and ");" in s:
        muts.append(("break_plug_call", 0.7))
    muts.append(("insert_extra_rbrace", 0.6))
    if "->" in s:
        muts.append(("mangle_arrow", 0.7))
    if "\nSYSTEM" in s or s.startswith("SYSTEM"):
        muts.append(("mangle_system_kw", 0.5))
    if "link " in s and " to " in s:
        muts.append(("drop_to_keyword", 0.5))
    if " implements " in s and " using " in s:
        muts.append(("drop_using_keyword", 0.5))

    kind = choose_weighted(rng, muts)

    if kind == "drop_semicolon":
        i = s.rfind(";")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_lbrace":
        i = s.find("{")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_rbrace":
        i = s.rfind("}")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_rparen":
        i = s.rfind(")")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_lparen":
        i = s.find("(")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_lsquare":
        i = s.find("[")
        return kind, s[:i] + s[i + 1 :]
    if kind == "drop_rsquare":
        i = s.rfind("]")
        return kind, s[:i] + s[i + 1 :]
    if kind == "insert_stray_op":
        pos = rng.randint(0, len(s))
        return kind, s[:pos] + " + * " + s[pos:]
    if kind == "insert_stray_keyword":
        # Insert a real keyword token in a random place; should break most productions.
        pos = rng.randint(0, len(s))
        kw = rng.choice([" else ", " then ", " init ", " using ", " implements ", " link ", " SYSTEM "])
        return kind, s[:pos] + kw + s[pos:]
    if kind == "insert_extra_rparen":
        pos = rng.randint(0, len(s))
        return kind, s[:pos] + ")" + s[pos:]
    if kind == "insert_extra_comma":
        # Prefer to place it in an argument list if possible.
        p = s.find("(")
        if p != -1:
            return kind, s[: p + 1] + "," + s[p + 1 :]
        pos = rng.randint(0, len(s))
        return kind, s[:pos] + "," + s[pos:]
    if kind == "eq_to_eqeq":
        return kind, s.replace("=", "==", 1)
    if kind == "eqeq_to_eq":
        return kind, s.replace("==", "=", 1)
    if kind == "break_if_paren":
        # Turn 'if (<expr>)' into 'if <expr>)' (missing '(' token).
        return kind, s.replace("if (", "if ", 1)
    if kind == "break_for_in":
        # Turn 'for x in y' into 'for x y' (remove required IN_KW).
        return kind, s.replace(" in ", " ", 1)
    if kind == "break_cast":
        # Break a cast token sequence by removing the closing ')'.
        for t in ("(int)", "(float)", "(bool)"):
            if t in s:
                return kind, s.replace(t, t[:-1], 1)
        return kind, s + "(int"
    if kind == "break_plug_call":
        # Break a plugging call 'a.b(...);' by removing the '(' after the port.
        # This yields 'a.b...);' which should not match any statement production.
        import re

        m = re.search(r"\.[A-Za-z][A-Za-z0-9_]*\s*\(", s)
        if m:
            i = m.end() - 1
            return kind, s[:i] + s[i + 1 :]
        # Fallback: remove the first '(' in the program.
        p = s.find("(")
        if p != -1:
            return kind, s[:p] + s[p + 1 :]
        return kind, s + "("
    if kind == "insert_extra_rbrace":
        pos = rng.randint(0, len(s))
        return kind, s[:pos] + "}" + s[pos:]
    if kind == "mangle_arrow":
        # Break the ARROW token into something else.
        return kind, s.replace("->", "-", 1)
    if kind == "mangle_system_kw":
        # Replace SYSTEM keyword with an identifier; should not match SYSTEM_KW.
        return kind, s.replace("SYSTEM", "SYSTEMS", 1)
    if kind == "drop_to_keyword":
        return kind, s.replace(" to ", " ", 1)
    if kind == "drop_using_keyword":
        return kind, s.replace(" using ", " ", 1)
    return "fallback", s + " ) "


def write_cases(out_dir: str, cases: List[str], prefix: str):
    os.makedirs(out_dir, exist_ok=True)
    for i, txt in enumerate(cases, 1):
        path = os.path.join(out_dir, f"{prefix}_{i:04d}.chips")
        with open(path, "w", encoding="utf-8") as f:
            f.write(txt)


def write_tagged_cases(out_dir: str, cases: List[Tuple[str, str]], prefix: str):
    os.makedirs(out_dir, exist_ok=True)
    for i, (kind, txt) in enumerate(cases, 1):
        # Keep filenames stable and easy to group/sort by mutation kind.
        path = os.path.join(out_dir, f"{prefix}_{kind}_{i:04d}.chips")
        with open(path, "w", encoding="utf-8") as f:
            f.write(f"// mutation: {kind}\n")
            f.write(txt)


def clean_generated(out_dir: str, prefix: str) -> int:
    """Remove previously generated test cases for a given prefix.

    Only deletes files named like: {prefix}_*.chips
    Returns the number of files removed.
    """
    if not os.path.isdir(out_dir):
        return 0
    pattern = os.path.join(out_dir, f"{prefix}_*.chips")
    removed = 0
    for path in glob.glob(pattern):
        try:
            os.remove(path)
            removed += 1
        except OSError:
            # Best-effort cleanup; generation can still proceed.
            pass
    return removed

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out-root", default=".", help="Project root where unitTestFilesForCompiler/ lives (default: .)")
    ap.add_argument("--valid", type=int, default=200, help="Number of valid syntax tests")
    ap.add_argument("--invalid", type=int, default=200, help="Number of invalid syntax tests")
    ap.add_argument("--seed", type=int, default=None, help="Random seed (optional)")
    ap.add_argument("--max-stmts", type=int, default=8, help="Max statements per program")
    ap.add_argument("--expr-depth", type=int, default=4, help="Expression recursion depth")
    ap.add_argument("--with-control-flow", action="store_true", help="(Deprecated) Full mode is always enabled")
    ap.add_argument("--with-system-ops", action="store_true", help="(Deprecated) Full mode is always enabled")
    ap.add_argument("--with-preambles", action="store_true", help="(Deprecated) Full mode is always enabled")
    ap.add_argument("--max-preambles", type=int, default=2, help="Max number of generated preambles per program")
    ap.add_argument(
        "--full",
        action="store_true",
        help="Enable --with-preambles --with-system-ops --with-control-flow",
    )
    ap.add_argument(
        "--clean",
        action="store_true",
        help="Delete previously generated gbt_valid_*.chips / gbt_invalid_*.chips before writing new ones",
    )
    args = ap.parse_args()

    # Always enable full generation (requested): preambles + system ops + control flow.
    # Keep the CLI flags for backward compatibility, but they no longer change behavior.
    args.full = True
    args.with_preambles = True
    args.with_system_ops = True
    args.with_control_flow = True

    rng = random.Random(args.seed)

    valid_cases = [
        gen_program(
            rng,
            args.max_stmts,
            args.expr_depth,
            with_preambles=args.with_preambles,
            with_system_ops=args.with_system_ops,
            with_control_flow=args.with_control_flow,
            max_preambles=args.max_preambles,
        )
        for _ in range(args.valid)
    ]

    # Invalid cases are created by mutating valid ones. Support --invalid without
    # forcing the user to also request --valid output files.
    invalid_cases: List[Tuple[str, str]] = []
    if args.invalid > 0:
        base_valid_cases = valid_cases
        if not base_valid_cases:
            # Generate a small internal pool for mutation.
            base_n = min(10, args.invalid)
            base_valid_cases = [
                gen_program(
                    rng,
                    args.max_stmts,
                    args.expr_depth,
                    with_preambles=args.with_preambles,
                    with_system_ops=args.with_system_ops,
                    with_control_flow=args.with_control_flow,
                    max_preambles=args.max_preambles,
                )
                for _ in range(base_n)
            ]
        invalid_cases = [mutate_to_invalid(rng, base_valid_cases[i % len(base_valid_cases)]) for i in range(args.invalid)]

    should_compile = os.path.join(args.out_root, "unitTestFilesForCompiler", "ShouldCompileSyntax")
    should_not_compile = os.path.join(args.out_root, "unitTestFilesForCompiler", "ShouldNotCompileSyntax")

    if args.clean:
        removed_valid = clean_generated(should_compile, "gbt_valid")
        removed_invalid = clean_generated(should_not_compile, "gbt_invalid")
        print(f"Cleaned: {removed_valid} valid + {removed_invalid} invalid")

    write_cases(should_compile, valid_cases, "gbt_valid")
    write_tagged_cases(should_not_compile, invalid_cases, "gbt_invalid")

    print("Generated:")
    print(f"  {len(valid_cases)} valid   -> {should_compile}")
    print(f"  {len(invalid_cases)} invalid-> {should_not_compile}")
    print("Next:")
    print("  ./CompilerTests.sh")

if __name__ == "__main__":
    main()
