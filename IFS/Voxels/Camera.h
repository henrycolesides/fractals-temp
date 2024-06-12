// Camera.h
// Provides declaration for Camera class
// Camera holds position and orientation data
// Camera traces rays through the scene, tracking collisions with scene objects

#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include "Octree.h"
#include "VectorMath.h"
#include "SceneObjects.h"

class Camera
{
	public:
		Camera();
		Camera(const Vec3 & origin, const uint32_t frame_width, const uint32_t frame_height,
			const float viewport_width, const float viewport_height, const float viewport_distance);

		void render(Octree & octree, const std::vector<Light *> & lights);
	//	const Color trace_ray(const Vec3 & origin, const Vec3 & direction, const float refraction_index, const float t_min, const float t_max, const int recursion_depth, const std::vector<Shape *> & shapes, const std::vector<Light *> & lights);
	//	float closest_intersection(const Vec3 & origin, const Vec3 & direction, const float t_min, const float t_max, const std::vector<Shape *> & shapes, Shape * & closest_shape);

	private:
		Vec3 origin;
		int32_t frame_width;
		int32_t frame_height;
		float viewport_width;
		float viewport_height;
		float viewport_distance;
		

		int32_t convert_screen_x(const int32_t cx) const { return (frame_width / 2) + cx; }
		int32_t convert_screen_y(const int32_t cy) const { return (frame_height / 2) + cy; }
		float convert_viewport_x(const float cx) const { return ((float)cx) * (viewport_width / (float)frame_width); }
		float convert_viewport_y(const float cy) const { return ((float)cy) * (viewport_height / (float)frame_height); }
};

#endif // CAMERA_H
