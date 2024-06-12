// Octree.h
// Provides definitions for my implementation of a Sparse Voxel Octree (SVO) for efficient storage of voxel data
// Used by Voxel Raycaster to find voxel state and bounds for any particular point in 3d space
#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include "VectorMath.h"
#include "SceneObjects.h"

// Bounds struct provides easy container access to some Node:
//      - min/max x
//      - min/max y
//      - min/max z
//      For indexing based on some point {x, y, z} into the Octree

struct Bounds {
    Vec3 min;
    Vec3 max;
};


// Face class for returning face vertices upon successful intersection
// If an intersection occurs in the Octree for some point at some face
// A node will calculate which face based on its bounds, and return the points which make up that face
// Order of points depends on which face is being intersected
//      (haven't figured out exact method yet, but because normals will always be pointint outwards, 
//       order of face vertices will matter)

struct Face {
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Vec3 d;
};

// Node class contains:
//      - bounds for the particular bounding box it represents
//      - voxel state (for first implementation, on/off, but could be extended to include color)
//      - child points to up to 8 other nodes, existing within a current node's bounds
//
//      For this implementation, any node instance with >= 1 child node CANNOT be set to an 'on' state
//      As that would imply the entire voxel should be considered 'filled' (and therefore disregard any child's state)
// 
// Rules box partitioning:
//      For children {a, b, c, d, e, f, g, h}:
//          - The children can be separated in half based on their position in relation to a camera with 
//          direction pointing down -z, with x going right->left and y going down->up (left-handed)
//          - {a, b, c, d} make up those box partitions with greater z:
//
//              a   b
//              c   d
//
//          - {e, f, g, h} make up those box partitions with lesser z:
//
//              e   f
//              g   h
//
//          - For every partition depth, each box has side lengths 1/2th of their parent box's side length
//            such that every box's volume is 1/8th of their parent box

class Node {

    public:
        Node(const Bounds & bounds);
        Node(const Bounds & bounds, const Color & color, const bool filled);
        
        // Fetches pointer to the child at index in children
        Node * &  get_child(const int index);

        // Fetches pointer to child which contains point
        Node * & get_child(const Vec3 & point);

        // Finds index of child adjacent to children[index] sharing point 
        int get_adjacent_index(const Vec3 & point, const int index);

        // Evaluates if some node's bounds contain point 
        bool check_contains(const Vec3 & point); 

        // Returns true or false indicating if some point lies on the outer bounds of a node
        bool check_on_bounds(const Vec3 & point);
        
        // Subdivides based on bounds, adding some child whose bounds contain point/
        // Returns pointer to new child
        Node * & add_child(const Vec3 & point);

        // Returns formatted vertices for face which some ray has intersected
        // This provides data for rendering some face to the canvas
        Face get_face_at_intersection(const Vec3 & point);

        // Returns bounds{min, max} of some octant based on the given index 0-7
        Bounds get_bounds_from_index(const int index);

        // Returns index 0-7 based on some point in bounds
        int get_index_from_point(const Vec3 & point);

        Vec3 get_intersection(Vec3 & origin, const Vec3 & direction, Bounds & bounds);
        Vec3 get_my_intersection(Vec3 & origin, const Vec3 & direction);
        Vec3 get_child_intersection(Vec3 & origin, const Vec3 & direction, const int index);

        //int which_face(Vec3 & point);
        Vec3 which_face(Vec3 & point);

        Color get_color();
        bool check_filled();
        void set_filled();

        bool check_split();
        void set_split();

        void test_display();
    private:
        Bounds bounds;
        Color color;
        bool filled;
        bool split;
        Node * children[8];
};


// Octree class
// Contains pointer to the root node, which represents the bounding box for the entire voxel scene held within
// All of root's children represent the 8 partitions which make up one box
// The rules for this Octree are:
//      - Upon insertion into the Octree based on some point {x, y, z}, the tree must be traversed to maximum depth before filling.
//      This way, no state must be tracked between insertions, such that some point would require moving further down if another point
//      is entered into the same box. Instead, we can always assume that, if some box is already filled, the new point can be discarded,
//      instead of subdividing further.
//      - The Octree's primary function is to allow quick indexing to find the status of some voxel at a particular point. Because of this,
//      indexing into the tree based on some point, such that we can quickly find the state of any particular voxel, must be supported.


class Octree {
    public:
        Octree();
        Octree(const Bounds initial_bounds, const Bounds floor_bounds, const int max_depth);
        Octree(const Bounds initial_bounds, const int max_depth);
        ~Octree();

        void insert(const Vec3 & point, Color color);
        Bounds retrieve(const Vec3 & point);

        Color intersect_ray(Vec3 & origin, const Vec3 & direction, const std::vector<Light *> & lights);


        void test_display();
    private:
        Node * root;
        Node * floor;

        int max_depth;

        void insert(Node *& root, const Vec3 & point, int depth, Color color);
        void remove_all(Node * & root);
        
        Vec3 intersect_ray(Vec3 & origin, const Vec3 & direction, Node * root, Color & color, Vec3 & normal);
        
        void test_display(Node * root, int depth);
    private:
};

#endif