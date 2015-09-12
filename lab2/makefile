

make:
	gcc zadanie2.c `pkg-config --cflags --libs gsl` -o zad
	./zad2
	clear

gnuplot_interpolation:
	gnuplot -e "plot \"dane.txt\" w points pointsize 5, \"custom_lagrange.txt\" w points pointtype 1 pointsize 2, \"custom_newton.txt\" w points pointtype 4 pointsize 2, \"gsl_polynomial.txt\" w points pointtype 6 pointsize 2" -p

gnuplot_times:
	gnuplot -e "plot \"time_lagrange.txt\" with lines, \"time_newton.txt\" with lines, \"time_gsl.txt\" w lines" -p