// 4/1/24 In-class 
// Dr. Ely's introduction to writing out own programs with FPToolkit

#include "FPToolkit.c"

int main(int argc, char *argv[])
{
	float n = 0.0;
	float width = 600.0;
	float height = 600.0;
	float wstep = 0.0;	
	float hstep = 0.0;	

	if(argc < 2) return 0;

	n = atof(argv[1]);
	if(n < 1) return 0;

	wstep = width / n;
	hstep = height / n;
   	G_init_graphics (width, height);
	
	G_rgb(0.9, 0.9, 0.9);
	G_clear();
		
	G_rgb(0.0, 0.0, 0.0);
	//G_line(0, 0, width-1, height-1);
	for(float i = 0.0; i < n; ++i)
	{	
   		G_line(i * wstep, 0, i * wstep, height - 1);
   		G_line(0, i * hstep, width - 1, i * hstep);
	}
	G_line(0, height - 1, width - 1, height - 1);
	G_line(width - 1, 0, width - 1, height - 1);


	G_wait_key();
}
