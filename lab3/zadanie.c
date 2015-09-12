#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <time.h>

void printX(int N, double *X){
	int i;
	for(i = 0; i < N; i++){
		printf("My x%i: %f\n", i, X[i]);
	}
	return;
}

void zeroTridag(int N, double *tridiag){
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < 3; j++){
			tridiag[i*3+j] = 0;
		}
	}
	tridiag[0] = tridiag[3*N-1] = NAN;
	return;
}

void generateSquare(int N, double *square){
	srand(time(NULL));
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			square[i*N+j] = (((double)(rand()))/((double)rand()));
		}
	}
	return;
}

void generateTridag(int N, double *tridiag){
	srand(time(NULL));
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < 3; j++){
			tridiag[i*3+j] = (((double)(rand()))/((double)rand()));
		}
	}
	tridiag[0] = tridiag[3*N-1] = NAN;
	return;
}
void generateX(int N, double *X){
	srand(time(NULL));
	int i;
	for(i = 0; i < N; i++){
		X[i] = (((double)(rand()))/((double)rand()));
	}
	return;
}

void printSquare(int N, double *square){
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%f ", square[i*N+j]);
		}
		printf("\n");
	}
}

void printTridag(int N, double *tridiag){
	int i,j;
	for(i = 0; i < N; i++){
		for(j = 0; j < 3; j++){
			printf("%f ", tridiag[i*3+j]);
		}
		printf("\n");
	}
	printf("\n");
	return;
}

void decompose(int N, double *A, double *L, double *U){
	int i;
	for(i = 0; i < N; i++){
		U[1 + 3*i] = A[1 + 3*i];
		L[1 + 3*i] = 1;
	}
	for(i = 0; i < N-1; i++){
		U[2+3*i] = A[2+3*i];
	}
	for(i = 1; i < N; i++){
		L[3*i] = A[3*i]/U[1 + 3*(i-1)];
		U[1 + 3*i] = A[1 + 3*i] - L[3*i]*A[2+3*(i-1)];
	}
	return;
}

void solveLU(int N, double *L, double *U, double *X){
	int i;
	for(i = 1; i < N; i++){
		X[i] -= X[i-1]*L[3*i];
	}
	for(i = N-1; i > 0; i--){
		X[i] /= U[1 + 3*i];
		// printf("X[i-1] (%f) -= U[2 + 3(i-1)] (%f) * X[i] (%f)\n", X[i-1], U[2+3*(i-1)], X[i]);
		X[i-1] -= U[2 + 3*(i-1)] * X[i];
		// printf("i: %i\n", i);
	}
	X[0] /= U[1];
	return;
}

void GSLRunMyProgram(int N, double *A, double *X, FILE *output){
	int i;
  	gsl_vector * x = gsl_vector_alloc (N);
  	gsl_vector * e = gsl_vector_alloc (N-1);
  	gsl_vector * d = gsl_vector_alloc (N);
  	gsl_vector * f = gsl_vector_alloc (N-1);
  	gsl_vector * b = gsl_vector_alloc (N);
  
	for (i = 0; i < N; i++)
	{
	  	gsl_vector_set (b, i, X[i]);
	  	gsl_vector_set (d, i, A[1 + 3*i]);
	}
	for(i = 0; i < N-1; i++){
		gsl_vector_set (e, i, A[2 + 3*i]);
		gsl_vector_set (f, i, A[3*(i+1)]);
	}

	clock_t startTime = clock();
	gsl_linalg_solve_tridiag(d, e, f, b, x);
	fprintf(output, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));

	// for(i = 0; i < N; i++){
	// 	printf("GSL x%i: %g\n", i, gsl_vector_get(x, i));
	// }

	gsl_vector_free (x);
	gsl_vector_free (e);
	gsl_vector_free (d);
	gsl_vector_free (f);
	gsl_vector_free (b);
	return;
}

void runMyProgram(int N, FILE *output1, FILE *output2){
	double A[3*N];
	double X[N];

	generateTridag(N, A);

	generateX(N, X);
	fprintf(output1, "%i, ", N);
	fprintf(output2, "%i, ", N);
	GSLRunMyProgram(N, A, X, output1);
	double L[3*N];
	double U[3*N];
	zeroTridag(N, L);
	zeroTridag(N, U);
	clock_t startTime = clock();
	decompose(N, A, L, U);
	solveLU(N, L, U, X);
	fprintf(output2, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));
	// printX(N, X);	

}

int main(int argc, char* argv[]){
    char* number = argv[1];
    int N = atoi(number);
    FILE *output1, *output2;
    output1 = fopen("results_GSL.txt", "w");
    output2 = fopen("results_myLU.txt", "w");
    int i;
    for(i = 3; i < N; i++){
    	runMyProgram(i, output1, output2);
    }
    

	return 0;
}