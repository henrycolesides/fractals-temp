// SceneObjects.h
// Provides required class and function declarations for the scene and objects within
// Current implementation provides:
//		light interface, ambient, point, directional light classes
//		shape interface, sphere geometry class 

#ifndef SCENEOBJECTS_H
#define SCENEOBJECTS_H

#include <stdint.h>
#include <functional>
#include <vector>
#include <iostream>
#include "RaytracerMath.h"


// Color class
// Represents some RGB color by three 32-bit integer values
// Upon a map_color call, bit shifts R, G, and B into correct positions before outputting
class Color
{
	public:
		Color();
		Color(const uint32_t r, const uint32_t g, const uint32_t b);
		Color(const uint32_t values[3]);
		Color(const uint32_t value);

		static inline uint32_t map_color(uint32_t r, uint32_t g, uint32_t b) { return (r << 16) | (g << 8) | (b); }
		inline uint32_t map_color() const { return (values[0] << 16) | (values[1] << 8) | (values[2]); }
		uint32_t map_color(const float scalar) const;

		Color& operator*=(const float op2);
		Color& operator/=(const float op2);
		Color& operator+=(const float op2);
		Color& operator-=(const float op2);
			
		friend Color operator*(const Color & op1, const Color & op2);
		friend Color operator*(const Color & op1, const float op2);
		friend Color operator*(const float op1, const Color & op2);
		
		friend Color operator/(const Color & op1, const Color & op2);
		friend Color operator/(const Color & op1, const float op2);
		friend Color operator/(const float op1, const Color & op2);
		
		friend Color operator+(const Color & op1, const Color & op2);
		friend Color operator+(const Color & op1, const float op2);
		friend Color operator+(const float op1, const Color & op2);
		
		friend Color operator-(const Color & op1, const Color & op2);
		friend Color operator-(const Color & op1, const float op2);
		friend Color operator-(const float op1, const Color & op2);

        friend std::ostream & operator<<(std::ostream & out, const Color & op2);

	private:
		uint32_t values[3];
};


class Shape
{
	public:
		virtual ~Shape() = 0;
		virtual Vec3 intersect_ray(const Vec3& origin, const Vec3& direction) const = 0;

		virtual uint32_t map_color() = 0;
		virtual uint32_t map_color(const float scalar) const = 0;
	
		virtual const Vec3 & get_position() const = 0;
		virtual Vec3 get_normal_at_point(const Vec3& point) const = 0;
		virtual const Color & get_color() const = 0;
		virtual const float get_specularity() const = 0;	// Will move specularity and related functions into material class
		virtual const float get_reflectivity() const = 0;
		virtual const float get_refractive_index() const = 0;
        virtual void rotate_about_y(const float angle) = 0;
};


class Sphere : public Shape
{
	public:
		Sphere();
		Sphere(const Vec3 & position, const float radius, const Color & color, const float specularity, const float reflectivity, const float refractive_index);
		
		uint32_t map_color();
		uint32_t map_color(const float scalar) const;
		void scale_color(const float scalar);
	
		const Vec3 & get_position() const;
		Vec3 get_normal_at_point(const Vec3& point) const;
		const Color & get_color() const;
		const float get_specularity() const;
		const float get_reflectivity() const;
		const float get_refractive_index() const;
        void rotate_about_y(const float angle);

		Vec3 intersect_ray(const Vec3 & origin, const Vec3 & direction) const;

	private:
		Vec3 position;
		float radius;
		Color color;
		float specularity;  // Specular constant
		// Exponent of cos(angle between view and R)
		// Where view is the view vector from point P to the camera
		// And R is the reflection vecter from incident ray of light L 
		//  (reflected across some surface's normal)
		float reflectivity;
		float refractive_index;
};


class Triangle : public Shape
{
	public:
		Triangle();
		Triangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, const Color& color, const float specularity, const float reflectivity, const float refractive_index);
		
		uint32_t map_color();
		uint32_t map_color(const float scalar) const;
		
		const Vec3 & get_position() const;
		Vec3 get_normal_at_point(const Vec3& point) const;
		const Color & get_color() const;
		const float get_specularity() const;
		const float get_reflectivity() const;
		const float get_refractive_index() const;
        void rotate_about_y(const float angle);

		Vec3 intersect_ray(const Vec3& origin, const Vec3& direction) const;

	private:
		Vec3 a;
		Vec3 b;
		Vec3 c;
		Vec3 normal;
		Color color;
		float specularity;
		float reflectivity;
		float refractive_index;
};



// Light interface as an abstract base class. Provides const float INTENSITY and float compute_lighting()
// to be implemented by all children for lighting calculations
class Light
{
public:
	Light();
	Light(const float INTENSITY);
	virtual ~Light() = 0;

//float Camera::closest_intersection(const Vec3 & origin, const Vec3 & direction, const float t_min, const float t_max, const std::vector<Shape *> & shapes, Shape * & closest_shape)
	virtual float compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity, const std::function<float(const Vec3 &, const Vec3 &, const float, const float, const std::vector<Shape *> &, Shape * &)> & closest_intersection, const std::vector<Shape *> & shapes) = 0;

protected:
	const float INTENSITY;
};



// AmbientLight class to simulate ambient lighting
// Implements compute_lighting, which returns intensity
class AmbientLight : public Light
{
	public:
		AmbientLight();
		AmbientLight(const float INTENSITY);

		// Compute lighting for some point P with normal N
	//	float compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity);
		float compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity, const std::function<float(const Vec3 &, const Vec3 &, const float, const float, const std::vector<Shape *> &, Shape * &)> & closest_intersection, const std::vector<Shape *> & shapes);
};



// DirectionalLight class to simulate directional lighting
// Implements compute_lighting(), which performs diffuse and specular reflection calculations 
// based on the object's direction and intensity
class DirectionalLight : public Light
{
	public:
		DirectionalLight();
		DirectionalLight(const float INTENSITY, const Vec3 & direction);

	//	float compute_lighting(const Vec3 & point, const Vec3 & normal, const Vec3 & view, const float specularity);
		float compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity, const std::function<float(const Vec3 &, const Vec3 &, const float, const float, const std::vector<Shape *> &, Shape * &)> & closest_intersection, const std::vector<Shape *> & shapes);

	private:
		Vec3 direction;
};



// PointLight class to simulate some point of lighting
// Implements compute_lighting(), which performs diffuse and specular reflection calculations
// based on the object's position and intensity
class PointLight : public Light
{
	public:
		PointLight();
		PointLight(const float INTENSITY, const Vec3 & position);

		//float compute_lighting(const Vec3 & point, const Vec3 & normal, const Vec3 & view, const float specularity);
		float compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity, const std::function<float(const Vec3 &, const Vec3 &, const float, const float, const std::vector<Shape *> &, Shape * &)> & closest_intersection, const std::vector<Shape *> & shapes);

	private:
		Vec3 position;
};
#endif
