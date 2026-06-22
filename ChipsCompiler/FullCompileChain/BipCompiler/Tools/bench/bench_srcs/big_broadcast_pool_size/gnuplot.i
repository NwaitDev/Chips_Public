set title "1 big broadcast"
set xlabel "pool size"
set ylabel "exec time in s"
set term png
set offsets 0, 0, 5, 0
set yr [0:]

set output "exec_times.png"
set ytics nomirror

plot '03.res'  using '"03_%lf_exec" %lf %lf"' smooth csplines title "3 nodes" axis x1y1, \
  '05.res'  using '"05_%lf_exec" %lf %lf"' with lines title "5 nodes" axis x1y1, \
  '10.res'  using '"10_%lf_exec" %lf %lf"' with lines title "10 nodes" axis x1y1
