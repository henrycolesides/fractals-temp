#include "FPToolkit.c"

double x,y ;

void scale(double sx, double sy)
{
  x = sx*x ;
  y = sy*y ;
}

void translate(double dx, double dy)
{
  x = x + dx ;
  y = y + dy ;
}

void rotate(double a)
{
  double temp ;
  temp = x*cos(a) - y*sin(a) ;
  y    = x*sin(a) + y*cos(a) ;
  x = temp ;
}

int main()
{

  double swidth, sheight ;
  swidth = 600 ;
  sheight = 600 ;

  G_init_graphics(swidth,sheight) ;
  
  x = 0 ;
  y = 0 ;

  int k ;
  double r ;

  for(k=0;k<200000;k++) {

    r = drand48() ;

    if(r < 0.25) {
      //rule 1
      scale(0.5 , 0.5) ;
      G_rgb(1, 0, 0);
    }
    else if(r < 0.5) {
      //rule 2
      scale(0.5 , 0.5) ;
      translate(0.5 , 0) ;
      G_rgb(0, 1, 0);
    }
    else if(r < 0.75) {
      //rule 3
      scale(0.5 , 0.5) ;
      translate(0 , 0.5) ;
      G_rgb(0, 0, 1);
    }
    else {
      //rule 4
      scale(0.5 , 0.5) ;
      translate(0.5 , 0.5) ;
      G_rgb(1, 0, 1);
    }

//    G_rgb(0,1,0) ;
    G_point(x*swidth , y*sheight) ;
    
  }

  G_wait_key() ;
  
}
