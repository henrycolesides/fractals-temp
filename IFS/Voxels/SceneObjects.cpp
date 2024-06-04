// SceneObjects.cpp
// Class and function definitions for scene and objects within
// Current implementation provides:
//      Color class for storage and manipulation of RGB color values
//		Light interface and Ambient, Directional, Point lights
//		Shape interface and Sphere geometry class


#include <cmath>
#include "SceneObjects.h"


Color::Color() : values{ 0 } {}

Color::Color(const uint32_t r, const uint32_t g, const uint32_t b)
{
    values[0] = r;
    values[1] = g;
    values[2] = b;
    return;
}

Color::Color(const uint32_t values[3])
{
    for (int i = 0; i < 3; ++i) this->values[i] = values[i];
    return;
}

Color::Color(const uint32_t value)
{
    for (int i = 0; i < 3; ++i) values[i] = value;
    return;
}

uint32_t Color::map_color(const float scalar) const
{
    return
        (values[0] * scalar > 255 ? 255 << 16 : uint32_t(values[0] * scalar) << 16) |
        (values[1] * scalar > 255 ? 255 << 8 : uint32_t(values[1] * scalar) << 8) |
        (values[2] * scalar > 255 ? 255 : uint32_t(values[2] * scalar));
}

Color & Color::operator*=(const float op2)
{
    values[0] = (values[0] * op2 > 255 ? 255 : values[0] * op2);
    values[1] = (values[1] * op2 > 255 ? 255 : values[1] * op2);
    values[2] = (values[2] * op2 > 255 ? 255 : values[2] * op2);
    return *this;
}

Color & Color::operator/=(const float op2)
{
    values[0] = (values[0] / op2 > 255 ? 255 : values[0] / op2);
    values[1] = (values[1] / op2 > 255 ? 255 : values[1] / op2);
    values[2] = (values[2] / op2 > 255 ? 255 : values[2] / op2);
    return *this;
}

Color& Color::operator+=(const float op2)
{
    values[0] = (values[0] + op2 > 255 ? 255 : values[0] + op2);
    values[1] = (values[1] + op2 > 255 ? 255 : values[1] + op2);
    values[2] = (values[2] + op2 > 255 ? 255 : values[2] + op2);
    return *this;
}

Color& Color::operator-=(const float op2)
{
    values[0] = (values[0] - op2 > 255 ? 255 : values[0] - op2);
    values[1] = (values[1] - op2 > 255 ? 255 : values[1] - op2);
    values[2] = (values[2] - op2 > 255 ? 255 : values[2] - op2);
    return *this;
}

Color operator*(const Color& op1, const Color& op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] * op2.values[0] > 255 ? 255 : temp.values[0] * op2.values[0]);
    temp.values[1] = (temp.values[1] * op2.values[1] > 255 ? 255 : temp.values[1] * op2.values[1]);
    temp.values[2] = (temp.values[2] * op2.values[2] > 255 ? 255 : temp.values[2] * op2.values[2]);
    return temp;
}

Color operator*(const Color& op1, const float op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] * op2 > 255 ? 255 : temp.values[0] * op2);
    temp.values[1] = (temp.values[1] * op2 > 255 ? 255 : temp.values[1] * op2);
    temp.values[2] = (temp.values[2] * op2 > 255 ? 255 : temp.values[2] * op2);
    return temp;
}

Color operator*(const float op1, const Color& op2)
{
    Color temp = Color(op2);
    temp.values[0] = (temp.values[0] * op1 > 255 ? 255 : temp.values[0] * op1);
    temp.values[1] = (temp.values[1] * op1 > 255 ? 255 : temp.values[1] * op1);
    temp.values[2] = (temp.values[2] * op1 > 255 ? 255 : temp.values[2] * op1);
    return temp;
}

