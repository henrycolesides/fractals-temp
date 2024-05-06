
#include "FPToolkit.c"

void triangle_wrapper(float p1[2], float p2[2], float p3[2], int depth, int max);
void triangle(float p1[2], float p2[2], float p3[2], int depth, int max);

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
	G_rgb(0.8, 0.8, 0.8);
	G_clear();

	G_rgb(0.0, 0.0, 0.0);
	float p1[2] = {500.0, 950.0};
	float p2[2] = {890.0, 275.0};
	float p3[2] = {110.0, 275.0};

	triangle_wrapper(p1, p2, p3, 0, size);
	G_wait_key();
}

// For triangle vertices:
// p1: top
// p2: bottom-left
// p3: bottom-right
void triangle_wrapper(float p1[2], float p2[2], float p3[2], int depth, int max)
{
	G_line(p1[0], p1[1], p2[0], p2[1]);	
	G_line(p2[0], p2[1], p3[0], p3[1]);	
	G_line(p3[0], p3[1], p1[0], p1[1]);	
	triangle(p1, p2, p3, depth, max);
	return;
}

void triangle(float p1[2], float p2[2], float p3[2], int depth, int max)
{
	if(depth > max) return;
	// m1: midpoint between top and bottom-left
	// m2: midpoint between bottom-left and bottom-right
	// m3: midpoint between bottom-right and top
	float m1[2] = {(p1[0] + p2[0]) / 2, (p1[1] + p2[1]) / 2};
	float m2[2] = {(p2[0] + p3[0]) / 2, (p2[1] + p3[1]) / 2};
	float m3[2] = {(p3[0] + p1[0]) / 2, (p3[1] + p1[1]) / 2};
	
	// Color here:
	
	G_line(m1[0], m1[1], m2[0], m2[1]);
	G_line(m2[0], m2[1], m3[0], m3[1]);
	G_line(m3[0], m3[1], m1[0], m1[1]);

	triangle(p1, m1, m3, depth + 1, max);
	triangle(m1, p2, m2, depth + 1, max);
	triangle(m3, m2, p3, depth + 1, max);
	return;
}






