// VectorMath.h
// Provides declarations for necessary mathematics classes and functions for a Voxel IFS renderer
// Extendended from my RaytracerMath.h

#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <vector>
#include <iostream>

#define X 'x'
#define Y 'y'
#define Z 'z'

class Shape;

class Vec3
{

	public:
		Vec3();
		Vec3(const float x, const float y, const float z);

		// Negate
		Vec3 operator-() const;

		// Dot product
		float operator*(const Vec3& op2) const;

		Vec3 operator+(const Vec3& op2) const;
		Vec3& operator+=(const Vec3& op2);
		Vec3 operator-(const Vec3& op2) const;
		Vec3& operator-=(const Vec3& op2);

		bool operator==(const Vec3& op2) const;
		bool operator!=(const Vec3& op2) const;

		// Scalar members
		Vec3& operator*=(const float op2);
		Vec3& operator/=(const float op2);
        
        void rotate_about_y(const float angle);

		// Scalar friends
		friend Vec3 operator*(const Vec3& op1, const float op2);
		friend Vec3 operator*(const float op1, const Vec3& op2);
		friend Vec3 operator/(const Vec3& op1, const float op2);
		friend Vec3 operator/(const float op1, const Vec3& op2);
    
        friend std::ostream & operator<<(std::ostream & out, const Vec3& op2);

		friend Vec3 cross(const Vec3& op1, const Vec3& op2);

		friend void koch_snowflake3d(const Vec3& a, const Vec3& b, const Vec3& c, int depth, int max, std::vector<Shape *> & shapes);
		friend float distance_between_points(const Vec3& op1, const Vec3& op2);

		float length() const;
		void set(const char dimension, const float value);
		float get(const char dimension) const;
	private:
		float values[3];
};
#endif // VECTORMATH_H
