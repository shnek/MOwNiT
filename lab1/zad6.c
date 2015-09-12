#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

int
main (void)
{
  int i;
  double xi, yi, x[9], y[9];
  FILE *input, *output;
  input=fopen("zad6wartosci.txt","w");
  output=fopen("zad6spline.txt","w");
//  printf ("#m=0,S=2\n");


  for (i = 0; i < 9; i++)
    {
      x[i] = i * i;
      y[i] = i;
      fprintf (input,"%g %g\n", x[i], y[i]);
    }

//  printf ("#m=1,S=0\n");

  {
    gsl_interp_accel *acc 
      = gsl_interp_accel_alloc ();
    gsl_spline *spline 
      = gsl_spline_alloc (gsl_interp_cspline,9);

    gsl_spline_init (spline, x, y, 9);

    for (xi = x[0]; xi < x[8]; xi += 0.01)
      {
        yi = gsl_spline_eval (spline, xi, acc);
        fprintf (output,"%g %g\n", xi, yi);
      }
    gsl_spline_free (spline);
    gsl_interp_accel_free(acc);
  }
  return 0;
}

