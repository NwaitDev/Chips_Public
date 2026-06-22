#!/usr/bin/python
import sys

n=[int(x) for x in sys.argv[1:]]

header="""
package big_broadcast_%d

  port type Port_t()
"""


atom="""
  atom type A_t()
    data int c
    export port Port_t p()
    place S, END
    initial to S do { c = 0; }
    on p from S to S provided (c<100) do {c = c + 1; }
    on p from S to END provided (c >= 100)
  end
  
"""

footer="""
  end

end
"""

def connector_t(num):
    return """
   connector type Bcast_t (Port_t s, %s)
   define s' %s
   end
   
""" % (",".join(["Port_t r%d"%i for i in range(num)]) , " ".join(["r%d"%i for i in range(num)]))

for sub_n in n:
    f = open("big_broadcast_%d.bip" % sub_n, "w")
    
    f.write(header % sub_n)
    f.write(connector_t(sub_n))
    f.write(atom)

    f.write("  compound type Top()\n")
    f.write("  component A_t sender()\n")
    
    for i in range(sub_n):
        f.write("  component A_t rcvr%d()\n" % i)

    f.write("  connector Bcast_t broadcast(sender.p, %s)" % (",".join(["rcvr%d.p" % d for d in range(sub_n)])))

    f.write(footer)
    f.close()