Color operator/(const Color& op1, const Color& op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] / op2.values[0] > 255 ? 255 : temp.values[0] / op2.values[0]);
    temp.values[1] = (temp.values[1] / op2.values[1] > 255 ? 255 : temp.values[1] / op2.values[1]);
    temp.values[2] = (temp.values[2] / op2.values[2] > 255 ? 255 : temp.values[2] / op2.values[2]);
    return temp;
}

Color operator/(const Color& op1, const float op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] / op2 > 255 ? 255 : temp.values[0] / op2);
    temp.values[1] = (temp.values[1] / op2 > 255 ? 255 : temp.values[1] / op2);
    temp.values[2] = (temp.values[2] / op2 > 255 ? 255 : temp.values[2] / op2);
    return temp;
}

Color operator/(const float op1, const Color& op2)
{
    Color temp = Color(op2);
    temp.values[0] = (temp.values[0] / op1 > 255 ? 255 : temp.values[0] / op1);
    temp.values[1] = (temp.values[1] / op1 > 255 ? 255 : temp.values[1] / op1);
    temp.values[2] = (temp.values[2] / op1 > 255 ? 255 : temp.values[2] / op1);
    return temp;
}

Color operator+(const Color& op1, const Color& op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] + op2.values[0] > 255 ? 255 : temp.values[0] + op2.values[0]);
    temp.values[1] = (temp.values[1] + op2.values[1] > 255 ? 255 : temp.values[1] + op2.values[1]);
    temp.values[2] = (temp.values[2] + op2.values[2] > 255 ? 255 : temp.values[2] + op2.values[2]);
    return temp;
}

Color operator+(const Color& op1, const float op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] / op2 > 255 ? 255 : temp.values[0] / op2);
    temp.values[1] = (temp.values[1] / op2 > 255 ? 255 : temp.values[1] / op2);
    temp.values[2] = (temp.values[2] / op2 > 255 ? 255 : temp.values[2] / op2);
    return temp;
}

Color operator+(const float op1, const Color& op2)
{
    Color temp = Color(op2);
    temp.values[0] = (temp.values[0] + op1 > 255 ? 255 : temp.values[0] + op1);
    temp.values[1] = (temp.values[1] + op1 > 255 ? 255 : temp.values[1] + op1);
    temp.values[2] = (temp.values[2] + op1 > 255 ? 255 : temp.values[2] + op1);
    return temp;
}

Color operator-(const Color& op1, const Color& op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] - op2.values[0] > 255 ? 255 : temp.values[0] - op2.values[0]);
    temp.values[1] = (temp.values[1] - op2.values[1] > 255 ? 255 : temp.values[1] - op2.values[1]);
    temp.values[2] = (temp.values[2] - op2.values[2] > 255 ? 255 : temp.values[2] - op2.values[2]);
    return temp;
}

Color operator-(const Color& op1, const float op2)
{
    Color temp = Color(op1);
    temp.values[0] = (temp.values[0] - op2 > 255 ? 255 : temp.values[0] - op2);
    temp.values[1] = (temp.values[1] - op2 > 255 ? 255 : temp.values[1] - op2);
    temp.values[2] = (temp.values[2] - op2 > 255 ? 255 : temp.values[2] - op2);
    return temp;
}

Color operator-(const float op1, const Color& op2)
{
    Color temp = Color(op2);
    temp.values[0] = (temp.values[0] - op1 > 255 ? 255 : temp.values[0] - op1);
    temp.values[1] = (temp.values[1] - op1 > 255 ? 255 : temp.values[1] - op1);
    temp.values[2] = (temp.values[2] - op1 > 255 ? 255 : temp.values[2] - op1);
    return temp;
}

std::ostream & operator<<(std::ostream & out, const Color & op2)
{
    out << op2.values[0] << ' ' << op2.values[1] << ' ' << op2.values[2] << '\n';
    return out;
}

// Shape destructor
Shape::~Shape() { return; }

