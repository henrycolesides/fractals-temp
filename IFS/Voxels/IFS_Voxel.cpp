// IFS_Voxel.cpp
// Main entry point into IFS voxel renderer

#include <random>
#include "IFS_Voxel.h"
#include "Camera.h"

#define SWIDTH 720
#define SHEIGHT 720

using std::min;

void fern_chaos(Octree * & my_tree, const Vec3 location, const float scale, const float bend, const float rotation, const int iterations);
void fern(Vec3 & p, const float r, const float bend);
void sierpinski(Vec3 & p, const float r, Color & color);

// Complex
bool mandelbulb(Vec3 z, const int power, float & length, float & axis);
float normalize(const float value, const float old_min, const float old_max);
Color lerp(const Color & from, const Color & to, const float t);
Color lerp3(const Color & from, const Color & middle, const Color & to, const float t);

float randomFloatBetweenMinus1And1() {
    // Create a random number generator engine
    std::random_device rd;  // Non-deterministic random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine seeded with the random device

    // Create a uniform real distribution between -1 and 1
    std::uniform_real_distribution<float> dis(-1.0f, 1.0f);

    // Generate and return the random float
    return dis(gen);
}



int main()
{
    // Fern
    //Bounds initial_bounds = {Vec3(-1.0, -1.0, -1.0), Vec3(1.0, 1.0, 1.0)};
    //Bounds floor_bounds = {Vec3(-1.0, -3.0, -1.0), Vec3(1.0, -1.0, 1.0)};
    //Octree * my_tree = new Octree(initial_bounds, floor_bounds, 10);

    //// IFS Production

    //// Main fern
    //fern_chaos(my_tree, Vec3(0.0, -1.0, 0.0), 1.0, 2.34, -20.0, 10000000);

    ////fern_chaos(my_tree, Vec3(-0.2, -1.0, -0.2), 0.1, 5.0, 45, 10000);
    ////fern_chaos(my_tree, Vec3(-0.22, -1.0, -0.22), 0.1, 5.0, -135, 10000);
   
    //Camera camera = Camera(Vec3(0.01, -0.4, -1.5), SWIDTH, SHEIGHT, 1.0, 1.0, 1.0);
    
    //std::vector<Light *> lights;
    //lights.push_back(new AmbientLight(0.1f));
    //lights.push_back(new PointLight(0.2f, Vec3(2.0, 2.0, -2.0)));
    //lights.push_back(new DirectionalLight(0.7f, Vec3(-1.0, 2.0, -1.0))); 


    // Mandelbulb
    int level_of_detail = 8;
    Bounds initial_bounds = {Vec3(-2.0, -2.0, -2.0), Vec3(2.0, 2.0, 2.0)};
    Octree * my_tree = new Octree(initial_bounds, level_of_detail);

    float range = pow(2, level_of_detail + 1);
    float step = 4.0 / range;
    step *= 2.0;

    Vec3 p;
    float length, axis;
    float max = 0.0;
    float min = 10000.0;

    float max_axis = 0.0;
    float min_axis = 100000.0;

    float min_distance_o = 0.0;
    float max_distance_o = 0.799139;
    
    float normalized_o = 0.0;
    float max_normalized_o = 0.0;

    float min_distance_a = 0.0;
    float max_distance_a = 0.552343;

    float normalized_a = 0.0;
    float max_normalized_a = 0.0;

    for(float x = -2.0; x < 2.0; x += step)
    {
        for(float y = -2.0; y < 2.0; y += step)
        {
            for(float z = -2.0; z < 2.0; z += step)
            {
                p = Vec3(x, y, z);
                length = 10000.0;
                axis = 10000.0;
                if(mandelbulb(p, 8, length, axis))
                {
                    if(length > max) max = length;
                    if(length < min) min = length;

                    if(axis > max_axis) max_axis = axis;
                    if(axis < min_axis) min_axis = axis;

                    p.rotate_about_x(200.0);
                    //p.rotate_about_x(20.0);
                    p.rotate_about_y(-20.0);

                    normalized_o = normalize(length, min_distance_o, max_distance_o);
                    if(normalized_o > max_normalized_o) max_normalized_o = normalized_o;

                    normalized_a = normalize(axis, min_distance_a, max_distance_a);
                    if(normalized_a > max_normalized_a) max_normalized_a = normalized_a;

                    Color c1 = lerp(Color(255, 0, 0), Color(255, 255, 255), normalized_o);
                    Color c2 = lerp(c1, Color(0, 200, 200), pow(normalized_a, 1.5));

                    //my_tree->insert(p, lerp3(Color(25, 25, 112), Color(255, 215, 0), Color(60, 179, 113), (normalized * normalized)));
                    //my_tree->insert(p, lerp3(Color(255, 20, 147), Color(60, 179, 113), Color(25, 25, 112), (pow(normalized, 0.75))));
                    //my_tree->insert(p, lerp(Color(255, 215, 0), Color(25, 25, 112), (pow(normalized, 0.75))));
                    //my_tree->insert(p, lerp3(Color(255, 20, 147), Color(60, 179, 113), Color(155, 26, 255), (normalized * normalized)));
                    my_tree->insert(p, c2);
                }
            }
        }
    }

    std::cout << "Max: " << max << ", Min: " << min << ", N Range: " << max_normalized_a << '\n'; 
    std::cout << "Max Axis: " << max_axis << ", Min Axis: " << min_axis << ", N Range: " << max_normalized_a << '\n'; 
    Camera camera = Camera(Vec3(0.01, 0.0, -4.0), SWIDTH, SHEIGHT, 1.0, 1.0, 1.0);


    std::vector<Light *> lights;
    lights.push_back(new AmbientLight(0.15f));
    lights.push_back(new PointLight(0.15f, Vec3(4.0, 4.0, -4.0)));
    lights.push_back(new DirectionalLight(0.7f, Vec3(-3.0, 4.0, -3.0))); 

    //lights.push_back(new AmbientLight(0.2f));
    ////lights.push_back(new DirectionalLight(0.8f, Vec3(2.0, 2.0, -2.0)));
    //lights.push_back(new DirectionalLight(0.8f, Vec3(-1.0, 2.0, -1.0))); 


    //lights.push_back(new DirectionalLight(1.0f, Vec3(0.0, 2.0, -0.5))); 
    
    //lights.push_back(new PointLight(0.6f, Vec3(2.0, 1.0, 0.0)));
    //lights.push_back(new DirectionalLight(0.8f, Vec3(2.0, 0.5, 0.0)));
    //lights.push_back(new DirectionalLight(0.8f, Vec3(, 1.0, -500.0)));   
    //lights.push_back(new PointLight(0.8f, Vec3(2.0, 2.0, -2.0)));
    
    
    
    //lights.push_back(new DirectionalLight(0.6f, Vec3(-100.0, 0.0, -2.0)));
    //lights.push_back(new DirectionalLight(0.4f, Vec3(2.0, 0.5, -2.0)));   
    //lights.push_back(new DirectionalLight(1.0f, Vec3(-0.5, 1.0, -2.0)));   
    

    camera.render(*my_tree, lights);
    delete my_tree;

    while(!lights.empty())
    {
        delete lights.back();
        lights.pop_back();
    }
}

