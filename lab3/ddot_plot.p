set autoscale


set key top center; 
set xlabel "Size of vector or matrix [N]"; 
set grid; 
set ylabel "Time of execution [s]"; 
plot "results_ddot.txt" u 1:2 smooth bezier title "DDOT"