#include<stdio.h>


int main(){
	int i = 0;
	double d = 0.01;
	float f = 0.01;

	for(i = 0; i < 40; i++){
		printf("Step: %i, Double: %f, Float: %f\n", i, d, f);
		d = d + 3.0 * d * (1 - d);
		f = f + 3.0 * f * (1 - f);
	}
	
	return 0;
}