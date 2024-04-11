
#include "FPToolkit.c"


int triangle(float points[6], int depth, int max, float rpoint[2]);
int main(int argc, char * argv[])
{
	int size = 0;
	if(argc < 2) return 0;
	else size = atoi(argv[1]);
	if(size > 15) 
	{
		fprintf(stderr, "%d is too large!\nLimit 15\n", size);
		return 0;
	}

	float width = 800.0;
	float height = 800.0;
	G_init_graphics(width, height);
	G_rgb(0.8, 0.8, 0.8);
	G_clear();

	G_rgb(0.0, 0.0, 0.0);
	
	float start_points[6] = {400.0, 600.0, 200.0, 200.0, 600.0, 200.0};
	float rpoint[2] = {400.0, 600.0};
	float angle = 0.0;
	while(1)
	{
		G_wait_key();
		
		angle += 0.025;
		rpoint[0] = 400 * cos(angle) + (width/2);
		rpoint[1] = 400 * sin(angle) + (height/2);
		
		G_rgb(0.8, 0.8, 0.8);
		G_clear();
		
		G_rgb(0.0, 0.0, 0.0);
		//start_points[0] = rpoint[0];
		//start_points[1] = rpoint[1];
		//G_triangle(rpoint[0], rpoint[1], 200.0, 200.0, 600.0, 200.0); 
		G_triangle(400.0, 600.0, 200.0, 200.0, 600.0, 200.0); 
		triangle(start_points, 0, size, rpoint);
	}
	G_wait_key();
}

int triangle(float points[6], int depth, int max, float rpoint[2])
{
	if(depth > max) return 0;
	float mx1 = (points[0] + points[2]) / 2;
	float mx2 = (points[0] + points[4]) / 2;
	float mx3 = (points[2] + points[4]) / 2;
	float my1 = (points[1] + points[3]) / 2;
	float my2 = (points[1] + points[5]) / 2;
	float my3 = (points[3] + points[5]) / 2;
	//G_line(mx1, my1, rpoint[0], rpoint[1]);
	//G_line(mx2, my2, rpoint[0], rpoint[1]);
	//G_line(mx3, my3, rpoint[0], rpoint[1]);
	float d1 = sqrt(pow((mx1 + rpoint[0]), 2) + pow((my1 + rpoint[1]), 2));
	G_rgb(mx1 / d1, my1 / d1, my2 / d1);	
	G_line(mx1, my1, mx2, my2);
	G_line(mx1, my1, rpoint[0], rpoint[1]);

	d1 = sqrt(pow((mx3 + rpoint[0]), 2) + pow((my3 + rpoint[1]), 2));
	G_rgb(mx3 / d1, my3 / d1, my1/d1);
	G_line(mx1, my1, mx3, my3);
	G_line(mx2, my2, rpoint[0], rpoint[1]);
	
	d1 = sqrt(pow((mx2 + rpoint[0]), 2) + pow((my2 + rpoint[1]), 2));
	G_rgb(mx2 / d1, my2 / d1, my3/d1);
	G_line(mx2, my2, mx3, my3);
	G_line(mx3, my3, rpoint[0], rpoint[1]);

	float p1[6] = {points[0], points[1], mx1, my1, mx2, my2};
	float p2[6] = {points[2], points[3], mx1, my1, mx3, my3};
	float p3[6] = {points[4], points[5], mx2, my2, mx3, my3};
	triangle(p1, depth + 1, max, rpoint);
	triangle(p2, depth + 1, max, rpoint);
	triangle(p3, depth + 1, max, rpoint);
	return 0;
}
