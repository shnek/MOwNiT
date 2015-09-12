//#include <config.h>
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
  double xi, yi, x[10], y[10];
  FILE *input, *output;
  input=fopen("wartosci.txt","w");
  output=fopen("inter_cspline_periodic.txt","w");
//  printf ("#m=0,S=2\n");

  for (i = 0; i < 10; i++)
    {
      x[i] = i + 0.5 * sin (i);
      y[i] = i + cos (i * i);
      fprintf (input,"%g %g\n", x[i], y[i]);
    }

//  printf ("#m=1,S=0\n");

  {
    gsl_interp_accel *acc 
      = gsl_interp_accel_alloc ();
    gsl_spline *spline 
      = gsl_spline_alloc (gsl_interp_cspline_periodic,10);

    gsl_spline_init (spline, x, y, 10);

    for (xi = x[0]; xi < x[9]; xi += 0.01)
      {
        yi = gsl_spline_eval (spline, xi, acc);
        fprintf (output,"%g %g\n", xi, yi);
      }
    gsl_spline_free (spline);
    gsl_interp_accel_free(acc);
  }
  return 0;
}

