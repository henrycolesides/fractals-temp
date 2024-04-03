// 4/3 Earth orbitting sun

#include "FPToolkit.c"

int main()
{
	float width = 600.0;
	float height = 600.0;
	G_init_graphics(width, height);

	G_rgb(0.0, 0.0, 0.0);
	G_clear();

	// Circle setup:
	float radius = 100.0;
	float angle = 0.0;

	G_rgb(0.0, 0.0, 1.0);
	while(1)
	{
		angle += 0.1;
		G_rgb(0.0, 0.0, 0.0);
		G_clear();
		
		G_rgb(0.5, 0.5, 0.0);
		G_fill_circle(width / 2, height / 2, radius);
		
		G_rgb(0.0, 0.0, 1.0);
		G_fill_circle((radius + 200) * cos(angle) + (width / 2), (radius + 200) * sin(angle) + (height / 2), 10);
		G_wait_key();
	}
	G_wait_key();
}
