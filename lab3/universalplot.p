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





set yrange [0:0.02]
set output 'level1.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" with lines title "DDOT"





set output 'level1smooth.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" using 1:2 smooth bezier title "DDOT"





set yrange [0:1.5]
set xrange [0:1000]
set output 'level2.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" with lines title "DDOT", "results_dgemv.txt" with lines title "DGEMV"






set output 'level2smooth.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" with lines title "DDOT", "results_dgemv.txt" using 1:2 smooth bezier title "DGEMV"






set yrange [0:70]
set xrange [0:500]
set output 'level3.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" with lines title "DDOT", "results_dgemv.txt" with lines title "DGEMV", "results_dgemm.txt" with lines title "DGEMM"






set output 'level3smooth.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" with lines title "DDOT", "results_dgemv.txt" with lines title "DGEMV", "results_dgemm.txt" u 1:2 smooth bezier title "DGEMM"





set yrange [0:0.1]
set xrange [0:1000]
set output 'final.pdf'
set key top center; 
set xlabel "Size of vector or matrix [N]";
set grid; 
set ylabel "Time of execution [ms]"; 
plot "results_ddot.txt" u 1:2 smooth bezier title "DDOT", "results_dgemv.txt" u 1:2 smooth bezier title "DGEMV", "results_dgemm.txt" u 1:2 smooth bezier title "DGEMM"




