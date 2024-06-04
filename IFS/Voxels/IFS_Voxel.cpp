// IFS_Voxel.cpp
// Main entry point into IFS voxel renderer

#include <random>
#include "IFS_Voxel.h"
#include "Camera.h"

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
    Bounds initial_bounds = {Vec3(-1.0, -1.0, -1.0), Vec3(1.0, 1.0, 1.0)};
    Octree * my_tree = new Octree(initial_bounds, 3);

    //my_tree->insert(Vec3(-1.0, -1.0, -1.0));
    ////my_tree->insert(Vec3(-0.8, -1.0, -1.0));
    //my_tree->insert(Vec3(-0.8, -1.0, -0.8));

    //my_tree->insert(Vec3(-0.1, -0.1, 1.0));

    //my_tree->insert(Vec3(1.0, 1.0, 1.0));


    // Generate and print a random float between -1 and 1
    for(int i = 0; i < 100; ++i)
    {
        my_tree->insert(Vec3(randomFloatBetweenMinus1And1(), randomFloatBetweenMinus1And1(), randomFloatBetweenMinus1And1()));
    }

    //Oct 0:
    //my_tree->insert(Vec3(-0.5, -0.5, 0.5));
    //my_tree->insert(Vec3(-0.5, -0.5, -0.5));
    //my_tree->insert(Vec3(-0.5, -0.5, -1.0));
    //my_tree->insert(Vec3(-0.5, -0.5, 0.0));
    
    //// Oct 3:
    //my_tree->insert(Vec3(-0.5, -0.5, 0.5));
    ////my_tree->insert(Vec3(0.0, 0.0, 0.5));
    
    ////// Oct 4:
    ////my_tree->insert(Vec3(0.5, 0.5, -0.5));  


    //// Oct 7:
    //my_tree->insert(Vec3(-0.5, -0.5, -0.5));

    //my_tree->test_display();

    // Oct 0:
    //my_tree->insert(Vec3(0.5, 0.5, 0.5));
    //my_tree->insert(Vec3(0.75, 0.75, 0.75));
    //my_tree->insert(Vec3(0.25, 0.25, 0.25));


    //// Oct 1:
   // my_tree->insert(Vec3(-0.5, 0.0, 0.5));

   // //// Oct 2:
   // my_tree->insert(Vec3(0.5, -0.5, 0.5));

   // my_tree->insert(Vec3(0.5, -0.5, -0.5));
   // //// Oct 3:
   // //my_tree->insert(Vec3(-0.5, -0.5, 0.5));

   // //// Oct 4:
   // //my_tree->insert(Vec3(0.5, 0.5, -0.5));  

   // //// Oct 5:
   // my_tree->insert(Vec3(-0.5, 0.5, -0.5));  
    
    //// Oct 6:
    //my_tree->insert(Vec3(0.5, -0.5, -0.5));  

    //// Oct 7:
    //my_tree->insert(Vec3(-0.5, -0.5, -0.5));
    
    //my_tree->test_display();

    Camera camera = Camera(Vec3(0.0, 0.0, -4.0), 720, 720, 1.0, 1.0, 1.0);
    camera.render(*my_tree);
    delete my_tree;
}