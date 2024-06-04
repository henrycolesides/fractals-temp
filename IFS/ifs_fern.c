#include "FPToolkit.c"

//Lifted from the old falling stickman code :
//double x[13] = {175,225,225,300,225,225,250,200,150,175,175,100,175} ;
//double y[13] = {300,300,250,225,225,200,100,175,100,200,225,225,250} ;
//double n = 13 ;


double x[1] = {0.0} ;
double y[1] = {0.0} ;
double n = 1 ;




void translate (double dx, double dy)
// leave the translation in the [0,1]x[0,1] universe
// but simply scale the point when you plot it
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = x[i] + dx ;
     y[i] = y[i] + dy ;
     i = i + 1 ;
  }
}




void scale (double sx, double sy)
{
  int i ;

  i = 0 ;
  while (i < n) {
     x[i] = sx * x[i] ;
     y[i] = sy * y[i] ;
     i = i + 1 ;
  }
}




void rotate (double degrees)
{
  double radians,c,s,t ;
  int i ;
  
  radians = degrees*M_PI/180.0 ;
  c = cos(radians) ;
  s = sin(radians) ;

  i = 0 ;
  while (i < n) {
      t    = x[i]*c - y[i]*s ;
      y[i] = y[i]*c + x[i]*s ;
      x[i] = t ;
      i = i + 1 ;
  }
}



//////////////////////////////////////////////////

void diagonal_line(double r)
{
   if (r < 0.5) {
     scale(0.5, 0.5) ;

   } else {
     scale(0.5, 0.5) ;
     translate(0.5, 0.5) ;
   }
}



void  filled_triangle (double r)
{
   if (r < 0.25) {
     scale(0.5, 0.5) ;

   } else if (r < 0.50) {
     scale(0.5, 0.5) ;
     translate(0.5, 0.0) ;

   } else if (r < 0.75) {
     scale(0.5, 0.5) ;
     translate(0.0, 0.5) ;

   } else {
     scale(0.5, 0.5) ;
     rotate(180) ;
     translate(0.5, 0.5) ;
   }
}



void  sierpinski_gasket (double r)
{
   if (r < 0.333) {
     scale(0.5, 0.5) ;

   } else if (r < 0.666) {
     scale(0.5, 0.5) ;
     translate(0.5, 0.0) ;

   } else {
     scale(0.5, 0.5) ;
     translate(0.0, 0.5) ;
   }
}





void koch_curve (double r)
{
   if (r < 0.25) {
     scale(0.3333, 0.3333) ;

   } else if (r < 0.50) {
     scale(0.3333, 0.3333) ;
     rotate(60.0) ;
     translate(0.3333, 0.0) ;

   } else if (r < 0.75) {
     scale(0.3333, 0.3333) ;
     rotate(-60.0) ;
     translate(0.5, 0.2886) ;

   } else {
     scale(0.3333, 0.3333) ;
     translate(0.6666, 0.0) ;
   }

}


void fern(double r)
{

   if (r < 0.01) {
     translate(-0.5,0.0) ;
     scale(0.0, 0.16) ;
     translate(0.5,0.0) ;
     G_rgb(0.7, 0.3, 1.0) ;

   } else if (r < 0.08) {
     translate(-0.5,0.0) ;
     rotate(-3.45) ;
     scale(0.30, 0.34) ;
     rotate(52.85) ;
     translate(0.0, 0.160) ;
     translate(0.5,0.0) ;
     G_rgb(1.0, 0.0, 0.0) ;

   } else if (r < 0.15) {
     translate(-0.5,0.0) ;
     rotate(20.82) ;
     scale(0.29, -0.38) ;
     rotate(146.65) ;
     translate(0.0, 0.044) ;
     translate(0.5,0.0) ;
     G_rgb(1.0, 0.8, 0.0) ;

   } else {
     translate(-0.5,0.0) ;
     scale(0.85, 0.85) ;
     rotate(-2.69) ;
     translate(0.0, 0.160) ;
     translate(0.5,0.0) ;
     G_rgb(0.0, 0.8, 0.3) ;
   }

}


int main() 
{
 double size,n,j,r ;
 
 size = 1000 ;
 // G_choose_repl_display() ; size = 600 ;
 G_init_graphics(size, size) ;
 G_rgb(0, 0, 0) ;
 G_clear() ;


 G_rgb(1,0,0.2) ;
 srand48(200) ;

 n = 2000000 ;
 
 j = 0 ;
 while (j < n) {

   r = drand48() ;
   //   diagonal_line(r) ;
   //   filled_triangle(r) ;
   //   sierpinski_gasket(r) ;
   //   koch_curve(r) ;
   fern(r) ;
   
   G_point (x[0]*size, y[0]*size) ;
   //   G_fill_circle (x[0]*size, y[0]*size, 1) ;
   //   G_wait_key() ;

   j=j+1 ;
 }

 G_wait_key() ;
 //G_save_to_bmp_file("fern.bmp") ;
}


