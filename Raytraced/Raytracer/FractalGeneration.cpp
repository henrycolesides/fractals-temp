
#include <cmath>
#include "RaytracerMath.h"
#include "SceneObjects.h"

void koch_snowflake3d(const Vec3& a, const Vec3& b, const Vec3& c, int depth, int max, std::vector<Shape *> & shapes)
{
	if (depth > max) return;
	
//	Vec3 a_mid_b = Vec3((a.values[0] + b.values[0]) / 2, (a.values[1] + b.values[1]) / 2, (a.values[3] + b.values[3]) / 2)
//	Vec3 b_mid_c = Vec3((b.values[0] + c.values[0]) / 2, (b.values[1] + c.values[1]) / 2, (b.values[3] + c.values[3]) / 2);
//	Vec3 c_mid_a = Vec3((c.values[0] + a.values[0]) / 2, (c.values[1] + a.values[1]) / 2, (c.values[3] + a.values[3]) / 2);
	
	Vec3 a_mid_b = (a + b) / 2;
	Vec3 b_mid_c = (b + c) / 2;
	Vec3 c_mid_a = (c + a) / 2;

	Vec3 centroid = a_mid_b + ((c - a_mid_b) / 3);
    Vec3 ab = b - a;
	Vec3 bc = c - a;

	Vec3 normal = cross(ab, bc);
	normal = normal / normal.length();
	
	float length = distance_between_points(a_mid_b, b_mid_c);
	float height = std::sqrt(std::pow(length, 2) - std::pow(distance_between_points(a_mid_b, centroid), 2));

	Vec3 d = centroid + (height * normal);
	
	shapes.push_back(new Triangle(d, a_mid_b, b_mid_c, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(d, b_mid_c, c_mid_a, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(d, c_mid_a, a_mid_b, Color(255, 255, 255), 300.0, 0.2f, INFINITY));
	
	koch_snowflake3d(a_mid_b, d, c_mid_a, depth + 1, max, shapes);
	koch_snowflake3d(b_mid_c, d, a_mid_b, depth + 1, max, shapes);
	koch_snowflake3d(c_mid_a, d, b_mid_c, depth + 1, max, shapes);
	koch_snowflake3d(a, a_mid_b, c_mid_a, depth + 1, max, shapes);
	koch_snowflake3d(a_mid_b, b, b_mid_c, depth + 1, max, shapes);
	koch_snowflake3d(c_mid_a, b_mid_c, c, depth + 1, max, shapes);

	// b_mid_c - d cross a_mid_b - b_mid_c
	return;
}

float distance_between_points(const Vec3& op1, const Vec3& op2)
{
	return std::sqrt(std::pow(op1.values[0] - op2.values[0], 2) 
					+ std::pow(op1.values[1] - op2.values[1], 2) 
					+ std::pow(op1.values[2] - op2.values[2], 2));
}
