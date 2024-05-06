
#include "FPToolkit.c"
#define OPTIONS "hn:"

void pyth_square(float p1[2], float p2[2], int depth, int max);
void pyth_tri(float p1[2], float p2[2], int depth, int max);

int main(int argc, char * argv[])
{
	srand(time(NULL));

	int size = 1;
	int opt = 0;
	while((opt = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch(opt)
		{
			case 'h':
				fprintf(stdout, "\toptions: n:s::h\n"
					"\t-n int : recursion depth (1-30)\n"
					"\t-h     : display help and exit\n\n");
				return 0;
				break;
			case 'n':
				size = atoi(optarg);
				if(size > 30)
				{
					fprintf(stderr, "%d is too large! Defaulting to 5\n", size);
					size = 20;
				}
				else if(size < 1)
				{
					fprintf(stderr, "%d is too small! Defaulting to 1\n", size);
					size = 1;
				}
				break;
				break;
			default:
				break;
		}
	}


	float width = 1000.0;
	float height = 1000.0;

	G_init_graphics(width, height);

	//float p1[2] = {450.0, 50.0};
	//float p2[2] = {550.0, 50.0};	
	
	float p1[2] = {300.0, 500.0};
	float p2[2] = {700.0, 500.0};
	while(1)
	{
		G_rgb(0.0, 0.0, 0.0);
		G_clear();
		pyth_tri(p1, p2, 0, size);
		pyth_tri(p2, p1, 0, size);
//		pyth_square(p1, p2, 0, size);
	//	G_line(0.0, 50.0, 999.0, 50.0);
		
		G_display_image();
	}

	G_wait_key();
}

void pyth_square(float p1[2], float p2[2], int depth, int max)
{
	if(depth >= max) return; 
	
	float scale = 0.5;
	G_rgb(pow(0.8, 2.2) , pow(((float)depth / (float)max), 2.2), pow(((float)depth / (float)max), 2.2));
	
	float p3[2] = {p1[0] + -(p2[1] - p1[1]), 
			p1[1] + (p2[0] - p1[0])};
	
	float p4[2] = {p2[0] + -(p2[1] - p1[1]), 
			p2[1] + (p2[0] - p1[0])};
	
	//p3[0] = scale * p3[0];
	//p3[1] = scale * p3[1];
	//p4[0] = scale * p4[0];
	//p4[1] = scale * p4[1];
	
	// Funky:
	double xx[4] = {p1[0], p2[0], p3[0], p4[0]};
	double yy[4] = {p1[1], p2[1], p3[1], p4[1]};
	
	//double xx[4] = {p1[0], p2[0], p4[0], p3[0]};
	//double yy[4] = {p1[1], p2[1], p4[1], p3[1]};
	G_fill_polygon(xx, yy, 4);
	//G_square(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1], p4[0], p4[1]);
	//G_line(p1[0], p1[1], p3[0], p3[1]);
	//G_line(p2[0], p2[1], p4[0], p4[1]);
	//G_line(p3[0], p3[1], p4[0], p4[1]);
	
	pyth_tri(p3, p4, depth + 1, max);
	return;
}

void pyth_tri(float p1[2], float p2[2], int depth, int max)
{
	if(depth >= max) return;	
	
	G_rgb(pow(0.8, 2.2) , pow(((float)depth / (float)max), 2.2), pow(((float)depth / (float)max), 2.2));
	float right_angle = 1.5708;
	float angle1, angle2 = 0.0;
	angle1 = 1.0472; // 60 degrees in radians!
	angle2 = 2.61799; // 150 degrees in radians!
	
	//angle1 = 0.785398; // 45
	//angle2 = 2.35619;  // 135
	//if(rand() % 2 == 0)
	//{
	//	angle1 = 1.0472; // 60 degrees in radians!
	//	angle2 = angle1 + right_angle; // 150 degrees in radians!
	//}
	//else
	//{
	//	angle1 = 0.523599; // 30 degrees in radians!
	//	angle2 = angle1 + right_angle; // 120 degrees in radians!
	//}

	angle1 = (rand() % 90) * (3.14159 / 180);
	angle2 = angle1 + right_angle;

	float m1, m2, slope = 0;

	// FIX case of vertical line on right-sided triangles
	if(p1[0] == p2[0]) // If verticle line:
	{
		m1 = tan(angle1 + right_angle);
		m2 = tan(angle2 + right_angle);
	}
	else
	{
		slope = (p1[1] - p2[1]) / (p1[0] - p2[0]);
		//float m1 = (tan(angle1) - slope) / (-1 - (tan(angle1) * slope));
		//float m2 = (tan(angle2) - slope) / (-1 - (tan(angle2) * slope));
		
		m1 = (slope + tan(angle1)) / (1 - (slope * tan(angle1)));
		m2 = (slope + tan(angle2)) / (1 - (slope * tan(angle2)));
		//m1 = (slope - tan(angle1)) / (1 + (slope * tan(angle1)));
		//m2 = (slope - tan(angle2)) / (1 + (slope * tan(angle2)));
	}

	// y-intercepts
	float c1 = (-m1 * p1[0]) + p1[1];
	float c2 = (-m2 * p2[0]) + p2[1];
	
	float p3[2] = {(c2 - c1) / (m1 - m2), 
		((c1 * m2) - (c2 * m1)) / -(m1 - m2)};
	
	G_fill_triangle(p1[0], p1[1], p3[0], p3[1], p2[0], p2[1]);
	
	G_rgb(0.0, 0.0, 0.0);
	G_line(p1[0], p1[1], p2[0], p2[1]);
	G_line(p2[0], p2[1], p3[0], p3[1]);
	G_line(p3[0], p3[1], p1[0], p1[1]);
	//printf("Depth: %d\n", depth);
	//printf("P1: (%f, %f)\tP2: (%f, %f)\n", p1[0], p1[1], p2[0], p2[1]);
	//printf("Slope: %f\nangle1(60): %f\nangle2(30): %f\nm1: %f\nm2: %f\n", slope, angle1, angle2, m1, m2);
	//printf("c1: %f\nc2: %f\n", c1, c2);
	//printf("p3: (%f, %f)\n\n", p3[0], p3[1]);

	//pyth_square(p1, p3, depth, max);
	//pyth_square(p3, p2, depth, max);
	
	pyth_tri(p1, p3, depth + 1, max);
	pyth_tri(p3, p2, depth + 1, max);
	return;
}


























