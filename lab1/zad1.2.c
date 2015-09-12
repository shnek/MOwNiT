#include<stdio.h>


int main(){
	double da, db, dc;
	float fa, fb, fc;
	
	fa = 1.0;
	da = 1.0;
	while(fa + 1.0 > 1){
		fa = fa / 2.0;
	}
	printf("Metoda 1, float: %e\n", fa);
	while(da + 1.0 > 1){
		da = da / 2.0;
	}
	printf("Metoda 1, double: %e\n", da);

	fa = da = 1.0;
	fb = db = 3.0;
	fc = dc = 4.0;
	printf("Metoda 2, dobrze zadeklarowane zmienne, float: %e\n", fb * (fc/fb - fa) - fa);
	printf("Metoda 2, dobrze zadeklarowane zmienne, double: %e\n", db * (dc/db - da) - da);
	printf("Metoda 2, obliczanie \"w biegu\": %e\n", 3.0 * (4.0 / 3.0 - 1.0) - 1.0);

	return 0;
}