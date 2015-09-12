#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <stdlib.h>
#include <math.h>

double a,b,w;
double x0;
double z0;

int
func (double t, const double y[], double f[],
      void *params)
{
  f[0] = y[1];
  f[1] = y[0] - y[0]*y[0]*y[0] - a * y[0] + b * cos(w * t); 
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy, 
     double dfdt[], void *params)
{
  gsl_matrix_view dfdy_mat 
    = gsl_matrix_view_array (dfdy, 2, 2);
  gsl_matrix * m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, 0.0);
  gsl_matrix_set (m, 0, 1, 1.0);
  gsl_matrix_set (m, 1, 0, 1 - 3 * y[0] * y[0]);
  gsl_matrix_set (m, 1, 1, -a);
  dfdt[0] = 0.0;
  dfdt[1] = b * sin(w*t) * w;
  return GSL_SUCCESS;
}

int main(int argc, char* argv[]){
  int pno = atoi(argv[1]);
  double max_step = atof(argv[2]);
  a = atof(argv[3]);
  b = atof(argv[4]);
  w = atof(argv[5]);
  x0 = 0.0;
  z0 = 0.0;
  FILE *output = fopen("/C/results.txt", "w");
  fprintf(output, "t,x,y\n");
  double mu = 10;
  gsl_odeiv2_system sys = {func, jac, 2, &mu};

  gsl_odeiv2_driver * d = 
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
				  1e-6, 1e-6, 0.0);
  int i;
  double t = 0.0, t1 = max_step;
  double y[2] = { x0, z0 };

  for (i = 1; i <= pno; i++)
    {
      double ti = i * 1 / (max_step*1.0);
      int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

      if (status != GSL_SUCCESS)
	{
	  printf ("error, return value=%d\n", status);
	  break;
	}

      fprintf (output, "%f,%f,%f\n", t, y[0], y[1]);
    }

  gsl_odeiv2_driver_free (d);
  return 0;
}