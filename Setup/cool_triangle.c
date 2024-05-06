
#include "FPToolkit.c"

void pyth_square(float p1[2], float p2[2], int depth, int max);
void pyth_tri(float p1[2], float p2[2], int depth, int max);

int main()
{
	float width = 1000.0;
	float height = 1000.0;

	G_init_graphics(width, height);
	G_rgb(0.0, 0.0, 0.0);
	G_clear();

	G_rgb(0.9, 0.9, 0.9);
	
	float p1[2] = {500.0, 500.0};
	float p2[2];	
	float step = 0.025;
	float angle = 0.0;
	float radius = 0.0;
	while(1)
	{
		p2[0] = (p1[0] + 10) * cos(angle) + (width/2);
		p2[1] = (p2[0] + 10) * sin(angle) + (height/2);
		G_rgb(0.9, 0.9, 0.9);
		pyth_tri(p1, p2, 0, 1); 
//		G_wait_key();

		G_rgb(0.0, 0.0, 0.0);
	//	G_clear();
		angle += step;	

		G_display_image();
	}
//	pyth_square(p1, p2, 0, 3);
	
	G_wait_key();
}

void pyth_square(float p1[2], float p2[2], int depth, int max)
{
	if(depth >= max) return; 

	//float length = sqrt(pow((p1[0] - p2[0]), 2) + pow((p1[1] - p2[1]), 2));
	//float slope = (p1[1] - p2[1]) / (p1[0] - p2[0]);
	//float angle = atan(-1 / slope);
	//float scale = 1.0;

	//float p3[2], p4[2];
	//if(slope >= 0)
	//{
	//	p3[0] = p1[0] + (scale * length * cos(angle));
	//	p3[1] = p1[1] + (scale * length * sin(angle));
	//	p4[0] = p2[0] + (scale * length * cos(angle));
	//	p4[1] = p2[1] + (scale * length * sin(angle));
	//}
	//else
	//{
	//	p3[0] = p1[0] + (scale * length * -cos(angle));
	//	p3[1] = p1[1] + (scale * length * -sin(angle));
	//	p4[0] = p2[0] + (scale * length * -cos(angle));
	//	p4[1] = p2[1] + (scale * length * -sin(angle));
	//}
	//
	//G_line(p1[0], p1[1], p3[0], p3[1]);
	//G_line(p2[0], p2[1], p4[0], p4[1]);
	//G_line(p3[0], p3[1], p4[0], p4[1]);
	
	float p3[2] = {p1[0] + -(p2[1] - p1[1]), 
			p1[1] + (p2[0] - p1[0])};

	float p4[2] = {p2[0] + -(p2[1] - p1[1]), 
			p2[1] + (p2[0] - p1[0])};

	G_line(p1[0], p1[1], p3[0], p3[1]);
	G_line(p2[0], p2[1], p4[0], p4[1]);
	G_line(p3[0], p3[1], p4[0], p4[1]);
	
	pyth_tri(p3, p4, depth, max);
	return;
}

void pyth_tri(float p1[2], float p2[2], int depth, int max)
{
	if(depth >= max) return;	

	// First: assume l1 makes a 60 degree angle with p1p2
	// 		 l2 makes a 30 degree angle with p1p2
	
	float slope = (p1[1] - p2[1]) / (p1[0] - p2[0]);
	float angle1 = 1.0472; // 60 degrees in radians!
	float angle2 = 2.61799; // 150 degrees in radians!
		
	float m1 = -(tan(angle1) - slope) / (-1 - (tan(angle1) * slope));
	float m2 = -(tan(angle2) - slope) / (-1 - (tan(angle2) * slope));
	
	// y-intercepts
	float c1 = (-m1 * p1[0]) + p1[1];
	float c2 = (-m2 * p2[0]) + p2[1];
	
	float p3[2] = {(c2 - c1) / (m1 - m2), 
		((c1 * m2) - (c2 * m1)) / -(m1 - m2)};




	G_fill_triangle(p1[0], p1[1], p3[0], p3[1], p2[0], p2[1]);
	
	//printf("Depth: %d\n", depth);
	//printf("P1: (%f, %f)\tP2: (%f, %f)\n", p1[0], p1[1], p2[0], p2[1]);
	//printf("Slope: %f\nangle1(60): %f\nangle2(30): %f\nm1: %f\nm2: %f\n", slope, angle1, angle2, m1, m2);
	//printf("c1: %f\nc2: %f\n", c1, c2);
	//printf("p3: (%f, %f)\n\n", p3[0], p3[1]);

	pyth_square(p1, p3, depth + 1, max);
//	pyth_square(p3, p2, depth + 1, max);
	return;
}


























