// Camera.cpp
// Provides definitions for camera class for Raytracing

#include <vector>
#include <functional>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Octree.h"
#include "Camera.h"
#include "VectorMath.h"

Camera::Camera() : origin(Vec3()), frame_width(0), frame_height(0),
    viewport_width(0), viewport_height(0), viewport_distance(0) {}

Camera::Camera(const Vec3& origin, const uint32_t frame_width, const uint32_t frame_height,
    const float viewport_width, const float viewport_height, const float viewport_distance)
	: origin(origin), frame_width(frame_width), frame_height(frame_height),
	viewport_width(viewport_width), viewport_height(viewport_height), viewport_distance(viewport_distance) {}







void Camera::render(Octree & octree, const std::vector<Light *> & lights)
{
	//if (!pixels) return;
	
	//std::vector<Shape *> shapes = scene.get_shapes();
	//const std::vector<Light *> lights = scene.get_lights();
	
    std::fstream output;
    char fname[200]; 
	
    //origin.rotate_about_y(0.3);

    int extra_samples = 4;
    Color current;

    int num_frames = 1;
    float angle = ((6.28319) / (float)num_frames);
    //float theta = 0.0;
    for (int f = 0; f < num_frames; ++f)
    {
        // PPM Construction - move to new method later
        

        sprintf(fname, "test%02d.ppm", f) ;
        output.open(fname, std::fstream::out | std::fstream::trunc);    
        output << "P3\n" << frame_width << ' ' << frame_height << "\n255\n";
        //output << "P3\n" << 720 << ' ' << 720 << "\n255\n";
        
        //for(auto shape : shapes)
        //{
        //    shape->rotate_about_y(angle);
        //}

        Vec3 ray_direction = Vec3(0.0, 0.0, viewport_distance);
        Color current;

        // 4 SPP
        float samples_per_pixel     = 4.0;
        float sample_subdivisions   = 4.0; 

        // 16 SPP
        //float samples_per_pixel     = 16.0;
        //float sample_subdivisions   = 8.0; 

        //for (int j = -(frame_height / 2); j < (frame_height / 2); ++j)
        for (int j = (frame_height / 2); j > -(frame_height / 2); --j)
        {
            for (int i = -(frame_width / 2); i < (frame_width / 2); ++i)
            {
                Color total = Color(0, 0, 0);
                //int x = convert_screen_x(i);
                //int y = convert_screen_y(j);
                
                //ray_direction.set(X, convert_viewport_x(float(i)));
                //ray_direction.set(Y, convert_viewport_y(float(j)));

                //float length = ray_direction.length();
                //ray_direction.normalize();
                //ray_direction.rotate_about_y(0.785);
                //ray_direction = ray_direction * length;

                // Super sampling 

                for(int sy = 1; sy < sample_subdivisions; sy += 2)
                {
                    for(int sx = 1; sx < sample_subdivisions; sx += 2)
                    {
                        ray_direction.set(X, convert_viewport_x(float(i) + (float(sx) / sample_subdivisions)));
                        ray_direction.set(Y, convert_viewport_y(float(j) + (float(sy) / sample_subdivisions)));
                        total.unbounded_add(octree.intersect_ray(origin, ray_direction, lights));                        
                    }
                }
                
                total /= samples_per_pixel;
				output << total;
            }
        }

        //theta += angle;


       // std::cout << ray_direction.get(X) << ", " <<  ray_direction.get(Y) << ", " << ray_direction.get(Z) << '\n';
       // std::cout << origin.get(X) << ", " <<  origin.get(Y) << ", " << origin.get(Z) << '\n';

       // std::cout << "Angle: " << angle <<'\n';
        std::cout << f << "frame done!\n";
        output.close();
    }
}
//
//const Color Camera::trace_ray(const Vec3& origin, const Vec3& direction, const float refraction_index, const float t_min, const float t_max, const int recursion_depth, const std::vector<Shape*>& shapes, const std::vector<Light*>& lights)
//{
//	float intensity = 0.0;
//	float closest_t = INFINITY;
//	Shape* closest_shape = nullptr;
//		
//	closest_t = closest_intersection(origin, direction, t_min, t_max, shapes, closest_shape);
//	//if (!closest_shape) return Color(255, 255, 255);	// return background color
//	if (!closest_shape) return Color(135, 206, 235);	// return background color
//	
//	Vec3 point = origin + closest_t * direction;
//	Vec3 normal = closest_shape->get_normal_at_point(point);
//	normal = (normal / normal.length());
//
//	{
//		using namespace std::placeholders;
//		for (auto light : lights)
//		{
//			intensity += light->compute_lighting(point, normal, -direction, closest_shape->get_specularity(), std::bind(&Camera::closest_intersection, this, _1, _2, _3, _4, _5, _6), shapes);
//		}
//		//Color local_color = closest_shape->get_color() * intensity;
//	}
//	Color local_color = closest_shape->get_color() * intensity;
//	float r = closest_shape->get_reflectivity();
//	if (recursion_depth <= 0 || r <= 0) return local_color;
//	
//	// Calculate reflected ray
//	Vec3 reflected = 2.0 * normal * (normal * -direction) + direction;
// 
//	// Recursive call to find reflected color through ray bouncing
//	Color reflected_color = trace_ray(point, reflected, refraction_index, 0.075f, INFINITY, recursion_depth - 1, shapes, lights);
//
//	// Transparency check
//	if (closest_shape->get_refractive_index() < INFINITY)
//	{
//		// Snell's law for angle of refraction ray:
//		
//		// Angle of incidence:
//		// Dot product w/ theta: a * b = ||a||||b||cos(theta)
//		// to
//		// theta = cos^-1((a * b) / ||a||||b||)
//		float a_incidence = std::acos((direction * closest_shape->get_normal_at_point(point)) / 
//							(direction.length() * closest_shape->get_normal_at_point(point).length()));
//
//		// Snell's law for angle of refraction:
//		// (sin(a1) / sin(a2)) = (n2 / n1)
//		// to
//		// a2 = arcsin(sin(a1) * (n1 / n2))
//		float a_refraction = std::asin(std::sin(a_incidence) * (refraction_index / closest_shape->get_refractive_index()));
//
//		//n1(incident x normal) = n2(transmitted x normal)
//
//
//	}
//
//
//	// Return calculated local color weighted by reflectivity and the color from where the ray bounced
//	return (local_color * (1 - r)) + (reflected_color * r);
//}
//
//float Camera::closest_intersection(const Vec3 & origin, const Vec3 & direction, const float t_min, const float t_max, const std::vector<Shape *> & shapes, Shape * & closest_shape)
//{
//	float closest_t = INFINITY;
//	int size = shapes.size();
//	for (int i = 0; i < size; ++i)
//	{
//		Vec3 ts = shapes[i]->intersect_ray(origin, direction);
//
//		if (ts.get(X) >= t_min && ts.get(X) < t_max && ts.get(X) < closest_t)
//		{
//			closest_t = ts.get(X);
//			closest_shape = shapes[i];
//		}
//		if (ts.get(Y) >= t_min && ts.get(Y) < t_max && ts.get(Y) < closest_t)
//		{
//			closest_t = ts.get(Y);
//			closest_shape = shapes[i];
//		}
//	}
//	return closest_t;
//}
//