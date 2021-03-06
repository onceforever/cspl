
// gcc -I../../CSPL/Array -L../../ Array1.c -lm -Wall -lCSPL -o Array1
// install_name_tool -add_rpath ../../ Array1


#include <stdio.h>

#include "CSPL_Array.h"

int main(void) {
  double dat1[5] = {1, 2, 5, 7, 8};
  double dat2[5] = {2, 3, 4, 6, 5};
  double dtmp[5];
  double v1,v2;
  long i;

  printf("\nArray1\tArray2\n");
  for (i=0;i<5;i++) {
    printf("%lf\t", dat1[i]);
    printf("%lf\n", dat2[i]);
  }

  
  printf("Min\n");
  v1 = CSPL_Array_min(dat1, 5);
  v2 = CSPL_Array_min(dat2, 5);
  printf("%lf\t%lf\n", v1, v2);

  printf("Max\n");
  v1 = CSPL_Array_max(dat1, 5);
  v2 = CSPL_Array_max(dat2, 5);
  printf("%lf\t%lf\n", v1, v2);

  printf("Range\n");
  v1 = CSPL_Array_range(dat1, 5);
  v2 = CSPL_Array_range(dat2, 5);
  printf("%lf\t%lf\n", v1, v2);
  

  CSPL_Array_add(dat1, dat2, dtmp, 5);
  printf("\nSum is:\n");
  for (i=0;i<5;i++) 
    printf("dtmp[%ld]=%lf\n", i, dtmp[i]);

  CSPL_Array_subtract(dat1, dat2, dtmp, 5);
  printf("\nDifference is:\n");
  for (i=0;i<5;i++) 
    printf("dtmp[%ld]=%lf\n", i, dtmp[i]);

  CSPL_Array_multiply(dat1, dat2, dtmp, 5);
  printf("\nProduct is:\n");
  for (i=0;i<5;i++) 
    printf("dtmp[%ld]=%lf\n", i, dtmp[i]);

  CSPL_Array_divide(dat1, dat2, dtmp, 5);
  printf("\nQuotient is:\n");
  for (i=0;i<5;i++) 
    printf("dtmp[%ld]=%lf\n", i, dtmp[i]);

  CSPL_Array_scale(dat1, 1, 10, 5);
  printf("\nScaled to [1,10] gives:\n");
  for (i=0;i<5;i++) 
    printf("dat1[%ld]=%lf\n", i, dat1[i]);

  CSPL_Array_logscale(dat2, 1, 10, 5);
  printf("\nLog Scaled to [1,10] gives:\n");
  for (i=0;i<5;i++) 
    printf("dat2[%ld]=%lf\n", i, dat2[i]);

  return(0);
}






