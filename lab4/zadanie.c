#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>



void printX(int N, double *X){
	int i;
	for(i = 0; i < N; i++){
		printf("My x%i: %f\n", i, X[i]);
	}
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



void GSLlevel1(int N, FILE *output){
	int i;
  	gsl_vector *x = gsl_vector_alloc (N);
  	gsl_vector *y = gsl_vector_alloc (N);
  
	for (i = 0; i < N; i++)
	{
	  	gsl_vector_set (x, i, (((double)(rand()))/((double)rand())));
	  	gsl_vector_set (y, i, (((double)(rand()))/((double)rand())));
	}

	double *result = malloc(sizeof(double));
	fprintf(output, "%i, A1, ", N);
	struct timeval start, end;

  	gettimeofday(&start, NULL);
		gsl_blas_ddot(x,y,result);
  	gettimeofday(&end, NULL);
  	fprintf(output, "%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));

	// for(i = 0; i < N; i++){
	// 	printf("GSL x%i: %g\n", i, gsl_vector_get(x, i));
	// 	printf("GSL y%i: %g\n", i, gsl_vector_get(y, i));
	// }
	// printf("Iloczyn skalarny: %f\n", result);

	gsl_vector_free (x);
	gsl_vector_free (y);
	return;
}

void GSLlevel2(int N, FILE *output){
	gsl_matrix *m = gsl_matrix_alloc(N, N);
	// double *square = malloc(sizeof(double * N * N));
	// generateSquare(N, square);
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			gsl_matrix_set(m, i, j, (((double)(rand()))/((double)rand())));
		}
	}
	double alfa = ((double)(rand()))/((double)rand());
	double beta = ((double)(rand()))/((double)rand());
	gsl_vector *x = gsl_vector_alloc (N);
  	gsl_vector *y = gsl_vector_alloc (N);
  	for (i = 0; i < N; i++)
	{
	  	gsl_vector_set (x, i, (((double)(rand()))/((double)rand())));
	  	gsl_vector_set (y, i, (((double)(rand()))/((double)rand())));
	}
	fprintf(output, "%i, A2, ", N);
	struct timeval start, end;

  	gettimeofday(&start, NULL);
		gsl_blas_dgemv(CblasNoTrans, alfa, m, x, beta, y);
  	gettimeofday(&end, NULL);
  	fprintf(output, "%ld\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));

	gsl_vector_free(x);
	gsl_vector_free(y);
	gsl_matrix_free(m);
	return;
}

void GSLlevel3(int N, FILE *output){
	gsl_matrix *A = gsl_matrix_alloc(N, N);
	gsl_matrix *B = gsl_matrix_alloc(N, N);
	gsl_matrix *C = gsl_matrix_alloc(N, N);
	// double *square = malloc(sizeof(double * N * N));
	// generateSquare(N, square);
	int i, j;
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			gsl_matrix_set(A, i, j, (((double)(rand()))/((double)rand())));
			gsl_matrix_set(B, i, j, (((double)(rand()))/((double)rand())));
		}
	}
	double alfa = ((double)(rand()))/((double)rand());
	double beta = ((double)(rand()))/((double)rand());
		fprintf(output, "%i, A3, ", N);
		clock_t startTime = clock();
		gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, alfa, A, B, beta, C);
		fprintf(output, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));
	gsl_matrix_free(A);
	gsl_matrix_free(B);
	return;
}


int main(int argc, char* argv[]){
    int n = atoi(argv[1]);
    FILE *output;
    output = fopen("data.txt", "a");

    int i;

    for(i = 3; i < n; i++){
		GSLlevel1(i, output);
    }
    for(i = 3; i < n; i++){
		GSLlevel2(i, output);
    }
  //   for(i = 3; i < 500; i++){
		// GSLlevel3(i, output);
  //   }
	return 0;
}
