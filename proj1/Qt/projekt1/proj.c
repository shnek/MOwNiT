#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>

#include "functions.c"


FILE *output;

void printResults(double x, double result, double error, double real, double nodif){
	fprintf(output,"%f,%f,%f,%f,%f\n",x,nodif,result,real,error);
}

void compute(double start, double end, int func){
    gsl_function F;
    gsl_function G;
    double result, abserr;
    switch(func){
    	case 1:
    		F.function = edox;
    		G.function = edox;
    		break;
    	case 2:
    		F.function = xsquare;
    		G.function = xsquareprim;
    		break;
    	case 3:
    		F.function = lnx;
    		G.function = oneoverx;
    		break;
    	case 4:
    		F.function = polynomial;
    		G.function = polynomialdx;
    		break;
    	case 5:
    		break;
    	case 6:
    		break;
    	case 7:
    		break;
    	case 8:
    		break;
    	case 9:
    		break;
    	default:
    		return;
    }

    F.params = 0;
    int i;
    for(i = start; i < end; i = i + 1){
        gsl_deriv_central(&F, i, 1e-8, &result, &abserr);
    	printResults(i, result, abserr, G.function(i, NULL), F.function(i,NULL));
    }
	return;
}

int run(int start, int end, int fno){

	output = fopen("data.txt", "w");
	fprintf(output, "X,F,Y,R,Err\n");

	compute(start, end, fno);
	return 0;
}
