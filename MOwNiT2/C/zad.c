#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

FILE * output;
FILE * results;

struct quadratic_params
  {
    double a, b, c, d;
  };

double startpoint;
double precis;

double quadratic (double x, void *params);
double quadratic_deriv (double x, void *params);
void quadratic_fdf (double x, void *params, 
                    double *y, double *dy);

double
quadratic (double x, void *params)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;

  return ((a * x + b) * x + c) * x + d;
}

double
quadratic_deriv (double x, void *params)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;

  return ((3*a)*x + 2*b)*x + c;
}

void
quadratic_fdf (double x, void *params, 
               double *y, double *dy)
{
  struct quadratic_params *p 
    = (struct quadratic_params *) params;

  double a = p->a;
  double b = p->b;
  double c = p->c;
  double d = p->d;

  *y = ((a * x + b) * x + c) * x + d;
  *dy = ((3*a)*x + 2*b)*x + c;
}

void printFunction(gsl_function F, double start, double end, double step){
    double i;
    for(i = start; i <= end; i += step){
        fprintf(output,"%f,%f\n",i, GSL_FN_EVAL(&F,i));
    }
}


void bracketing(int fno, double start, double end, double a, double b, double c, double d){
    results = fopen("C/results.txt", "w");
    fprintf(results, "iter,lower,upper,root,err,err(est)\n");
    int status;
    int iter = 0, max_iter = 100;
    const gsl_root_fsolver_type *T;
    gsl_root_fsolver *s;
    double r = 0, r_expected = sqrt (5.0);
    double x_lo = start, x_hi = end;
    struct quadratic_params params = {a,b,c,d};
    gsl_function F;

    F.function = &quadratic;
    F.params = &params;

    if(fno == 1){
        T = gsl_root_fsolver_bisection;       
        // printf("jeden\n");
    }else if(fno == 2){
        T = gsl_root_fsolver_falsepos;
        // printf("dwa\n"); 
    }else if(fno == 3){
        T = gsl_root_fsolver_brent;
        // printf("trzy\n"); 
    }
    s = gsl_root_fsolver_alloc (T);
    gsl_root_fsolver_set (s, &F, x_lo, x_hi);


    do
    {
      iter++;
      status = gsl_root_fsolver_iterate (s);
      r = gsl_root_fsolver_root (s);
      x_lo = gsl_root_fsolver_x_lower (s);
      x_hi = gsl_root_fsolver_x_upper (s);
      status = gsl_root_test_interval (x_lo, x_hi,
                                       0, precis);

      // if (status == GSL_SUCCESS)
      //   printf ("Converged:\n");

      // printf ("%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
      //         iter, x_lo, x_hi,
      //         r, r - r_expected, 
      //         x_hi - x_lo);
      fprintf(results, "%i,%f,%f,%f,%f,%f\n", iter,x_lo,x_hi,r,r - r_expected,x_hi-x_lo);
    }
    while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fsolver_free (s);
    output = fopen("C/plot.txt", "w");
    fprintf(output, "X,Y\n");
    printFunction(F, start, end, (end-start)/100.0);

    fclose(output);
    fclose(results);
}
void derivatives(int fno, double start, double end, double a, double b, double c, double d){
    
    results = fopen("C/results.txt", "w");
    fprintf(results, "iter,root,err\n");
    int status;
    int iter = 0, max_iter = 50;
    const gsl_root_fdfsolver_type *T;
    gsl_root_fdfsolver *s;
    double x0, x = startpoint, r_expected = sqrt (5.0);
    gsl_function_fdf FDF;
    struct quadratic_params params = {a,b,c,d};
    gsl_function F;

    F.function = &quadratic;
    F.params = &params;

    FDF.f = &quadratic;
    FDF.df = &quadratic_deriv;
    FDF.fdf = &quadratic_fdf;
    FDF.params = &params;


     if(fno == 4){
        T = gsl_root_fdfsolver_newton;       
    }else if(fno == 5){
        T = gsl_root_fdfsolver_secant;
    }else if(fno == 6){
        T = gsl_root_fdfsolver_steffenson;
    }

    s = gsl_root_fdfsolver_alloc (T);
    gsl_root_fdfsolver_set (s, &FDF, x);

 
    do
    {
      iter++;
      status = gsl_root_fdfsolver_iterate (s);
      x0 = x;
      x = gsl_root_fdfsolver_root (s);
      status = gsl_root_test_delta (x, x0, 0, precis);

    fprintf(results, "%i,%f,%f\n", iter,x,x-x0);
    }
    while (status == GSL_CONTINUE && iter < max_iter);

    output = fopen("C/plot.txt", "w");
    fprintf(output, "X,Y\n");
    printFunction(F, start, end, (end - start)/100.0);
    fclose(output);
    fclose(results);
    gsl_root_fdfsolver_free (s);
}

int main(int argc, char* argv[]){
    if(argc!=10){
        printf("argno error\n");
        return 1;
    }
    precis = atof(argv[8]);
    startpoint = atof(argv[9]);
    // printf("%f, %f\n", precis, atof(argv[6]));
    if(atoi(argv[1]) < 4){
        bracketing(atoi(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
    }else{
        derivatives(atoi(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), atof(argv[6]), atof(argv[7]));
    }
    return 0;
}