/*
Assuming Ubuntu:

1) Install imagemagick : sudo apt-get install imagemagick
2) Install ffmpeg :      sudo apt-get install ffmpeg
3) Compile and run this program. Hold down any key in the 
   graphics window until the program finishes.  
   Many numbered .bmp files should now be created.
4) Type : convert simple*.bmp simple.mpg
5) You now have a .mpg movie file that should run in any 
   movie player on your computer.  I suggest using VLC.

*/

#include "FPToolkit.c"

int main()
{
  int size = 600 ;
  char fname[200] ;
  double rmax,r ;
  int count ;

  G_init_graphics(size,size) ;

  rmax = 0.4*size ;

  count = 0 ;
  for (r = 10 ; r < rmax ; r++) {
    
    G_rgb(0.15,0.15,0.15) ;
    G_clear() ;

    G_rgb(r/rmax, 0.5, 0.5) ;
    G_fill_circle(0.5*size, 0.5*size, r) ;
    
    G_wait_key() ;
    
    sprintf(fname, "simple%04d.bmp",count) ;
    G_save_to_bmp_file(fname) ;

    count++ ;
  }

}

