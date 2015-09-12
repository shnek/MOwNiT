double xsquare(double x, void *params){
	return x*x;
}
double xsquareprim(double x, void *params){
	return 2*x;
}
double edox(double x, void *params){
	return pow(M_E, x);
}
double oneoverx(double x, void *params){
	if(x < 0.00001 && x > -0.00001) return 0;
	else return 1/x;
}
double lnx(double x, void *params){
	return log(x);
}
double polynomial(double x, void *params){
	return 4*x*x*x*x + 6*x*x*x - 3*x*x - 9*x + 8;
}
double polynomialdx(double x, void *params){
	return 16*x*x*x + 18*x*x -6*x - 9;
}
double nieroz(double x, void* params){
	if(x < 0)return -x; else return x;
}
double pochznieroz(double x, void *params){
	if(x < 0) return -1;
	else if (x == 0) return 0;
	else return 1;
}
double pochznieroz2(double x, void *params){
	return 0;
}

double nieroz2(double x, void* params){
	if(x < 0) return -x*(x-4);
	else if(x==0) return 1;
	else return 2;
}
double nieroz2prim(double x, void *params){
	if(x<0) return -2*x+4;
	else return 0;
}
