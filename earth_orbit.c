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
	
	float moon_radius = 20.0;
	float moon_angle = 0.0;
	
	float earth_x = 0.0;
	float earth_y = 0.0;

	G_rgb(0.0, 0.0, 1.0);
	while(1)
	{
		angle += 0.025;
		moon_angle += 0.314;

		G_rgb(0.0, 0.0, 0.0);
		G_clear();
		
		G_rgb(0.5, 0.5, 0.0);
		G_fill_circle(width / 2, height / 2, radius);
		
		G_rgb(0.0, 0.0, 1.0);
		earth_x = (radius + 100) * cos(angle) + (width/2);
		earth_y = ((((radius + 100) * sin(angle)) / 2.5) + (height/2));
		G_fill_circle(earth_x, earth_y, 10.0 - (2.0 * sin(angle)));

		G_rgb(0.5, 0.5, 0.5);
		G_fill_circle(earth_x + (moon_radius * cos(moon_angle)), earth_y + (moon_radius * sin(moon_angle)), 5);
		
		if(earth_y > height / 2)
		{
			G_rgb(0.5, 0.5, 0.0);
			G_fill_circle(width / 2, height / 2, radius);
		}
		G_wait_key();
	}
	G_wait_key();
}
