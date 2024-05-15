
#include <cmath>
#include <iostream>
#include "RaytracerMath.h"
#include "SceneObjects.h"

void pyth_tree_3d(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int depth, const int max, std::vector<Shape *> & shapes);

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

// Given four points, add triangles to shapes according to tri_per_sides which make up a cube 
// These four points make up one side of the cube
// A ------- B 
//   |     |
//   |     |
// C ------- D
//
// Initial case is made up of two tris: (A, B, C) and (B, D, C)
// AB and CD are parallel! be careful

void cube(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int depth, const int max, std::vector<Shape *> & shapes)
{
    float side_length = distance_between_points(a, b);
   
    Vec3 ab = b - a;	
    Vec3 bc = c - a;
    Vec3 normal = cross(ab, bc);
    normal = normal / normal.length();
    
    Vec3 e = a + (side_length * normal);
    Vec3 f = b + (side_length * normal);
    Vec3 g = c + (side_length * normal);
    Vec3 h = d + (side_length * normal);
    
	shapes.push_back(new Triangle(a, c, b, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(b, c, d, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
    
	shapes.push_back(new Triangle(e, g, f, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(f, g, h, Color(255, 0, 0), 300.0, 0.2f, INFINITY));

	shapes.push_back(new Triangle(e, g, a, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(a, g, c, Color(255, 0, 0), 300.0, 0.2f, INFINITY));

	shapes.push_back(new Triangle(b, d, f, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(f, d, h, Color(255, 0, 0), 300.0, 0.2f, INFINITY));

	shapes.push_back(new Triangle(a, b, e, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(e, b, f, Color(255, 0, 0), 300.0, 0.2f, INFINITY));

	shapes.push_back(new Triangle(c, g, d, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
	shapes.push_back(new Triangle(d, g, h, Color(255, 0, 0), 300.0, 0.2f, INFINITY));
    
    pyth_tree_3d(e, f, g, h, depth + 1, max, shapes); 
}


// Provided a, b, c, d find, finds triangle pointing upwards in their normal direction, and adds cubes to shapes based on triangle points
void pyth_tree_3d(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int depth, const int max, std::vector<Shape *> & shapes)
{
    if(depth > max) return;
    
    Vec3 normal = cross(b - a, c - a);
    normal = normal / normal.length();
    
    float side_length = distance_between_points(a, b);
    float new_length = side_length / std::sqrt(2.0);
//    float height = std::sqrt(std::pow(side_length, 2) - (std::pow(side_length, 2) / 2.0));
    float height = std::sqrt((std::pow(side_length, 2) / 2.0) - (std::pow(side_length, 2) / 4.0));
    float d_along_side = (side_length - new_length) / 2;

    //std::cout << "Height: " << height << '\n';
    //std::cout << "Normal: " << normal << '\n';
     
    Vec3 a_close = a + (((c - a) / (c - a).length()) * d_along_side);
    Vec3 c_close = c + (((a - c) / (a - c).length()) * d_along_side);
    Vec3 b_close = b + (((d - b) / (d - b).length()) * d_along_side);
    Vec3 d_close = d + (((b - d) / (b - d).length()) * d_along_side);
    
    Vec3 a_mid_b = (a_close + b_close) / 2.0; 
    Vec3 c_mid_d = (c_close + d_close) / 2.0; 

    Vec3 ab_up = a_mid_b + (height * normal);
    Vec3 cd_up = c_mid_d + (height * normal);

    //std::cout << a_close << ", " << b_close << '\n';
    //std::cout << "Mid: " << a_mid_b << '\n';
    //std::cout << "Up: " << ab_up << "\n\n";
    //
    //std::cout << c_close << ", " << d_close << '\n';
    //std::cout << "Mid: " << c_mid_d << '\n';
    //std::cout << "Up: " << cd_up << "\n\n";

    cube(ab_up, cd_up, a_close, c_close, depth, max, shapes); 
    cube(cd_up, ab_up, d_close, b_close, depth, max, shapes); 

    return;
}



