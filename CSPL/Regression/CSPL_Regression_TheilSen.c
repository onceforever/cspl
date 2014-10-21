
#include <stdio.h>
#include <stdlib.h>

#include "CSPL_Regression.h"
#include "../Stats/CSPL_Stats.h"


/** compute the robust Theil-Sen linear regression coefficients.
 * Taken from Theil, H. (1950), A rank-invariant method of linear and polynomial regression analysis. 
 * I, II, III, Nederl. Akad. Wetensch., Proc. 53: 386–392, 521–525, 1397–1412, MR 0036489.
 * and Sen, Pranab Kumar (1968), Estimates of the regression coefficient based on Kendall's tau, 
 * Journal of the American Statistical Association 63: 1379–1389, JSTOR 2285891, MR 0258201.
 * 
 * This is done but finding all the slopes between each two-points, then the median
 * of the slopes is the returned slope. Then the intercept is the median of all the 
 * intercepts using the derived slope at each point. The return value is the R**2 as defined
 * as 1-SSres/SStot, where SSres is the residual sum of squares and SStot is the total 
 * sum of squares (proportional to the sample variance)
 *
 * TODO this should be updated to give a confidence interval via bootstrap!
 *
 * @param[in] x The *sorted* x points to use in the regression.
 * @param[in] y The y values of the points to use in the regression.
 * @param[in] n The length of the x,y arrays;
 * @param[out] slope The calculated slope.
 * @param[out] intercept The calculated intercept.
 * @return R-squared value, 1-SSres/SStot.
 */
double CSPL_Regression_TheilSen(double *x, double *y, long n, double *slope, double *intercept) {
  double *slopes;
  double *intercepts;
  double dx;
  unsigned long i, j, k;
  unsigned long combs;
  double SStot=0, SSres=0, ymean;
  
  combs = CSPL_Stats_combination(n, 2); // number of point combinations of n data points
      
  if (combs == 0) {
    fprintf(stderr, "CSPL_Regression_TheilSen: Data has one or zero length, no calcualtion posssible\n");
    return(-1); // do we want to do more?
  }
   
  slopes     = (double *)calloc(combs, sizeof(double));
  intercepts = (double *)calloc(combs, sizeof(double));

  k=0;
  for (i=0; i<n; i++) {
    for (j=0; j<i; j++) { // this is the over ahead
      dx = (x[j]-x[i]);
      slopes[k] = ((y[j]-y[i])/dx);
      k++;
    }
  }

  *slope = CSPL_Stats_median_quickselect(slopes, combs); 

  // now loop over all the points and get the intercepts
  for (i=0;i<n;i++) {
    intercepts[i] = y[i] - *slope*x[i];
  }
  *intercept = CSPL_Stats_median_quickselect(intercepts, n); 

  // figure out the R**2 value
  ymean = CSPL_Stats_mean(y, n);
  for (i=0; i<n; i++) {
    SStot += ((y[i]-ymean)*(y[i]-ymean));
    // need sum of squared residuals
    SSres += ((y[i]-*slope*x[i]+*intercept)*(y[i]-*slope*x[i]+*intercept));
  }
  
  free(slopes);
  free(intercepts);
  return(1-SSres/SStot);
}


