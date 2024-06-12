// Octree.cpp
// Provides implementation of a Sparse Voxel Octree (SVO) for efficient storage of voxel data
// Used by Voxel Raycaster to find voxel state and bounds for any particular point in 3d space

#include <algorithm>
#include <cmath>
#include <vector>

#include "iostream"
#include "Octree.h"

using std::cout, std::min, std::max;

#define MISS 0.0f
#define HIT 1.0f
#define HIT_FILLED 2.0f

#define MISS_VECTOR Vec3(INFINITY, -INFINITY, 0.0)
#define BACKGROUND Color(0, 0, 0)

#define BABY_BLUE Color(179, 205, 224)
#define ROSY_PINK Color(244, 194, 194)
#define BLUE Color(0, 0, 230)
#define WHITE Color(230, 230, 230)

#define EPSILON 0.0001

enum FACE {BACK, FRONT, TOP, BOTTOM, RIGHT, LEFT};

Node::Node(const Bounds & bounds) : bounds(bounds), color(), filled(false), split(false)
{
    for(int i = 0; i < 8; ++i)
    {
        children[i] = nullptr;
    }
}

Node::Node(const Bounds & bounds, const Color & color, const bool filled) : bounds(bounds), color(color), filled(filled), split(false)
{
    for(int i = 0; i < 8; ++i)
    {
        children[i] = nullptr;
    }
}
        
// Fetches pointer to the child at index in children
Node * & Node::get_child(const int index)
{
    if(index > 7 || index < 0) throw nullptr;
    return children[index];
}

// Fetches pointer to child which contains point
Node * & Node::get_child(const Vec3 & point)
{
    // If outer bounds don't contain point, return nullptr (no possible match)
    if(!check_contains(point)) throw nullptr;
    return children[get_index_from_point(point)];
}
    
// Evaluates if some node's bounds contain point 
bool Node::check_contains(const Vec3 & point)
{
    if(point.get(X) > bounds.max.get(X) || point.get(X) < bounds.min.get(X) 
    || point.get(Y) > bounds.max.get(Y) || point.get(Y) < bounds.min.get(Y)
    || point.get(Z) > bounds.max.get(Z) || point.get(Z) < bounds.min.get(Z)) return false;
    return true;
}

// Returns true or false indicating if some point lies on the outer bounds of a node
bool Node::check_on_bounds(const Vec3 & point)
{
    if((point.get(X) < bounds.max.get(X) + 0.0001 && point.get(X) > bounds.max.get(X) - 0.0001)
    || (point.get(X) < bounds.min.get(X) + 0.0001 && point.get(X) > bounds.min.get(X) - 0.0001)
    || (point.get(Y) < bounds.max.get(Y) + 0.0001 && point.get(Y) > bounds.max.get(Y) - 0.0001)
    || (point.get(Y) < bounds.min.get(Y) + 0.0001 && point.get(Y) > bounds.min.get(Y) - 0.0001)
    || (point.get(Z) < bounds.max.get(Z) + 0.0001 && point.get(Z) > bounds.max.get(Z) - 0.0001)
    || (point.get(Z) < bounds.min.get(Z) + 0.0001 && point.get(Z) > bounds.min.get(Z) - 0.0001)) return true;
    return false;
}

//// Subdivides based on bounds, adding some child whose bounds contain point/
//// Returns pointer to new child
//Node * & Node::add_child(const Vec3 & point)
//{
//
//}
//
//// Returns formatted vertices for face which some ray has intersected
//// This provides data for rendering some face to the canvas
//Face get_face_at_intersection(const Vec3 & point);

bool Node::check_filled()
{
    return filled;
}

void Node::set_filled()
{
    if(!filled) filled = true;
}


