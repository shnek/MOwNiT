#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <time.h>


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
	fprintf(output, "%i, ", N);
	clock_t startTime = clock();
		gsl_blas_ddot(x,y,result);
	fprintf(output, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));


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
	fprintf(output, "%i, ", N);
	clock_t startTime = clock();
		gsl_blas_dgemv(CblasNoTrans, alfa, m, x, beta, y);
	fprintf(output, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));
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
	fprintf(output, "%i, ", N);
		clock_t startTime = clock();
		gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, alfa, A, B, beta, C);
		fprintf(output, "%f\n", 1000*(double)(clock()-startTime)/(double)(CLOCKS_PER_SEC));
	gsl_matrix_free(A);
	gsl_matrix_free(B);
	return;
}


int main(int argc, char* argv[]){
    char* number = argv[1];
    int N = atoi(number);
    FILE *output1, *output2, *output3;
    output1 = fopen("results_ddot.txt", "w+");
    output2 = fopen("results_dgemv.txt", "w+");
   	output3 = fopen("results_dgemm.txt", "w+");
    int i;

    for(i = 3; i < 10000; i++) GSLlevel1(i, output1);
    for(i = 3; i < 1000; i++) GSLlevel2(i, output2);
    for(i = 3; i < 500; i++) GSLlevel3(i, output3);
	return 0;
}