// Sphere class
Sphere::Sphere() : position(Vec3()), radius(0.0), color(Color()), specularity(-1.0), reflectivity(0.0), refractive_index(INFINITY) {}
Sphere::Sphere(const Vec3& position, const float radius, const Color& color, const float specularity, const float reflectivity, const float refractive_index)
   : position(position), radius(radius), color(color), specularity(specularity), reflectivity(reflectivity), refractive_index(refractive_index) { }

uint32_t Sphere::map_color()
{
    return color.map_color();
}

uint32_t Sphere::map_color(const float scalar) const
{
    return color.map_color(scalar);
}

const Vec3 & Sphere::get_position() const
{
    return position;
}

Vec3 Sphere::get_normal_at_point(const Vec3& point) const
{
    return point - position;
}

const Color & Sphere::get_color() const
{
    return color;
}

const float Sphere::get_specularity() const
{
    return specularity;
}

const float Sphere::get_reflectivity() const
{
    return reflectivity;
}

const float Sphere::get_refractive_index() const
{
    return refractive_index;
}

void Sphere::scale_color(const float scalar)
{
    color *= scalar;
    return;
}

void Sphere::rotate_about_y(const float angle)
{
    return;
}

Vec3 Sphere::intersect_ray(const Vec3 & origin, const Vec3 & direction) const
{
    Vec3 CO = origin - position;

    float a = direction * direction;
    float b = 2 * (CO * direction);
    float c = (CO * CO) - (radius * radius);

    float discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0.0)
    {
        return Vec3(INFINITY, INFINITY, 0);
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2 * a);
    return Vec3(t1, t2, 0.0);
}

// Sphere class
Triangle::Triangle() : a(Vec3()), b(Vec3()), c(Vec3()), normal(Vec3()), color(Color()), specularity(-1.0), reflectivity(0.0), refractive_index(INFINITY) {}
Triangle::Triangle(const Vec3& a, const Vec3 & b, const Vec3 & c, const Color& color, const float specularity, const float reflectivity, const float refractive_index)
 : a(a), b(b), c(c), color(color), specularity(specularity), reflectivity(reflectivity), refractive_index(refractive_index)
{
    Vec3 ab = b - a;
    Vec3 bc = c - b;
    normal = cross(ab, bc);
    return;
}

uint32_t Triangle::map_color()
{
	return color.map_color();
}

uint32_t Triangle::map_color(const float scalar) const
{
	return color.map_color(scalar);
}

const Vec3 & Triangle::get_position() const
{
    return a;
}

Vec3 Triangle::get_normal_at_point(const Vec3& point) const
{
    return normal;
}

const Color & Triangle::get_color() const
{
    return color;
}

const float Triangle::get_specularity() const
{
    return specularity;
}

const float Triangle::get_reflectivity() const
{
    return reflectivity;
}

const float Triangle::get_refractive_index() const
{
    return refractive_index;
}
//void Triangle::scale_color(const float scalar)
//{
//	color *= scalar;
//	return;
//}

void Triangle::rotate_about_y(const float angle)
{
    a.rotate_about_y(angle);
    b.rotate_about_y(angle);
    c.rotate_about_y(angle); 
    Vec3 ab = b - a;
    Vec3 bc = c - b;
    normal = cross(ab, bc);
    return;
}

Vec3 Triangle::intersect_ray(const Vec3& origin, const Vec3& direction) const
{
    // If ray is parallel, return invalid t's (with t_min always > 0, a return x or y of zero means not valid)
    float n_dot_d = normal * direction;
    if (n_dot_d == 0) return Vec3(0.0, 0.0, 0.0);
    
    float t = ((normal * a) - (normal * origin)) / n_dot_d;
    
    // If ray is not visible, return invalid t
    // Need to do this step here because we must calculate point 
    // For inside-outside check
    if (t < 0) return Vec3(0.0, 0.0, 0.0);

    // Inside-outside check
    // Is the intersection point in the triangle?
    Vec3 point = origin + t * direction;
    Vec3 C;

    C = cross(b - a, point - a);
    if (normal * C < 0) return Vec3(0.0, 0.0, 0.0);

    C = cross(c - b, point - b);
    if (normal * C < 0) return Vec3(0.0, 0.0, 0.0);

    C = cross(a - c, point - c);
    if (normal * C < 0) return Vec3(0.0, 0.0, 0.0);
    
    return Vec3(t, 0.0, 0.0);
}



