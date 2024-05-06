
#include "FPToolkit.c"
#include "koch_snowflake.c"

void triangle_wrapper(float points[6], int depth, int max);
int triangle(float points[6], int depth, int max);
//float rpoint[2]);
	//int main(int argc, char * argv[])
	//{
	//	int size = 0;
	//	if(argc < 2) return 0;
	//	else size = atoi(argv[1]);
	//	if(size > 15) 
	//	{
	//		fprintf(stderr, "%d is too large!\nLimit 15\n", size);
	//		return 0;
	//	}
        //
	//	float width = 1000.0;
	//	float height = 1000.0;
	//	G_init_graphics(width, height);
	//	G_rgb(0.8, 0.8, 0.8);
	//	G_clear();
        //
	//	G_rgb(0.0, 0.0, 0.0);
	//	
	//	float start_points[6] = {500.0, 950.0, 110.0, 275.0, 890.0, 275.0};
	//	triangle_wrapper(start_points, 0, size);	
	//	//G_triangle(400.0, 600.0, 200.0, 200.0, 600.0, 200.0); 
	//	//float start_points[6] = {400.0, 600.0, 200.0, 200.0, 600.0, 200.0};
	//	//float rpoint[2] = {400.0, 600.0};
	//	//float angle = 0.0;
	//	//while(1)
	//	//{
	//	//	G_wait_key();
	//	//	
	//	//	angle += 0.025;
	//	//	rpoint[0] = 400 * cos(angle) + (width/2);
	//	//	rpoint[1] = 400 * sin(angle) + (height/2);
	//	//	
	//	//	G_rgb(0.8, 0.8, 0.8);
	//	//	G_clear();
	//	//	
	//	//	G_rgb(0.0, 0.0, 0.0);
	//	//	//start_points[0] = rpoint[0];
	//	//	//start_points[1] = rpoint[1];
	//	//	//G_triangle(rpoint[0], rpoint[1], 200.0, 200.0, 600.0, 200.0); 
	//	//	G_triangle(400.0, 600.0, 200.0, 200.0, 600.0, 200.0); 
	//	//	triangle(start_points, 0, size, rpoint);
	//	//}
	//	G_wait_key();
	//}

void triangle_wrapper(float points[6], int depth, int max)
{
	G_rgb((points[0] / 1000), ((1000 - points[2]) / 1000), (points[5] / 1000));
	G_triangle(points[0], points[1], points[2], points[3], points[4], points[5]); 
	triangle(points, 0, max);
	return;
}


int triangle(float points[6], int depth, int max)// float rpoint[2])
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
	//float d1 = sqrt(pow((mx1 + rpoint[0]), 2) + pow((my1 + rpoint[1]), 2));
	//G_rgb(mx1 / d1, my1 / d1, my2 / d1);	
//	G_line(mx1, my1, mx2, my2);
//	G_line(mx1, my1, rpoint[0], rpoint[1]);

//	d1 = sqrt(pow((mx3 + rpoint[0]), 2) + pow((my3 + rpoint[1]), 2));
//	G_rgb(mx3 / d1, my3 / d1, my1/d1);
//

	G_rgb((mx1 / 1000), ((1000 - mx2) / 1000), (my3 / 1000));

	//float k3[2] = {points[4], points[5]};
	float k1[2] = {mx1, my1};
	float k2[2] = {mx2, my2};
	float k3[2] = {mx3, my3};
	koch_curve(k1, k3, 0, max);
	koch_curve(k3, k2, 0, max);
	koch_curve(k2, k1, 0, max);

	G_rgb((mx2 / 1000), ((1000 - mx1) / 1000), (my2 / 1000));
	G_line(mx1, my1, mx2, my2);
	
	G_rgb(mx1/ 1000, (1000 - mx3) / 1000, my1 / 1000);
	G_line(mx1, my1, mx3, my3);
	
	G_rgb(mx3/ 1000, (1000 - mx2) / 1000, my3 / 1000);
	G_line(mx2, my2, mx3, my3);
	
	//float k1[2] = {points[0], points[1]};
	//float k2[2] = {points[2], points[3]};
	//float k3[2] = {points[4], points[5]};
	//float k1[2] = {mx1, my1};
	//float k2[2] = {mx2, my2};
	//float k3[2] = {mx3, my3};
	//koch_curve(k1, k2, 0, max);
	//koch_curve(k2, k3, 0, max);
	//koch_curve(k3, k1, 0, max);

	//G_line(mx2, my2, rpoint[0], rpoint[1]);
	//
	//d1 = sqrt(pow((mx2 + rpoint[0]), 2) + pow((my2 + rpoint[1]), 2));
	//G_rgb(mx2 / d1, my2 / d1, my3/d1);
	//G_line(mx2, my2, mx3, my3);
	//G_line(mx3, my3, rpoint[0], rpoint[1]);
	
	

	float p1[6] = {points[0], points[1], mx1, my1, mx2, my2};
	float p2[6] = {points[2], points[3], mx1, my1, mx3, my3};
	float p3[6] = {points[4], points[5], mx2, my2, mx3, my3};
	triangle(p1, depth + 1, max); //, rpoint);
	triangle(p2, depth + 1, max); //, rpoint);
	triangle(p3, depth + 1, max); //, rpoint);
	return 0;
}