// Finds the bounds for some octant at children[index]
Bounds Node::get_bounds_from_index(const int index)
{
    Vec3 center = (bounds.min + bounds.max) / 2;
    Bounds to_return;
    switch(index)
    {
        case 0: // BackTopRight
            to_return.min = center;
            to_return.max = bounds.max;
            break;
        case 1: // BackTopLeft
            to_return.min = Vec3(bounds.min.get(X), center.get(Y), center.get(Z));
            to_return.max = Vec3(center.get(X), bounds.max.get(Y), bounds.max.get(Z));
            break;
        case 2: //BackBottomRight
            to_return.min = Vec3(center.get(X), bounds.min.get(Y), center.get(Z));
            to_return.max = Vec3(bounds.max.get(X), center.get(Y), bounds.max.get(Z));
            break;
        case 3: //BackBottomLeft
            to_return.min = Vec3(bounds.min.get(X), bounds.min.get(Y), center.get(Z));
            to_return.max = Vec3(center.get(X), center.get(Y), bounds.max.get(Z));
            break;
        case 4: // FronTopRight
            to_return.min = Vec3(center.get(X), center.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(bounds.max.get(X), bounds.max.get(Y), center.get(Z));
            break;
        case 5: //FrontTopLeft
            to_return.min = Vec3(bounds.min.get(X), center.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(center.get(X), bounds.max.get(Y), center.get(Z));
            break;
        case 6: //FrontBottomRight
            to_return.min = Vec3(center.get(X), bounds.min.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(bounds.max.get(X), center.get(Y), center.get(Z));
            break;
        case 7: //FrontBottomLeft
            to_return.min = bounds.min;
            to_return.max = center;
            break;
        default:
            break;
    }
    return to_return;
}

// Get index of the child whose bounds containt point
// Assumes point has already been determined to lie within bounds of the parent
int Node::get_index_from_point(const Vec3 & point)
{
    Vec3 center = (bounds.min + bounds.max) / 2;
    int octant = 0;

    if(point.get(Z) <= center.get(Z)) octant |= 4;
    if(point.get(Y) <= center.get(Y)) octant |= 2;
    if(point.get(X) <= center.get(X)) octant |= 1;

    return octant;
}


// Finds index of child adjacent to children[index] sharing point 
int Node::get_adjacent_index(const Vec3 & point, const int index)
{
    Vec3 center = (bounds.min + bounds.max) / 2;
    int new_index = index;
    // If ray_max lies lies on the boundary between two children on the x axis, flip x bit
    if(point.get(X) > center.get(X) - 0.0001 && point.get(X) < center.get(X) + 0.0001) new_index ^= 1;

    // If ray_max lies lies on the boundary between two children on the y axis, flip y bit
    if(point.get(Y) > center.get(Y) - 0.0001 && point.get(Y) < center.get(Y) + 0.0001) new_index ^= 2;

    // If ray_max lies lies on the boundary between two children on the z axis, flip z bit
    if(point.get(Z) > center.get(Z) - 0.0001 && point.get(Z) < center.get(Z) + 0.0001) new_index ^= 4;
    return new_index;

}

void Node::test_display()
{
    cout << "Bounds: " << "{" << bounds.min.get(X) << ", " << bounds.min.get(Y) << ", " << bounds.min.get(Z) << "} ";
    cout << "{" << bounds.max.get(X) << ", " << bounds.max.get(Y) << ", " << bounds.max.get(Z) << "}, ";
    cout << "Filled: " << filled << ", Split: " << split << '\n';
    return;
}


bool Node::check_split()
{
    return split;
}

void Node::set_split()
{
    split = true;
}

Color Node::get_color()
{
    return color;
}

// Rendering code!


// Given some bounds, find tmin, tmax for the ray origin + (direction * t) with those bounds
// Z coordinate of returned Vec3 is 0.0 for miss, 1.0 for hit
Vec3 Node::get_intersection(Vec3 & origin, const Vec3 & direction, Bounds & bounds)
{
    //// Calculate the inverse of the ray direction components
    //Vec3 dirfrac = Vec3(1.0 / direction.get(X), 1.0 / direction.get(Y), 1.0 / direction.get(Z));

    ////Vec3 dirfrac = Vec3((direction.get(X) == 0.0 ? INFINITY : 1.0 / direction.get(X)),
    //                    (direction.get(Y) == 0.0 ? INFINITY : 1.0 / direction.get(Y)),
    //                    (direction.get(Z) == 0.0 ? INFINITY : 1.0 / direction.get(Z)));


    //// Compute intersection distances for each axis
    //Vec3 t1_v = Vec3((bounds.min.get(X) - origin.get(X)) * dirfrac.get(X),
    //                 (bounds.min.get(Y) - origin.get(Y)) * dirfrac.get(Y), 
    //                 (bounds.min.get(Z) - origin.get(Z)) * dirfrac.get(Z));
    //Vec3 t2_v = Vec3((bounds.max.get(X) - origin.get(X)) * dirfrac.get(X),
    //                 (bounds.max.get(Y) - origin.get(Y)) * dirfrac.get(Y), 
    //                 (bounds.max.get(Z) - origin.get(Z)) * dirfrac.get(Z));
   
    //// Find the smallest and largest t values for the ray to intersect the bounding box
    //float tmin = max(max(min(t1_v.get(X), t2_v.get(X)), min(t1_v.get(Y), t2_v.get(Y))), min(t1_v.get(Z), t2_v.get(Z)));
    //float tmax = min(min(max(t1_v.get(X), t2_v.get(X)), max(t1_v.get(Y), t2_v.get(Y))), max(t1_v.get(Z), t2_v.get(Z)));


    float tmin = -std::numeric_limits<float>::infinity();
    float tmax = std::numeric_limits<float>::infinity();

    for (int i = 0; i < 3; ++i) 
    {
        if (direction.get(i) != 0.0) 
        {
            float invD = 1.0 / direction.get(i);
            float t1 = (bounds.min.get(i) - origin.get(i)) * invD;
            float t2 = (bounds.max.get(i) - origin.get(i)) * invD;
            if (invD < 0.0) std::swap(t1, t2);
            tmin = std::max(tmin, t1);
            tmax = std::min(tmax, t2);
        } 
        else 
        {
            // Ray is parallel to the slab. No hit if origin is not within the slab
            if (origin.get(i) < bounds.min.get(i) || origin.get(i) > bounds.max.get(i)) 
            {
                return MISS_VECTOR;
            }
        }
    }

    // If tmax < 0, the intersection is behind the ray's origin
    // If tmin > tmax, the ray misses the bounding box
    if(tmax < 0 || tmin > tmax)
{
        return MISS_VECTOR;
    }
    else 
    {
        if(filled) return Vec3(tmin, tmax, HIT_FILLED);
        return Vec3(tmin, tmax, HIT);
    }
}

Vec3 Node::get_my_intersection(Vec3 & origin, const Vec3 & direction)
{
    return get_intersection(origin, direction, bounds);
}

Vec3 Node::get_child_intersection(Vec3 & origin, const Vec3 & direction, const int index)
{
    Bounds child_bounds = get_bounds_from_index(index);
    return get_intersection(origin, direction, child_bounds);
}

Vec3 Node::which_face(Vec3 & point)
{
    // Known issue - cases where some point lies on the corner of face bounds - which vector to choose?
    // For now, I prioritize top-bottom, back-front, and right-left in that order
    // Theres definitely a better way to get normal values
    int count = 0;
    int face = -1;
    if(point.get(Y) < bounds.max.get(Y) + 0.0001 && point.get(Y) > bounds.max.get(Y) - 0.0001) 
    {
        return Vec3(0.0, 1.0, 0.0);
        //return FACE::TOP;
        //++count;
        //face = FACE::TOP;
    }
    if(point.get(Y) < bounds.min.get(Y) + 0.0001 && point.get(Y) > bounds.min.get(Y) - 0.0001)
    {
        return Vec3(0.0, -1.0, 0.0);
        //return FACE::BOTTOM;
        //++count;
        //face = FACE::BOTTOM;
    }
    if(point.get(Z) < bounds.max.get(Z) + 0.0001 && point.get(Z) > bounds.max.get(Z) - 0.0001)
    {
        return Vec3(0.0, 0.0, 1.0);
        //return FACE::BACK;
        //++count;
        //face = FACE::BACK;
    }
    if(point.get(Z) < bounds.min.get(Z) + 0.0001 && point.get(Z) > bounds.min.get(Z) - 0.0001) 
    {
        return Vec3(0.0, 0.0, -1.0);
        //return FACE::FRONT;
        //++count;
        //face = FACE::FRONT;
    }
    if(point.get(X) < bounds.max.get(X) + 0.0001 && point.get(X) > bounds.max.get(X) - 0.0001) 
    {
        return Vec3(1.0, 0.0, 0.0);
        //return FACE::RIGHT;
        //++count;
        //face = FACE::RIGHT;
    }
    if(point.get(X) < bounds.min.get(X) + 0.0001 && point.get(X) > bounds.min.get(X) - 0.0001)
    {
        return Vec3(-1.0, 0.0, 0.0);
        //return FACE::LEFT;
        //++count;
        //face = FACE::LEFT;
    }

    //if(count != 1)
    //{
    //    return -1;
    //}

    return Vec3(0.0, 1.0, 0.0);
}






Octree::Octree() : root(nullptr), max_depth(0) {}

Octree::Octree(const Bounds initial_bounds, const Bounds floor_bounds, const int max_depth) : max_depth(max_depth) 
{
    root = new Node(initial_bounds, Color(0, 255, 0), false);
    floor = new Node(floor_bounds, Color(139, 90, 43), true);
}

Octree::Octree(const Bounds initial_bounds, const int max_depth) : root(nullptr), floor(nullptr), max_depth(max_depth) 
{
    root = new Node(initial_bounds, Color(0, 255, 0), false);
}


void Octree::insert(const Vec3 & point, Color color)
{
    // Empty tree case
    if(!root) return;

    // Point outside case
    if(!root->check_contains(point)) return;

    insert(root, point, 0, color);
}

void Octree::insert(Node * & root, const Vec3 & point, int depth, Color color)
{
    if(depth > max_depth) return;
    int index = root->get_index_from_point(point);
    Node *& temp = root->get_child(index);

    // Case: returns pointer to nonexistant child
    if(!temp)
    {
        root->set_split();

        // If we've reached max depth, make a new filled child!
        if(depth == max_depth)
        {
            temp = new Node(root->get_bounds_from_index(index), color, true);
            return;
        }
        else // Else make a new child 
        {
            temp = new Node(root->get_bounds_from_index(index));
        }
    }
    else // Case: returns pointer to existant child
    {
        // Found a filled square where the point belongs - no work to be done!
        if(depth == max_depth) return;
    }
    insert(temp, point, ++depth, color);
    return;
}



void Octree::test_display()
{
    if(!root) return;
    test_display(root, 0);
}

void Octree::test_display(Node * root, int depth)
{
    if(!root) return;
    cout << depth << ": ";
    if(root) root->test_display();
    cout << '\n';
    for(int i = 0; i < 8; ++i)
    {
        cout << "Index: " << i << '\n';
        test_display(root->get_child(i), depth + 1);
    }
    cout << '\n';
    return;
}


//Color Octree::intersect_ray(Vec3 & origin, Vec3 & direction)
//{
//    if(!root) return Color(0, 0, 0);
//
//    float t = root->get_intersection(origin, direction);
//    if(t < 0.0) return Color(0, 0, 0);
//
//    Vec3 intersection = origin + (direction * t);
//
//    int face = root->which_face(intersection);
//    switch(face)
//    {
//        case 0: // Left
//            return Color(0, 255, 0);
//        case 1: // Right
//            return Color(0, 125, 0);
//        case 2: // Top
//            return Color(255, 0, 0);
//        case 3: // Bottom
//            return Color(125, 0, 0);
//        case 4: // Front
//            return Color(0, 0, 255);
//        case 5: // Back
//            return Color(0, 0, 125);
//        default:
//            return Color(0, 0, 0);
//    }
//    return Color(0, 0, 0);
//    // p is point of intersection
//    //Vec3 p = origin + (t * direction);
//
//}


//Color Octree::intersect_ray(Vec3 & origin, Vec3 & direction)
//{
//    if(!root) return Color(0, 0, 0);
//    std::vector<Node *> stack;
//
//    float tmin, tmax;
//    int index;
//
//    
//
//}




// Public wrapper for tree intersection traversal
//Color Octree::intersect_ray(Vec3 & origin, Vec3 & direction)
//{
//    // Return background color!
//    if(!root) return Color(0, 0, 0);
//
//    // Initial intersection for outermost bounding box
//    float t = root->get_intersection(origin, direction);
//    if(t < 0.0) return Color(0, 0, 0);
//
//    Vec3 intersection = origin + (direction * t);
//    Color to_fill = Color();
//
//    Vec3 T = intersect_ray(intersection, direction, root, to_fill);
//    if(T.get(Z) == 1) // Hit some filled!
//    {
//        return to_fill;
//    }
//    else // Ray exited without intersection
//    {
//        // Return background color
//        return Color(0, 0, 0); 
//    }
//}

Color lerp(const Color & from, const Color & to, const float t);

Color Octree::intersect_ray(Vec3 & origin, const Vec3 & direction, const std::vector<Light *> & lights)
{
    // If tree is empty, return background color
    if(!root) return BACKGROUND;

    // Initial intersection for outermost bounding box
    Vec3 t = root->get_my_intersection(origin, direction);

    // If ray misses entirely, return background color
    if(t.get(Z) == MISS) 
    {
        return BACKGROUND;
        //return lerp(Color(245, 245, 220), Color(163, 213, 255), 0.5 + direction.get(Y));
    }

    Color to_fill;
    Vec3 intersection;
    Vec3 hits;
    Vec3 normal;

    // If tmin is negative, the ray origin is within root's bounds!
    if(t.get(X) < 0.0)
    {
        intersection = origin;
        hits = intersect_ray(intersection, direction, root, to_fill, normal);
    }
    else // If not, ray origin hits root, but is outside it
    {
        intersection = origin + (direction * t.get(X));
        hits = intersect_ray(intersection, direction, root, to_fill, normal);
    }

    if(hits.get(Z) != HIT_FILLED && floor)
    {
        hits = floor->get_my_intersection(intersection, direction);
        if(hits.get(Z) == HIT_FILLED)
        {
            Vec3 floor_landing = intersection + (direction * (hits.get(X) - 0.00001));
            to_fill = floor->get_color();
            normal = floor->which_face(floor_landing);
        }
    }

    if(hits.get(Z) == HIT_FILLED)
    {
        // Once a hit is found, calculate lighting from the hit
        Vec3 light_origin = intersection + (direction * (hits.get(X) - 0.00001)); 
        Vec3 light_direction;
        Vec3 empty_normal = Vec3();
        Color empty_color = Color();

        float intensity = 0.0;
        for(auto light : lights)
        {
            AmbientLight * a = dynamic_cast<AmbientLight *>(light);
            if(!a)
            {
                light_direction = light->get_direction(light_origin);
                intersection = light_origin;

                hits = intersect_ray(intersection, light_direction, root, empty_color, empty_normal);

                // If there isn't a filled voxel in the way
                if(hits.get(Z) != HIT_FILLED)
                {
                    intensity += light->compute_lighting(light_origin, normal, -direction, 1000.0);
                }
            }
            else intensity += light->compute_lighting(light_origin, normal, -direction, 20.0);
        }
        return to_fill * intensity;
        //return to_fill;
    }
    else
    {
        // White-Blue gradient
        //return lerp(Color(245, 245, 220), Color(163, 213, 255), 0.5 + direction.get(Y));
        return BACKGROUND;
    }
}


// Private recursive for tree intersection traversal
// Must return t values for some node based on origin, direction of ray
// Based on t values, previous function on the stack can determine which of its next children to traverse to
Vec3 Octree::intersect_ray(Vec3 & origin, const Vec3 & direction, Node * root, Color & to_fill, Vec3 & normal)
{
    if(!root) return MISS_VECTOR;
    if(root->check_filled())
    {
        //std::cout << "Found filled\n";
        to_fill = root->get_color();
        Vec3 ct = root->get_my_intersection(origin, direction);
        Vec3 entry = origin + (direction * ct.get(X));
        normal = root->which_face(entry);
        //switch(face)
        //{
        //    case FACE::BACK: 
        //        normal = Vec3(0.0, 0.0, 1.0);
        //        break;
        //    case FACE::FRONT:
        //        normal = Vec3(0.0, 0.0, -1.0);
        //        break;
        //    case FACE::TOP:
        //        normal = Vec3(0.0, 1.0, 0.0);
        //        break;
        //    case FACE::BOTTOM:
        //        normal = Vec3(0.0, -1.0, 0.0);
        //        break;
        //    case FACE::RIGHT:
        //        normal = Vec3(1.0, 0.0, 0.0);
        //        break;
        //    case FACE::LEFT:
        //        normal = Vec3(-1.0, 0.0, 0.0);
        //        break;
        //    default:
        //        normal = Vec3(0.0, 1.0, 0.0);
        //        break;
        //    //default:
        //    //    //std::cout << "Got here!\n";
        //    //    //normal = -direction;
        //    //    //normal.normalize();
        //    //    break;
        //}
        //return Vec3(0.0, 0.0, HIT_FILLED);
        return ct;
    }
    else
    {
        int index = root->get_index_from_point(origin);
        bool in_bounds = true;
        Vec3 t;
        while(in_bounds)
        {
            if(!root->get_child(index))
            {
                t = root->get_child_intersection(origin, direction, index);
                if(t.get(Z) == 1.0)
                {
                    origin = origin + (direction * (t.get(Y) + EPSILON));
                    index = root->get_index_from_point(origin);
                }
            }
            else
            {
                // If root is split

                // PUSH down to next node
                t = intersect_ray(origin, direction, root->get_child(index), to_fill, normal);

                // Case 1: found a filled hit 
                if(t.get(Z) == HIT_FILLED)
                {
                    return t;
                }

                // Case 2: found a hit, but no fill
                if(t.get(Z) == HIT)
                {
                    // ADVANCE
                    //origin = origin + (direction * (t.get(Y) + EPSILON));
                    //if(index == root->get_index_from_point(origin))
                    //{

                    //}
                    index = root->get_index_from_point(origin);
                }
                
                // Case 3: for some reason, ray did not intersect
                if(t.get(Z) == MISS)
                {
                    //std::cout << "Got here!\n";
                    //in_bounds = false;
                    index = root->get_index_from_point(origin);
                }
            }

            t = root->get_my_intersection(origin, direction);
            if(t.get(Z) == MISS)
            {
                in_bounds = false;
            }
        }
        return t;
    }
}


Octree::~Octree()
{
    if(floor) delete floor;
    if(!root) return;
    remove_all(root);
}

void Octree::remove_all(Node * & root)
{
    if(!root) return;
    for(int i = 0; i < 8; ++i)
    {
        remove_all(root->get_child(i));
    }
    delete root;
    root = nullptr;
    return;
}