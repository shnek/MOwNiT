#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>

int
main (void) 
{
  float f = 1.0/3.0;
  double d = 1.0/3.0;
  /*
  Mantysa nie jest w postaci znormalizowanej dla:
  a) float - liczby mniejszej od 1.0 * 10^-126
  b) double - liczby mniejszej od 1.0 * 10^-1022

  */



  double fd = f; /* promote from float to double */
  int i = 0;
  for(i = 0; i < 1010; i++){
     f = f / 2.0;
     d = d / 2.0;
     fd = fd / 2.0;
  }
  for (i = 0; i < 30; i++){
  printf(" f="); gsl_ieee_printf_float(&f); 
  printf("\n");

  printf("fd="); gsl_ieee_printf_double(&fd); 
  printf("\n");

  printf(" d="); gsl_ieee_printf_double(&d); 
  printf("\n");
    f = f / 2.0;
    d = d / 2.0;
    fd = fd / 2.0;
  }

  return 0;
}


