make:
	gcc zadanie.c `pkg-config --cflags --libs gsl` -o zad
	clear
	./zad 10000
	

test:
	gcc zadanie2.c `pkg-config --cflags --libs gsl` -o zadanie2
	clear
	./zadanie2 10000
	
	

gnuplot:
	gnuplot -e "set key top center; set xlabel \"Amount of equations [N]\"; set ylabel \"Time of execution [s]\"; set grid; plot \"results_myLU.txt\" u 1:2 smooth bezier title \"My solver\", \"results_GSL.txt\" u 1:2 smooth bezier title \"GSL solver\" " -p

wykres1:
	gnuplot -e "set key top center; set xlabel \"Size of vector or matrix [N]\"; set grid; set ylabel \"Time of execution [s]\"; plot \"results_ddot.txt\" with lines title \"DDOT\", \"results_dgemv.txt\" with lines title \"DGEMV\", \"results_dgemm.txt\" w lines title \"DGEMM\" " -p

	gnuplot -e "set key top center; set xlabel \"Size of vector or matrix [N]\"; set grid; set ylabel \"Time of execution [s]\"; plot \"results_ddot.txt\" with lines title \"DDOT\", \"results_dgemv.txt\" with lines title \"DGEMV\", \"results_dgemm.txt\" u 1:2 smooth bezier title \"DGEMM\" " -p

	gnuplot -e "set key top center; set xlabel \"Size of vector or matrix [N]\"; set grid; set ylabel \"Time of execution [s]\"; plot \"results_ddot.txt\" with lines title \"DDOT\", \"results_dgemv.txt\" with lines title \"DGEMV\" " -p
	
	gnuplot -e "set key top center; set xlabel \"Size of vector or matrix [N]\"; set grid; set ylabel \"Time of execution [s]\"; plot \"results_ddot.txt\" with lines title \"DDOT\", \"results_dgemv.txt\" u 1:2 smooth bezier title \"DGEMV\" " -p
	
	