set title "1 big broadcast"
set xlabel "# of nodes"
set ylabel "exec time in s"
set y2label "perf boost in %"
set term png
set offsets 0, 0, 5, 0
set yr [0:]

set output "exec_times.png"
set ytics nomirror
set y2range [0:100]  
set y2tics nomirror

plot 'O0.res'  using '"O0_%lf_exec" %lf %lf"' smooth csplines title "O0 exec time" axis x1y1, \
  'O2.res'  using '"O2_%lf_exec" %lf %lf"' with lines title "O2 exec time" axis x1y1, \
  'O5.res'  using '"O5_%lf_exec" %lf %lf"' with lines title "O5 exec time" axis x1y1, \
  'perf_boost_O2.res' using '"O0_%lf_exec" %lf"' with lines title "O2 perf boost %" axis x1y2, \
  'perf_boost_O5.res' using '"O0_%lf_exec" %lf"' with lines title "O5 perf boost %" axis x1y2

set output "O0_compile_times.png"

set title "Compilation times"
set style histogram rowstacked
set style data histograms
plot 'O0_compile.res' using 2 title "bipc", '' using 5 title "cmake", '' using 8:xticlabels(1) title "make"

set output "O2_compile_times.png"
set title "Compilation times"
set style histogram rowstacked
set style data histograms
plot 'O2_compile.res' using 2 title "bipc", '' using 5 title "cmake", '' using 8:xticlabels(1) title "make"

set output "O5_compile_times.png"
set title "Compilation times"
set style histogram rowstacked
set style data histograms
plot 'O5_compile.res' using 2 title "bipc", '' using 5 title "cmake", '' using 8:xticlabels(1) title "make"

set output "O2_compile_memory.png"
set ylabel "max rss in Mib."
set title "max RSS usage"
set style histogram rowstacked
set style data histograms
plot 'O2_compile.res' using ($3/1024) title "bipc", '' using ($6/1024) title "cmake", '' using ($9/1024):xticlabels(1) title "make"

set output "O5_compile_memory.png"
set ylabel "max rss in Mib."
set title "max RSS usage"
set style histogram rowstacked
set style data histograms
plot 'O5_compile.res' using ($3/1024) title "bipc", '' using ($6/1024) title "cmake", '' using ($9/1024):xticlabels(1) title "make"


set output "O0_compile_memory.png"
set ylabel "max rss in Mib."
set title "max RSS usage"
set style histogram rowstacked
set style data histograms
plot 'O0_compile.res' using ($3/1024) title "bipc", '' using ($6/1024) title "cmake", '' using ($9/1024):xticlabels(1) title "make"
