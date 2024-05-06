
#include "FPToolkit.c"

int main()
{
	float width = 1000.0;
	float height = 1000.0;

	G_init_graphics(width, height);

	G_rgb(0.0, 0.0, 0.0);
	G_clear();

	double p1[2], p2[2], p3[2], p4[2];
	G_rgb(0.9, 0.9, 0.9);

	G_wait_click(p1);
	G_fill_circle(p1[0], p1[1], 2);

	G_wait_click(p2);
	G_fill_circle(p2[0], p2[1], 2);
	
	G_line(p1[0], p1[1], p2[0], p2[1]);


	float length = sqrt(pow((p1[0] - p2[0]), 2) + pow((p1[1] - p2[1]), 2));
	float slope = (p1[1] - p2[1]) / (p1[0] - p2[0]);
	float angle = atan(-1 / slope);
	float scale = 0.25;	
	if(slope < 0)
	{
		p3[0] = p1[0] + (scale * length * cos(angle));
		p3[1] = p1[1] + (scale * length * sin(angle));
		p4[0] = p2[0] + (scale * length * cos(angle));
		p4[1] = p2[1] + (scale * length * sin(angle));
	}
	else
	{
		p3[0] = p1[0] + (scale * length * -cos(angle));
		p3[1] = p1[1] + (scale * length * -sin(angle));
		p4[0] = p2[0] + (scale * length * -cos(angle));
		p4[1] = p2[1] + (scale * length * -sin(angle));
	}
	
	G_fill_circle(p3[0], p3[1], 2);
	G_fill_circle(p4[0], p4[1], 2);
	
	G_line(p1[0], p1[1], p3[0], p3[1]);
	G_line(p2[0], p2[1], p4[0], p4[1]);
	G_line(p3[0], p3[1], p4[0], p4[1]);
	G_wait_key();
}
