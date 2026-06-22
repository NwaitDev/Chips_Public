#!/usr/bin/python

n=10

header="""
package rdv2by2

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


print header

for i in range(n):
    print "component A_t c%d()" % i


for i in range(n):
    for j in range(n):
        if i == j:
            pass
        else:
            print "connector Rdv_t co_%d_%d(c%d.p, c%d.p)" %(i,j,i,j)


print footer
