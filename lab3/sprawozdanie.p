set autoscale


set key top center; 
set xlabel "Amount of equations [N]"; 
set ylabel "Time of execution [s]"; 
set grid; 
plot "results_myLU.txt" u 1:2 smooth bezier title "My solver", "results_GSL.txt" u 1:2 smooth bezier title "GSL solver"




set key top center; 
set xlabel "Size of vector or matrix [N]"; 
set grid; 
set ylabel "Time of execution [s]"; 
plot "results_ddot.txt" u 1:2 smooth bezier title "DDOT"