// ABC interface for all light classes
Light::Light() : INTENSITY(0.0) {}
Light::Light(const float INTENSITY) : INTENSITY(INTENSITY) {}
Light::~Light() { return; }



AmbientLight::AmbientLight() {}
AmbientLight::AmbientLight(const float INTENSITY) : Light(INTENSITY) {}
//float AmbientLight::compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity)
float AmbientLight::compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity)
{
    return INTENSITY;
}

Vec3 AmbientLight::get_direction(Vec3 & point)
{
    return Vec3(0.0, 0.0, 0.0);
}



DirectionalLight::DirectionalLight() : direction(Vec3()) {}
DirectionalLight::DirectionalLight(const float INTENSITY, const Vec3 & direction) : Light(INTENSITY), direction(direction) { return; }

//float DirectionalLight::compute_lighting(const Vec3 & point, const Vec3 & normal, const Vec3 & view, const float specularity)
float DirectionalLight::compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity)
{
    float i = 0.0;
    Vec3 L = direction;
    float n_dot_l = L * normal;
    float t_max = INFINITY;

    // Shadow check
//    Sphere* shadow_sphere = nullptr;
    Shape * shadow_shape = nullptr;
    //closest_intersection(point, L, 0.001f, t_max, shapes, shadow_shape);

    if (shadow_shape) return i;

    // Diffuse reflection (matte)
    if (n_dot_l > 0) // Make sure we don't add negative spaces (if n_dot_l <= 0)
    {
        //i += (intensity * (n_dot_l / N.length()) * L.length());
        i += (INTENSITY * n_dot_l / (normal.length() * L.length()));
    }

    // Specular reflection(shiny)
    if (specularity != -1) // if surface is shiny
    {
        Vec3 R = (2.0 * normal * (n_dot_l)) - L;
        float r_dot_v = R * view;
        if (r_dot_v > 0) // Make sure we don't add negative light intensity
        {
            i += (INTENSITY * std::pow(r_dot_v / (R.length() * view.length()), specularity));
        }
    }
    return i;
}

Vec3 DirectionalLight::get_direction(Vec3 & point)
{
    return direction;
}


PointLight::PointLight() : position(Vec3()) { return; }
PointLight::PointLight(const float INTENSITY, const Vec3 & position) : Light(INTENSITY), position(position) { return; }

//float PointLight::compute_lighting(const Vec3 & point, const Vec3 & normal, const Vec3 & view, const float specularity)
float PointLight::compute_lighting(const Vec3& point, const Vec3& normal, const Vec3& view, const float specularity)
{
    float i = 0.0;
    Vec3 L = position - point;
    float n_dot_l = L * normal;
    float t_max = 1;

    Shape * shadow_shape = nullptr;
    //closest_intersection(point, L, 0.001f, t_max, shapes, shadow_shape);
    if (shadow_shape) return i;

    if (n_dot_l > 0) // Make sure we don't add negative spaces (if n_dot_l <= 0)
    {
        //i += (intensity * (n_dot_l / N.length()) * L.length());
        i += (INTENSITY * n_dot_l / (normal.length() * L.length()));
    }

    // Specular reflection(shiny)
    if (specularity != -1) // if surface is shiny
    {
        Vec3 R = (2.0 * normal * (n_dot_l)) - L;
        float r_dot_v = R * view;
        if (r_dot_v > 0) // Make sure we don't add negative light intensity
        {
            i += (INTENSITY * std::pow(r_dot_v / (R.length() * view.length()), specularity));
        }
    }
    return i;
}

Vec3 PointLight::get_direction(Vec3 & point)
{
    return position;
}

