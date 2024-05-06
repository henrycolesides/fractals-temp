#include "FPToolkit.c"

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

	G_rgb(pow((m1[0] / 1000), (0.8)), pow(((1000 - perp_m[0]) / 1000), (0.8)), pow((m2[1] / 1000), (0.8)));
//	G_rgb((m1[0] / 1000), ((0.75 * perp_m[0]) / 1000), (m2[1] / 1000));
//	G_rgb((m1[0] / 1000), ((1000 - perp_m[0]) / 1000), (m2[1] / 1000));
//	G_rgb(((float)rand() + m1[0]) / RAND_MAX, ((float)rand() + perp_m[0])/ RAND_MAX, ((float)rand() + m2[1])/ RAND_MAX);
	if(depth >= max) // If we have reach max depth
	{
		// Draw our calculated segments
//		G_rgb((p1[0] / 1000), ((1000 - m1[0]) / 1000), (p1[1] / 1000));
		G_line(p1[0], p1[1], m1[0], m1[1]);
	
//		G_rgb((p2[0] / 1000), ((1000 - m2[0]) / 1000), (p2[1] / 1000));
		G_line(p2[0], p2[1], m2[0], m2[1]);
	
//		G_rgb((perp_m[0] / 1000), ((1000 - p1[0]) / 1000), (perp_m[1] / 1000));
		G_line(m1[0], m1[1], perp_m[0], perp_m[1]);
	
//		G_rgb((perp_m[0] / 1000), ((1000 - m2[0]) / 1000), (perp_m[1] / 1000));
		G_line(m2[0], m2[1], perp_m[0], perp_m[1]);
		return 0;
	}
	
	koch_curve(p1, m1, depth + 1, max);
	koch_curve(m1, perp_m, depth + 1, max);
	koch_curve(perp_m, m2, depth + 1, max);
	koch_curve(m2, p2, depth + 1, max);
	return 0;
}
