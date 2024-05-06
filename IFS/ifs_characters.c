// cc Koch.c -lm -lX11

#define PI 3.1415926535

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

  G_rgb(0,0,0) ;
  G_clear();
  G_rgb(1,0,1) ;

  //x = swidth ;
  //y = sheight ;

  for(k=0;k<2000000;k++) {

    r = drand48() ;
    
    //*
    //if(r < 0.25) {
    //  //rule 1
    //  scale(1.0/3.0 , 1.0/3.0) ;

    //  G_rgb(1,0,1) ;
    //}
    //else if(r < 0.5) {
    //  //rule 2
    //  scale(1.0/3.0 , 1.0/3.0) ;
    //  rotate(PI/3.0);
    //  translate(1.0/3.0, 0.0);

    //  G_rgb(1,1,0) ;
    //}
    //else if(r < 0.75) {
    //  //rule 3
    //  scale(1.0/3.0 , 1.0/3.0) ;
    //  rotate(PI/3.0 * -1.0);
    //  translate(1.0/2.0, (sqrt(3.0))/6.0);

    //  G_rgb(0,1,0) ;
    //}
    //else {
    //  //rule 4
    //  scale(1.0/3.0 , 1.0/3.0) ;
    //  translate(2.0/3.0, 0.0);

    //  G_rgb(0,0,1) ;
    //}
    ////*/
	if(r < 0.34)
    	{
		scale(0.2, 1.0);
		G_rgb(1, 0, 0);
	}
	else if(r < 0.67)
	{
//		translate(-0.2, -1.0);
//		rotate(PI/2.0);


		scale(0.6, 0.2);
		translate(0.2, 0.4);
		G_rgb(0, 1, 0);
	}
	else if(r < 1.0)
	{
		scale(0.2, 1.0);
		translate(0.8, 0.0);
		G_rgb(0, 0, 1);
	}
	//G_rgb(1,0,1) ;
	G_point(x*swidth/5.0 , y*sheight) ;
	//G_fill_circle(x*swidth , y*sheight, 3.0) ;
    
  }

  G_wait_key() ;
  
}
