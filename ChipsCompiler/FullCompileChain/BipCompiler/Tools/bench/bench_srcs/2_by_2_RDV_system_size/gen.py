#!/usr/bin/python
import sys

n=[int(x) for x in sys.argv[1:]]

header="""
package rdv2by2_%d

  port type Port_t()

  connector type Rdv_t (Port_t p1, Port_t p2)
  define p1 p2
  end

  atom type A_t()
    data int c
    export port Port_t p()
    place S, END
    initial to S do { c = 0; }
    on p from S to S provided (c<100) do {c = c + 1; }
    on p from S to END provided (c >= 100)
  end

  compound type Top()
"""

footer="""
  end

end
"""

for sub_n in n:
    f = open("rdv2by2_%d.bip" % sub_n, "w")
    
    f.write(header % sub_n)

    for i in range(sub_n):
        f.write("  component A_t c%d()" % i)


    for i in range(sub_n):
        for j in range(sub_n):
            if i == j:
                pass
            else:
                f.write( "connector Rdv_t co_%d_%d(c%d.p, c%d.p)" %(i,j,i,j))


    f.write(footer)
    f.close()
