set datafile separator ';'

set terminal svg size 1000,700 enhanced font 'Verdana,16' background 'white'
set output 'ResultPrints.svg'

set multiplot layout 3,1 title 'Data Treatment Block signals'  margins 0.075, 0.97, 0.1, 0.95 spacing 0.03

set grid
set key top left
set key spacing 0.9 samplen 2

set style data linespoints
unset xtics

set ytics
set ylabel 'Time (s)'
plot './output/DataTreatmentBlock.csv' using (column("1.TIME")):(column("2.REQ_TIME")) title 'Required time', \
     '' using (column("1.TIME")):(column("3.RES_TIME")) title 'Response time', \
     '' using (column("1.TIME")):(column("3.RES_TIME_AVG")) title 'avg res time'



set ylabel 'Number of images'
plot './output/DataTreatmentBlock.csv' using (column("1.TIME")):(column("5.CACHE_MISS")) title 'Cache miss'

set xtics
set xlabel 'Time (s)'
plot './output/DataTreatmentBlock.csv' using (column("1.TIME")):(column("4.CACHE_SIZE")) title 'Cache size'

unset multiplot
