set autoscale

set terminal postscript enhanced color

set output 'zad3.pdf'

set key top center; 
set yrange [0:0.4]
set xlabel "Amount of equations [N]"; 
set ylabel "Time of execution [ms]"; 
set grid; 
plot "results_myLU.txt" with lines title "My solver", "results_GSL.txt" with lines title "GSL solver"

set output 'zad3smooth.pdf'

set key top center; 
set yrange [0:0.4]
set xlabel "Amount of equations [N]"; 
set ylabel "Time of execution [ms]"; 
set grid; 
plot "results_myLU.txt" using 1:2 smooth bezier title "My solver", "results_GSL.txt" using 1:2 smooth bezier title "GSL solver"