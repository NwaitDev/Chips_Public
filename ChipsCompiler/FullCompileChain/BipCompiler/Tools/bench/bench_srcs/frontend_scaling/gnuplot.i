set title "Model construction time"
set ylabel "exec time in s."
set xlabel "# of nodes"
set term png
set output "frontend_times.png"
set offsets 0, 0, 5, 5
set yr [0:]

plot 'frontend.res'  using '"FRONTEND_%lf_bipc" %lf"' smooth csplines title "model construct exec time"