void fern_chaos(Octree * & my_tree, const Vec3 location, const float scale, const float bend, const float rotation, const int iterations)
{
    Vec3 p = Vec3(0.0, 0.0, 0.0);
    float r;
 
    Color color = Color(20, 220, 40);

    Vec3 scale_down = Vec3(1.0, 1.0, 1.0) * scale;
    Vec3 scale_up = Vec3(1.0, 1.0, 1.0) / scale;

    // Main fern
    for(int i = 0; i < iterations; ++i)
    {
        r = drand48();
        if(i > 20)
        {
            fern(p, r, bend);
            p.scale(scale_down);
            p.rotate_about_y(rotation);
            p += location;
            
            my_tree->insert(Vec3(p), color); 

            p -= location;
            p.rotate_about_y(-rotation);
            p.scale(scale_up);
        }
    }
}

void fern(Vec3 & p, const float r, const float bend)
{
    if(r < 0.1)
    {
        // Full size
        p.scale(Vec3(0.01, 0.16, 0.01));
    }
    else if(r < 0.86)
    {
        // Full size
        p.scale(Vec3(0.9, 0.85, 0.85));
        
        // Original
        //p.rotate_about_z(-3.69);

        // Bendy
        p.rotate_about_x(bend);

        // More bendy
        //p.rotate_about_x(8.73);

        // Swirly 
        p.rotate_about_y(20.0);
            
        p += (Vec3(0.0, 0.16, 0.0));
    }
    else if(r < 0.93)
    {
        p.rotate_about_z(90.0);
        p.rotate_about_x(50.0);
        p.rotate_about_z(-90.0);
        p.rotate_about_z(-3.45);

        // Full size
        p.scale(Vec3(0.3, 0.46, 0.28));

        p.rotate_about_z(52.85);
        p.rotate_about_y(-20.0);

        p += (Vec3(0.0, 0.055, 0.0));
    }
    else
    {
        p.rotate_about_z(90.0);
        p.rotate_about_x(50.0);
        p.rotate_about_z(-90.0);
        p.rotate_about_z(20.82);

        // Full size
        p.scale(Vec3(0.3, -0.5, 0.3));
        
        p.rotate_about_z(136.65);
        p.rotate_about_y(20.0);

        p += Vec3(0.0, 0.044, 0.0);
    }
}

