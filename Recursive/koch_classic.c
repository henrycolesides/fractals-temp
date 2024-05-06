
#include "FPToolkit.c"

int koch_curve(float p1[2], float p2[2], int depth, int max);

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
	
	float width = 1000.0;
	float height = 1000.0;

	G_init_graphics(width, height);

	G_rgb(0.0, 0.0, 0.0);
	G_clear();

	G_rgb(0.0, 0.0, 0.0);

	//float p1[2] = {200.0, 600.0};
	//float p2[2] = {600.0, 600.0};
	//float p3[2] = {400.0, 200.0};

	// Classic curve
	//float p1[2] = {200.0, 200.0};
	//float p2[2] = {800.0, 200.0};
	//koch_curve(p2, p1, 1, size);
	
	// Classic snowflake (triangle)	- Clockwise
	//float p1[2] = {500.0, 950.0};
	//float p2[2] = {890.0, 275.0};
	//float p3[2] = {110.0, 275.0};
	//koch_curve(p1, p2, 1, size);
	//koch_curve(p2, p3, 1, size);
	//koch_curve(p3, p1, 1, size);
	
	// Koch antisnowflake (triangle) - Counter-clockwise
	float p1[2] = {500.0, 950.0};
	float p2[2] = {890.0, 275.0};
	float p3[2] = {110.0, 275.0};
	koch_curve(p1, p3, 1, size);
	koch_curve(p3, p2, 1, size);
	koch_curve(p2, p1, 1, size);
	

	//G_wait_key();
	// Regular 6-sided
	//p1 = {275.0, 617.0};
	//p2 = {525.0, 617.0};
	//p3 = {650.0, 400.0};
	//p4 = {525.0, 183.0};
	//p5 = {275.0, 183.0};
	//p6 = {150.0, 400.0};
	//koch_curve(p1, p2, 1, size);
	//koch_curve(p2, p3, 1, size);
	//koch_curve(p3, p4, 1, size);
	//koch_curve(p4, p5, 1, size);
	//koch_curve(p5, p6, 1, size);
	//koch_curve(p6, p1, 1, size);
	


	//Inverse 6-sided
	//float p1[2] = {775.0, 400.0};
	//float p2[2] = {587.0, 725.0};
	//float p3[2] = {213.0, 725.0};
	//float p4[2] = {25.0, 400.0};
	//float p5[2] = {212.0, 75.0};
	//float p6[2] = {588.0, 75.0};
	//koch_curve(p1, p2, 1, size);
	//koch_curve(p2, p3, 1, size);
	//koch_curve(p3, p4, 1, size);
	//koch_curve(p4, p5, 1, size);
	//koch_curve(p5, p6, 1, size);
	//koch_curve(p6, p1, 1, size);
	
	G_wait_key();

}

int koch_curve(float p1[2], float p2[2], int depth, int max)
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

	G_rgb((m1[0] / 1000), ((1000 - perp_m[0]) / 1000), (m2[1] / 1000));
	if(depth == max) // If we have reach max depth
	{
		// Draw our calculated segments
		G_line(p1[0], p1[1], m1[0], m1[1]);
		G_line(p2[0], p2[1], m2[0], m2[1]);
		G_line(m1[0], m1[1], perp_m[0], perp_m[1]);
		G_line(m2[0], m2[1], perp_m[0], perp_m[1]);
		return 0;
	}
	
	koch_curve(p1, m1, depth + 1, max);
	koch_curve(m1, perp_m, depth + 1, max);
	koch_curve(perp_m, m2, depth + 1, max);
	koch_curve(m2, p2, depth + 1, max);
	return 0;
}
