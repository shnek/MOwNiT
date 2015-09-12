#include<stdio.h>
#include<math.h>

int main(){
	
	double a,b,c;
	a = 10000;
	b = 2000000;
	c = 100000000;

	double x1 = (-b + sqrt(b * b - 4 * a * c))/2 * a;
	double x2 = (-b - sqrt(b * b - 4 * a * c))/2 * a;

	printf("x1 = %f, x2 = %f\n", x1, x2);

	// Result: both x1 and x2 are about -1 * 10^10, where correct answer is -100, which is -1*10^2

	return 0;
}