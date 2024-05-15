#include <stdint.h>
#include <iostream>
#include <vector>
#include "PPMRaytracer.h"


void cube(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int depth, const int max, std::vector<Shape *> & shapes);
void pyth_tree_3d(const Vec3& a, const Vec3& b, const Vec3& c, const Vec3& d, int depth, const int max, std::vector<Shape *> & shapes);
int main()
{
    int width = 720;
    int height = 720;

    // Setup pixel buffer
    uint32_t * pixels = new uint32_t[width * height];

    // Setup scene:    
    std::vector<Shape *> shapes;

    // 3D Koch Snowflake scene
    //
    //Point 1: (-0.5, 0.0, 0.0)
    //Point 2: (0.5, 0.0, 0.0)
    //Point 3: (0.0, 0.866, 0.0)
    //Triangle 2:
    //
    //Point 1: (-0.5, 0.0, -0.408)
    //Point 2: (0.0, 0.866, 0.0)
    //Point 3: (0.5, 0.0, -0.408)
    //Triangle 3:
    //
    //Point 1: (0.5, 0.0, -0.408)
    //Point 2: (0.0, 0.866, 0.0)
    //Point 3: (0.0, 0.0, 0.0)
    //Triangle 4:
    //
    //Point 1: (-0.5, 0.0, -0.408)
    //Point 2: (0.5, 0.0, -0.408)
    //Point 3: (0.0, 0.0, 0.0)

   // shapes.push_back(new Sphere((Vec3(0.0, -5005.0, 0.0)), 5000.0, Color(255, 0, 0), 1000.0, 0.5f, 1.3f));
   // 
   // shapes.push_back(new Triangle(Vec3(-0.5, 0.0, 0.0), Vec3(0.5, 0.0, 0.0), Vec3(0.0, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
   // shapes.push_back(new Triangle(Vec3(-0.5, 0.0, -0.408), Vec3(0.0, 0.866, 0.0), Vec3(0.5, 0.0, -0.408), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
   // shapes.push_back(new Triangle(Vec3(0.5, 0.0, -0.408), Vec3(0.0, 0.866, 0.0), Vec3(0.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
   // shapes.push_back(new Triangle(Vec3(-0.5, 0.0, -0.408), Vec3(0.5, 0.0, -0.408), Vec3(0.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
 
   // koch_snowflake3d(Vec3(-0.5, 0.0, 0.0), Vec3(0.5, 0.0, 0.0), Vec3(0.0, 0.866, 0.0), 1, 2, shapes);
   // koch_snowflake3d(Vec3(-0.5, 0.0, -0.408), Vec3(0.0, 0.866, 0.0), Vec3(0.5, 0.0, -0.408), 1, 2, shapes);
   // koch_snowflake3d(Vec3(0.5, 0.0, -0.408), Vec3(0.0, 0.866, 0.0), Vec3(0.0, 0.0, 0.0), 1, 2, shapes);
   // koch_snowflake3d(Vec3(-0.5, 0.0, -0.408), Vec3(0.5, 0.0, -0.408), Vec3(0.0, 0.0, 0.0),  1, 2, shapes);
    
    //shapes.push_back(new Sphere((Vec3(0.0, -5005.0, 0.0)), 5000.0, Color(255, 0, 0), 1000.0, 0.5f, 1.3f));
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
    //shapes.push_back(new Triangle(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f, 1.3f));  
    //
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), 1, 2, shapes);
    //koch_snowflake3d(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), 1, 2, shapes);
   
    // Cube check
    Vec3 a = Vec3(0.0, -1.0, 1.0);
    Vec3 b = Vec3(1.0, -1.0, 1.0);
    Vec3 c = Vec3(0.0, -1.0, 0.0);
    Vec3 d = Vec3(1.0, -1.0, 0.0);
   
   a.rotate_about_y(0.5);
   b.rotate_about_y(0.5);
   c.rotate_about_y(0.5);
   d.rotate_about_y(0.5);
    
    cube(a, b, c, d, 0, 6, shapes);
 
    //pyth_tree_3d(a, b, c, d, 0, 1, shapes);  

    // Lights in the scene
    std::vector<Light*> lights;
    lights.push_back(new AmbientLight(0.2f));
    //lights.push_back(new PointLight(0.6f, Vec3(2.0, 1.0, 0.0)));
    lights.push_back(new DirectionalLight(0.4f, Vec3(1.0, 4.0, 4.0)));
    lights.push_back(new PointLight(0.6f, Vec3(-1.0, 0.25, -3.0)));   
    
    Scene scene(shapes, lights);

    // Setup camera:
    Camera camera(Vec3(0.8, 0.5, -5.0), 720, 720, 1.0, 1.0, 1.0);
    camera.get_pixels() = pixels; 

    // Render the scene!
    camera.render(scene);


    // Clean up
    while (!shapes.empty())
    {
        delete shapes.back();
        shapes.pop_back();
    }

    while(!lights.empty())
    {
        delete lights.back();
        lights.pop_back();
    }
}

     //// 3D Koch Snowflake scene
    //shapes.push_back(new Sphere((Vec3(0.0, -5005.0, 0.0)), 5000.0, Color(255, 0, 0), 1000.0, 0.5f));
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //  
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), 1, 2, shapes);
    //koch_snowflake3d(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), 1, 2, shapes);
    // 
    //std::vector<Light*> lights;
    //lights.push_back(new AmbientLight(0.2f));
    //lights.push_back(new PointLight(0.2f, Vec3(2.0, 1.0, 0.0)));
    //lights.push_back(new PointLight(0.6f, Vec3(-1.0, 0.25, -3.0)));


    //shapes.push_back(new Triangle(Vec3(-4.0, -0.5, 5.0), Vec3(0.0, 5.0, 5.0), Vec3(4.0, -0.5, 5.0), Color(0, 255, 255), 500.0, 0.9f));
    //	shapes.push_back(new Triangle(Vec3(-2.5, -1.0, 1.0), Vec3(0.0, 4.0, 4.0), Vec3(2.5, -1.0, 1.0), Color(0, 255, 255), 500.0, 0.1f));
    //    koch_snowflake3d(Vec3(-2.5, -1.0, 1.0), Vec3(0.0, 4.0, 4.0), Vec3(2.5, -1.0, 1.0), 0, 2, shapes);
 
    //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.866, 0.0), Vec3(0.5, -0.433, 0), Color(0, 255, 255), 100.0, 0.0f));
    //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), Color(0, 255, 255), 100.0, 0.0f));
    //  shapes.push_back(new Triangle(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.5, -0.433, 0.0), Color(0, 255, 255), 100.0, 0.0f));
    //  shapes.push_back(new Triangle(Vec3(0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), Color(0, 255, 255), 100.0, 0.0f));
    // koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, 0.816), 1, 2, shapes);
    // koch_snowflake3d(Vec3(0.0, 0.866, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(-0.5, -0.433, 0.0), 1, 2, shapes);
    // koch_snowflake3d(Vec3(-0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.5, -0.433, 0.0), 1, 2, shapes);
    // koch_snowflake3d(Vec3(0.5, -0.433, 0.0), Vec3(0.0, 0.289, -0.866), Vec3(0.0, 0.866, 0.0), 1, 2, shapes);


    //// 3D Koch Snowflake scene
    //shapes.push_back(new Sphere((Vec3(0.0, -5005.0, 0.0)), 5000.0, Color(255, 0, 0), 1000.0, 0.5f));
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //shapes.push_back(new Triangle(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Color(255, 255, 255), 300.0, 0.2f));  
    //  
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.866, 0.0), Vec3(0.5, 0.289, -0.816), 1, 2, shapes);
    //koch_snowflake3d(Vec3(1.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(0.5, 0.866, 0.0), 1, 2, shapes);
    //koch_snowflake3d(Vec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), 1, 2, shapes);
    // 
    //std::vector<Light*> lights;
    //lights.push_back(new AmbientLight(0.2f));
    //lights.push_back(new PointLight(0.2f, Vec3(2.0, 1.0, 0.0)));
    //lights.push_back(new PointLight(0.6f, Vec3(-1.0, 0.25, -3.0)));
      
    // Single triangle
    // shapes.push_bacVec3(0.0, 0.0, 0.0), Vec3(0.5, 0.289, -0.816), Vec3(1.0, 0.0, 0.0), Ck(new Triangle(Vec3(-1.0, 1.73205, 0.0), Vec3(-1.0, -1.73205, 0.0), Vec3(2.0, 0.0, 0.0), Color(0, 255, 255), 300.0, 0.2f));  
    // koch_snowflake3d( Vec3(-1.0, -1.73205, 0.0), Vec3(-1.0, 1.73205, 0.0), Vec3(2.0, 0.0, 0.0), 1, 3, shapes);
     
    //shapes.push_back(new Triangle(Vec3(-0.28867, -0.25, 1.0), Vec3(0.0, 0.25, 1.0), Vec3(0.28867, -0.25, 1.0), Color(0, 255, 255), 500.0, 0.0f)); 
