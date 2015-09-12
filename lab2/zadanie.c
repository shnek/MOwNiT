#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include <time.h>

const int max = 100;
const int min = 3;


void generateData(int N, double *x, double* y){
	srand(time(NULL));
	int a,b;
	int i;
	for(i = 0; i < N; i ++){
		a = rand();
		b = rand();
		if(i == 0){
			x[i] = (a * 1.0)/ (b * 1.0);
		}else{
			x[i] = x[i-1] + (a*1.0)/(b*1.0);
		}
		a = rand();
		b = rand();
		y[i] = (a * 1.0) / (b * 1.0);
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////LAGRANGE////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void L(int N, double *Lu, double *x, int u){
	double mianownik = 1;
	int i;
	for(i = 0; i < N; i++){
		if(i != u) mianownik = mianownik * (x[u] - x[i]);
		if(i != u){
			int j;
			for(j = N-1; j > 0; j--){
				Lu[j] += Lu[j-1];
				Lu[j-1] *= -x[i];
			}
		}
	}
	for(i = 0; i < N; i++){
		Lu[i] /= mianownik;
	}
	return;
}
	
void lagrange(int N, double *Lg, double *x, double *y){
	int i;
	double Lu[N];
	for(i = 0; i < N; i++){
		Lg[i] = 0;
		Lu[i] = 0;
	}
	for(i = 0; i < N; i++){
		int j;
		for (j = 0; j < N; j++)
		{
			Lu[j] = 0;
		}
		Lu[0] = 1;
		L(N, Lu, x, i);
		for(j = 0; j < N; j++){
			Lg[j] += y[i]*Lu[j];
		}
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////WIELOMIAN///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

double Polynomial(int N, double *Wielomian, double a){
	int i;
	double temp = 1.0;
	double result = 0.0;
	for(i = 0; i < N; i++){
		result += temp * Wielomian[i];
		temp *= a;
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////NEWTON/////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

void nadd(int N, double *Nt, double *iks, double ai){
	int i;
	for(i = 0; i < N; i++){
		Nt[i] += ai*iks[i];
	}
	return;
}

double newton(int N, double *Nt, double *x, double *y){
	int i;
	double iks[N];
	for(i = 0; i < N; i++){
		Nt[i] = 0;
		iks[i] = 0;
	}
	iks[0] = 1;
	Nt[0] = y[0];
	double ai;

	for(i = 1; i < N; i++){
		int j;
		for(j = N-1; j > 0; j--){
			iks[j] += iks[j-1];
			iks[j-1] *= -x[i-1];
		}
		ai = (y[i] - Polynomial(N, Nt, x[i]))/(Polynomial(N, iks, x[i]));
		// printf("ai: %f, y[i] = %f, rmian = %f, Licznik = %f\n", ai, y[i], Polynomial(N, Nt, x[i]), Polynomial(N, iks, x[i]));
		// for(j = 0; j < N; j++){
		// 	printf("j: %i, iks: %f, Nt: %f \n", j, iks[j], Nt[j]);
		// }
		nadd(N, Nt, iks, ai);
	}
	// int j;
	// for(j = 0; j < N; j++){
	// 		printf("j: %i, iks: %f, Nt: %f \n", j, iks[j], Nt[j]);
	// 	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////MAIN//////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
	FILE *input, *output, *output2, *output3, *time1, *time2, *time3;
  	time1=fopen("time_lagrange.txt", "w");
  	time2=fopen("time_newton.txt", "w");
  	time3=fopen("time_gsl.txt", "w");

	int N;
	clock_t startTime = clock();
	for(N = min; N < max; N++){
	  	input=fopen("dane.txt","w");
	  	output=fopen("custom_lagrange.txt","w");
	  	output2=fopen("gsl_polynomial.txt","w");
	  	output3=fopen("custom_newton.txt", "w");
		fprintf(time1, "%i, ", N);
		fprintf(time2, "%i, ", N);
		fprintf(time3, "%i, ", N);
		double x[N];
		double y[N];
		int i;

		generateData(N, x, y);

		for(i = 0; i < N; i ++){
			fprintf (input,"%g %g\n", x[i], y[i]);
		}

		double Lg[N];
		startTime = clock();
		lagrange(N, Lg, x, y);
		fprintf(time1, "%f\n", (double)(clock() - startTime)/(double)(CLOCKS_PER_SEC));

		double Nt[N];
		
		startTime = clock();
		newton(N, Nt, x, y);
		fprintf(time2, "%f\n", (double)(clock() - startTime)/(double)(CLOCKS_PER_SEC));
		// for(i = 0; i < N; i++){
		// 	printf("%f\n", Nt[i]);
		// }

		double xi, yi;
		{
	    startTime = clock();
	    gsl_interp_accel *acc = gsl_interp_accel_alloc ();
	    gsl_spline *spline = gsl_spline_alloc (gsl_interp_polynomial,N);
	    gsl_spline_init (spline, x, y, N);
	    fprintf(time3, "%f\n", (double)(clock() - startTime)/(double)(CLOCKS_PER_SEC));

	    for (xi = x[0]; xi < x[N-1]; xi += 0.01)
	      {
	        yi = gsl_spline_eval (spline, xi, acc);
	        fprintf (output2,"%g %g\n", xi, yi);
	      }
	    gsl_spline_free (spline);
	    gsl_interp_accel_free(acc);
	  }

	  for(xi = x[0]; xi < x[N-1]; xi += 0.01){
	  	yi = Polynomial(N, Lg, xi);
	  	fprintf(output, "%g %g\n", xi, yi);
	  }

	  for(xi = x[0]; xi < x[N-1]; xi += 0.01){
	  	yi = Polynomial(N, Nt, xi);
	  	fprintf(output3, "%g %g\n", xi, yi);
	  }		
	  fclose(input);
	  fclose(output);
	  fclose(output2);
	  fclose(output3);
	}
	return 0;
}