void sierpinski(Vec3 & p, const float r, Color & color)
{
    if(r < 0.25)
    {
        p.scale(Vec3(0.5, 0.5, 0.5));
        color = Color(255, 0, 0);
    }    
    else if(r < 0.5)
    {
        p.scale(Vec3(0.5, 0.5, 0.5));
        p += Vec3(0.25, 0.0, 0.5);
        color = Color(0, 255, 0);
    }
    else if(r < 0.75)
    {
        p.scale(Vec3(0.5, 0.5, 0.5));
        p += Vec3(0.5, 0.0, 0.0);
        color = Color(0, 0, 255);
    }
    else
    {
        p.scale(Vec3(0.5, 0.5, 0.5));
        p += Vec3(0.25, 0.5, 0.25);
        color = Color(255, 255, 0);
    }
}



bool mandelbulb(Vec3 c, const int power, float & length, float & axis_distance)
{
    Vec3 v = Vec3(0.0, 0.0, 0.0);

    float r;        // Radial line
    float theta;    // Polar angle
    float phi;      // Azimuthal angle
    float m;

    float xdistance;
    float ydistance;
    float zdistance;
    float smallest_distance;

    for(int i = 0; i < 100; ++i)
    {
        r = v.length();
        theta = atan2(sqrt(v.get(X)*v.get(X) + v.get(Y)*v.get(Y)), v.get(Z));
        phi = atan2(v.get(Y), v.get(X));

        r = pow(r, power);
        theta *= power;
        phi *= power;

        v = Vec3(r * sin(theta) * cos(phi),
                r * sin(theta) * sin(phi),
                r * cos(theta));
        v += c;

        m = v.length(); 

        if(m > 2.0) return false;
        if(m < length) length = m;

        xdistance = sqrt((v.get(Y) * v.get(Y)) + (v.get(Z) * v.get(Z)));
        ydistance = sqrt((v.get(X) * v.get(X)) + (v.get(Z) * v.get(Z)));
        zdistance = sqrt((v.get(Y) * v.get(Y)) + (v.get(X) * v.get(X)));
        smallest_distance = min(min(xdistance, ydistance), zdistance);
        if(smallest_distance < axis_distance) axis_distance = smallest_distance;

    }
    return true;
}

float normalize(const float value, const float old_min, const float old_max)
{
    return (value - old_min) / (old_max - old_min);
}