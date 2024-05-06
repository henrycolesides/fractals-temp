
#include "FPToolkit.c"

float swidth = 1000.0;
float sheight = 1000.0;
float vwidth = 2.0;
float vheight = 2.0;
float D = 1.0;

struct point3_s
{
	float x;
	float y;
	float z;
} typedef point3_t;

struct triangle_s
{
	point3_t p1;
	point3_t p2;
	point3_t p3;
} typedef triangle_t;

float find_y(float y, float z); 
float find_x(float x, float z);
float shift_x(float x);
float shift_y(float y);
float v_to_canvas_x(float x);
float v_to_canvas_y(float y);
void draw_triangle(triangle_t);


int main()
{
	
	// Viewport space: 0-1, 0-1
	// Canvas space: 0-1000, 0-1000
	
	// shift to proper screen space:
	// xs = swidth / 2 + x
	// ys = sheight / 2 + y
	
	// convert to viewport:
	// vx = sx * (swidth / vwidth)
	// vy = sy * (sheight / vheight)
	
	// Find 2D Point from 3D point in viewport space:
	
	G_init_graphics(1000, 1000);
	G_rgb(1.0, 1.0, 1.0);
	G_clear(0.0, 0.0, 0.0);
	
	triangle_t scene[100] = {};	
	
	float p1[2] = {find_x(-0.5, 0.0), find_y(0.0, 0.0)};
	float p2[2] = {find_x(0.5, 0.0), find_y(0.0, 0.0)};
	float p3[2] = {find_x(0.0, 0.0), find_y(0.866, 0.0)};
	
	scene[0] = (triangle_t){{-0.5, 0.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 0.866, 0.0}};	

	float p4[2] = {find_x(-0.5, 0.0), find_y(0.0, 0.0)};
	float p5[2] = {find_x(0.0, 0.0), find_y(0.866, 0.0)};
	float p6[2] = {find_x(0.0, 0.816), find_y(0.289, 0.816)};
	
	float p7[2] = {find_x(0.5, 0.0), find_y(0.0, 0.0)};
	float p8[2] = {find_x(0.0, 0.816), find_y(0.289, 0.816)};
	float p9[2] = {find_x(0.0, 0.0), find_y(0.866, 0.0)};

	G_rgb(0.0, 0.0, 0.0);
	
	draw_triangle(scene[0]);
//	G_triangle(p1[0], p1[1], p2[0], p2[1], p3[0], p3[1]);
	G_triangle(p4[0], p4[1], p5[0], p5[1], p6[0], p6[1]);
	G_triangle(p7[0], p7[1], p8[0], p8[1], p9[0], p9[1]);

	

	G_wait_key();
}


float find_y(float y, float z)
{
	return shift_y(v_to_canvas_y((y * D) / (D + z)));
}

float find_x(float x, float z)
{
	return shift_x(v_to_canvas_x((x * D) / (D + z)));
}

// shift to middle:
// xs = swidth / 2 + x
// ys = sheight / 2 + y
 
float shift_x(float x)
{
	return (swidth / 2) + x;	
}

float shift_y(float y)
{
	return (sheight / 2) + y;	
}

// viewport to canvas:
float v_to_canvas_x(float x)
{
	return x * (swidth / vwidth);
}

float v_to_canvas_y(float y)
{
	return y * (sheight / vheight);
}

void draw_triangle(triangle_t T)
{
	G_triangle(find_x(T.p1.x, T.p1.z), find_y(T.p1.y, T.p1.z), find_x(T.p2.x, T.p2.z), find_y(T.p2.y, T.p2.z), find_x(T.p3.x, T.p3.z), find_y(T.p3.y, T.p3.z));

	//G_triangle(find_x(T->p1.x, T->p1.z), find_y(T->p1.y, T->p1.z),
	//		find_x(T->p2.x, T->p2.z), find_y(T->p2.y, T->p2.z),
	//		find_x(T->p3.x, T->p3.z), find_y(T->p3.y, T->p3.z));
}


//void koch_snowflake3d(const Vec3& a, const Vec3& b, const Vec3& c, int depth, int max, std::vector<Shape *> & shapes)
//{
//	if (depth > max) return;
//	
////	Vec3 a_mid_b = Vec3((a.values[0] + b.values[0]) / 2, (a.values[1] + b.values[1]) / 2, (a.values[3] + b.values[3]) / 2)
////	Vec3 b_mid_c = Vec3((b.values[0] + c.values[0]) / 2, (b.values[1] + c.values[1]) / 2, (b.values[3] + c.values[3]) / 2);
////	Vec3 c_mid_a = Vec3((c.values[0] + a.values[0]) / 2, (c.values[1] + a.values[1]) / 2, (c.values[3] + a.values[3]) / 2);
//	
//	Vec3 a_mid_b = (a + b) / 2;
//	Vec3 b_mid_c = (b + c) / 2;
//	Vec3 c_mid_a = (c + a) / 2;
//
//	Vec3 centroid = a_mid_b + ((c - a_mid_b) / 3);
//    Vec3 ab = b - a;
//	Vec3 bc = c - a;
//
//	Vec3 normal = cross(ab, bc);
//	normal = normal / normal.length();
//	
//	float length = distance_between_points(a_mid_b, b_mid_c);
//	float height = std::sqrt(std::pow(length, 2) - std::pow(distance_between_points(a_mid_b, centroid), 2));
//
//	Vec3 d = centroid + (height * normal);
//	
//	shapes.push_back(new Triangle(d, a_mid_b, b_mid_c, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
//	shapes.push_back(new Triangle(d, b_mid_c, c_mid_a, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
//	shapes.push_back(new Triangle(d, c_mid_a, a_mid_b, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
//	
//	koch_snowflake3d(a_mid_b, d, c_mid_a, depth + 1, max, shapes);
//	koch_snowflake3d(b_mid_c, d, a_mid_b, depth + 1, max, shapes);
//	koch_snowflake3d(c_mid_a, d, b_mid_c, depth + 1, max, shapes);
//	koch_snowflake3d(a, a_mid_b, c_mid_a, depth + 1, max, shapes);
//	koch_snowflake3d(a_mid_b, b, b_mid_c, depth + 1, max, shapes);
//	koch_snowflake3d(c_mid_a, b_mid_c, c, depth + 1, max, shapes);
//
//	// b_mid_c - d cross a_mid_b - b_mid_c
//	return;
//}
//
//float distance_between_points(const Vec3& op1, const Vec3& op2)
//{
//	return std::sqrt(std::pow(op1.values[0] - op2.values[0], 2) 
//					+ std::pow(op1.values[1] - op2.values[1], 2) 
//					+ std::pow(op1.values[2] - op2.values[2], 2));
//}
