
#include "FPToolkit.c"
#include "serpinski_triangle2.c"

#define OPTIONS "n:s:h"

int koch_and_serpinski(float p1[2], float p2[2], int depth, int max);

int main(int argc, char * argv[])
{
	int size = 1;
	int sides = 3;
	int opt = 0;

	while((opt = getopt(argc, argv, OPTIONS)) != -1)
	{
		switch(opt)
		{
			case 'h':
				fprintf(stdout, "\toptions: n:s::h\n"
					"\t-n int : recursion depth (1-6)\n"
					"\t-s int : number of polygon sides (1-7)\n"
					"\t-h     : display help and exit\n\n");
				return 0;
				break;
			case 'n':
				size = atoi(optarg);
				if(size > 7)
				{
					fprintf(stderr, "%d is too large! Defaulting to 5\n", size);
					size = 5;
				}
				else if(size < 1)
				{
					fprintf(stderr, "%d is too small! Defaulting to 1\n", size);
					size = 1;
				}
				break;
			case 's':
				sides = atoi(optarg);
				if(sides > 7) 
				{
					fprintf(stderr, "Only supports up to 7-sided polygons! Defaulting to 7\n");
					sides = 7;
				}
				if(sides < 1) 
				{
					fprintf(stderr, "Invalid argument. Defaulting to 1\n");
					sides = 1;
				}
				break;
			default:
				break;
		}
	}

	float width = 1000.0;
	float height = 1000.0;

	G_init_graphics(width, height);

	G_rgb(0.0, 0.0, 0.0);
	G_clear();
	
	switch(sides)
	{
		case 1:
		{
			float p1[2] = {100.0, 400.0};
			float p2[2] = {900.0, 400.0};

			koch_and_serpinski(p1, p2, 1, size);
		}
			break;
		case 2: 
		{
			float p1[2] = {500.0, 900.0};
			float p2[2] = {500.0, 100.0};

			koch_and_serpinski(p1, p2, 1, size);
			koch_and_serpinski(p2, p1, 1, size);
		}
			break;
		case 3:
		{
			float p1[2] = {500.0, 950.0};
			float p2[2] = {890.0, 275.0};
			float p3[2] = {110.0, 275.0};
			
			float m1[2] = {(p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2};
			float m2[2] = {(p2[0] + p3[0]) / 2, (p2[1] + p3[1]) / 2};
			float m3[2] = {(p3[0] + p1[0]) / 2, (p3[1] + p1[1]) / 2};
			
			//triangle_wrapper(p1, m1, m3, 0, size);
			//triangle_wrapper(m1, p2, m2, 0, size);
			//triangle_wrapper(m3, m2, p3, 0, size);
			//triangle_wrapper(m1, m2, m3, 0, size);
			//
			//koch_and_serpinski(p1, p2, 1, size);
			//koch_and_serpinski(p2, p3, 1, size);
			//koch_and_serpinski(p3, p1, 1, size);	
			
			for(int i = 1; i <= size; ++i)
			{
				G_wait_key();

				G_rgb(0.0, 0.0, 0.0);
				G_clear();

				triangle_wrapper(p1, m1, m3, 0, i);
				triangle_wrapper(m1, p2, m2, 0, i);
				triangle_wrapper(m3, m2, p3, 0, i);
				triangle_wrapper(m1, m2, m3, 0, i);
				
				koch_and_serpinski(p1, p2, 1, i);
				koch_and_serpinski(p2, p3, 1, i);
				koch_and_serpinski(p3, p1, 1, i);
			}
			//koch_and_serpinski(p2, p1, 1, size);
			//koch_and_serpinski(p3, p2, 1, size);
			//koch_and_serpinski(p1, p3, 1, size);
		}
			break;	
		case 4:
		{
			float p1[2] = {217.0, 783.0};
			float p2[2] = {783.0, 783.0};
			float p3[2] = {783.0, 217.0};
			float p4[2] = {217.0, 217.0};
			
			float midpoint[2] = {500.0, 500.0};
			
			triangle_wrapper(p1, p2, midpoint, 0, size);
			triangle_wrapper(p2, p3, midpoint, 0, size);
			triangle_wrapper(p3, p4, midpoint, 0, size);
			triangle_wrapper(p4, p1, midpoint, 0, size);
			
			koch_and_serpinski(p1, p2, 1, size);
			koch_and_serpinski(p2, p3, 1, size);
			koch_and_serpinski(p3, p4, 1, size);
			koch_and_serpinski(p4, p1, 1, size);
		}
			break;
		case 5:
		{
			float p1[2] = {265.0, 824.0};
			float p2[2] = {735.0, 824.0};
			float p3[2] = {880.0, 376.0};
			float p4[2] = {500.0, 100.0};
			float p5[2] = {120.0, 376.0};
			
			float midpoint[2] = {500.0, 500.0};
			
			triangle_wrapper(p1, p2, midpoint, 0, size);
			triangle_wrapper(p2, p3, midpoint, 0, size);
			triangle_wrapper(p3, p4, midpoint, 0, size);
			triangle_wrapper(p4, p5, midpoint, 0, size);
			triangle_wrapper(p5, p1, midpoint, 0, size);
			
			koch_and_serpinski(p1, p2, 1, size);
			koch_and_serpinski(p2, p3, 1, size);
			koch_and_serpinski(p3, p4, 1, size);
			koch_and_serpinski(p4, p5, 1, size);
			koch_and_serpinski(p5, p1, 1, size);
		}
			break;
		case 6:
		{
			float p1[2] = {300.0, 846.0};
			float p2[2] = {700.0, 846.0};
			float p3[2] = {900.0, 500.0};
			float p4[2] = {700.0, 154.0};
			float p5[2] = {300.0, 154.0};
			float p6[2] = {100.0, 500.0};
			
			float midpoint[2] = {500.0, 500.0};
			
			triangle_wrapper(p1, p2, midpoint, 0, size);
			triangle_wrapper(p2, p3, midpoint, 0, size);
			triangle_wrapper(p3, p4, midpoint, 0, size);
			triangle_wrapper(p4, p5, midpoint, 0, size);
			triangle_wrapper(p5, p6, midpoint, 0, size);
			triangle_wrapper(p6, p1, midpoint, 0, size);
			
			koch_and_serpinski(p1, p2, 1, size);
			koch_and_serpinski(p2, p3, 1, size);
			koch_and_serpinski(p3, p4, 1, size);
			koch_and_serpinski(p4, p5, 1, size);
			koch_and_serpinski(p5, p6, 1, size);
			koch_and_serpinski(p6, p1, 1, size);
			
			//koch_and_serpinski(p2, p1, 1, size);
			//koch_and_serpinski(p3, p2, 1, size);
			//koch_and_serpinski(p4, p3, 1, size);
			//koch_and_serpinski(p5, p4, 1, size);
			//koch_and_serpinski(p6, p5, 1, size);
			//koch_and_serpinski(p1, p6, 1, size);



		}
			break;
		case 7:
		{
			float p1[2] = {326.0, 860.0};
			float p2[2] = {674.0, 860.0};
			float p3[2] = {890.0, 589.0};
			float p4[2] = {813.0, 251.0};
			float p5[2] = {500.0, 100.0};
			float p6[2] = {187.0, 251.0};
			float p7[2] = {110.0, 589.0};
			
			float midpoint[2] = {500.0, 500.0};
			
			triangle_wrapper(p1, p2, midpoint, 0, size);
			triangle_wrapper(p2, p3, midpoint, 0, size);
			triangle_wrapper(p3, p4, midpoint, 0, size);
			triangle_wrapper(p4, p5, midpoint, 0, size);
			triangle_wrapper(p5, p6, midpoint, 0, size);
			triangle_wrapper(p6, p7, midpoint, 0, size);
			triangle_wrapper(p7, p1, midpoint, 0, size);
			
			koch_and_serpinski(p1, p2, 1, size);
			koch_and_serpinski(p2, p3, 1, size);
			koch_and_serpinski(p3, p4, 1, size);
			koch_and_serpinski(p4, p5, 1, size);
			koch_and_serpinski(p5, p6, 1, size);
			koch_and_serpinski(p6, p7, 1, size);
			koch_and_serpinski(p7, p1, 1, size);
		}
			break;
	}
	// Anti-snowflake of triangles of snowflakes
	//float p1[2] = {500.0, 950.0};
	//float p2[2] = {890.0, 275.0};
	//float p3[2] = {110.0, 275.0};
	//
	//triangle_wrapper(p3, p2, p1, 0, size);
        //
	//koch_and_serpinski(p3, p2, 1, size);
	//koch_and_serpinski(p2, p1, 1, size);
	//koch_and_serpinski(p1, p3, 1, size);
	int key = G_wait_key();
	if(key == 's')
	{
   		G_save_to_bmp_file("koch_and_serpinski.bmp") ;
	}
	//int color = 0;
	//int rgbI[3];
	//double rgbX[3];
	//for(double i = 0; i < width; ++i)
	//{
	//	for(double j = 0; j < height; ++j)
	//	{
	//		if((int)j % 100 == 0) printf("%lf, %lf\n", i, j);
	//		color = G_get_pixel(i, j);
	//		G_convert_pixel_to_rgbI(color, rgbI);
	//		G_convert_rgbI_to_rgb(rgbI, rgbX);
	//		rgbX[0] = pow(rgbX[0], (1.0/2.2));
	//		rgbX[1] = pow(rgbX[1], (1.0/2.2));
	//		rgbX[2] = pow(rgbX[2], (1.0/2.2));
	//		G_rgb(rgbX[0], rgbX[1], rgbX[2]);
	//		G_point(i, j);
	//	}
	//}
	//G_wait_key();
	return 0;
}

int koch_and_serpinski(float p1[2], float p2[2], int depth, int max)
{
	// Calculation of 1/3, 2/3 points
	float m1[2], m2[2];
	if(p1[0] < p2[0])
	{
		m1[0] = p1[0] + ((p2[0] - p1[0]) / 3);
		m2[0] = p1[0] + (2 * ((p2[0] - p1[0]) / 3));
	}
	else
	{
		m1[0] = p1[0] - ((p1[0] - p2[0]) / 3);
		m2[0] = p1[0] - (2 * ((p1[0] - p2[0]) / 3));
	}
	if(p1[1] < p2[1])
	{
		m1[1] = p1[1] + ((p2[1] - p1[1]) / 3);
		m2[1] = p1[1] + (2 * ((p2[1] - p1[1]) / 3));
	}
	else
	{
		m1[1] = p1[1] - ((p1[1] - p2[1]) / 3);
		m2[1] = p1[1] - (2 * ((p1[1] - p2[1]) / 3));
	}
	
	// Finding point on line perpendicular to (p1, p2) using midpoint and distance from:
	
	float midpoint[2] = {(m1[0] + m2[0]) / 2, (m1[1] + m2[1]) / 2};
	float perp_m[2];

	float length = sqrt(pow(m1[0] - m2[0], 2) + pow(m1[1] - m2[1], 2));
	float height = sqrt(pow(length, 2) - (pow(length, 2) / 4));
	
	if(m1[0] > m2[0])
	{
		height = -height;
	}

	// If finding point on verticel line (y1 == y2)
	if(m1[1] == m2[1])
	{
		perp_m[0] = midpoint[0];
		perp_m[1] = midpoint[1] + height;
	}
	else if(m1[0] == m2[0])	// If finding point on horizontal line (x1 == x2)
	{
		if(m1[1] <= m2[1]) height = -height;
		perp_m[0] = midpoint[0] + height;
		perp_m[1] = midpoint[1];
	}
	else // If finding point on some other slope of line
	{
		float slope = (p1[1] - p2[1]) / (p1[0] - p2[0]);
		float angle = atan(-1 / slope);
		
		if(slope < 0)
		{
			perp_m[0] = midpoint[0] + (height * cos(angle));
			perp_m[1] = midpoint[1] + (height * sin(angle));
		}
		else
		{
			perp_m[0] = midpoint[0] + (height * -cos(angle));
			perp_m[1] = midpoint[1] + (height * -sin(angle));
		}
	}
	
	// Add serpinski's triangle!
	
	triangle_wrapper(m1, perp_m, m2, 0, max - depth);
	
	if(depth == max) // If we have reach max depth
	{
		//triangle_wrapper(m1, perp_m, m2, 0, max - depth + 1);
		// Draw our calculated segments
		//G_line(p1[0], p1[1], m1[0], m1[1]);
		//G_line(p2[0], p2[1], m2[0], m2[1]);
		//G_line(m1[0], m1[1], perp_m[0], perp_m[1]);
		//G_line(m2[0], m2[1], perp_m[0], perp_m[1]);
		return 0;
	}
	
	koch_and_serpinski(p1, m1, depth + 1, max);
	koch_and_serpinski(m1, perp_m, depth + 1, max);
	koch_and_serpinski(perp_m, m2, depth + 1, max);
	koch_and_serpinski(m2, p2, depth + 1, max);
	return 0;
}
