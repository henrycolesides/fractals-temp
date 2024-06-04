#include <stdio.h>
#include <math.h>
#include <complex.h>


int main()
{
  int n,k ;
  double cx,cy ;
  complex c,z ;

  printf("enter the real and imaginary parts of the complex constant : ") ;
  scanf("%lf %lf",&cx,&cy) ;

  printf("how many reps ? ") ;
  scanf("%d",&n) ;
  
  c = cx + cy*I ;
  
  z = 0 ;
  for (k = 0 ; k < n ; k++) {
    printf("%3d : <%lf %lf>\n",k,creal(z), cimag(z)) ;
    z = z*z + c ;
  }    
  printf("%3d : <%lf %lf>\n",k,creal(z), cimag(z)) ;
  
}
