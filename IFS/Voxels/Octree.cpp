// Octree.cpp
// Provides implementation of a Sparse Voxel Octree (SVO) for efficient storage of voxel data
// Used by Voxel Raycaster to find voxel state and bounds for any particular point in 3d space

Node::Node() : bounds{0}, color(), filled(false)
{
    for(int i = 0; i < 8; ++i)
    {
        children[i] = nullptr;
    }
}

Node(const Bounds & bounds; const Color & color, const bool filled) : bounds(bounds), color(color), filled(filled)
{
    for(int i = 0; i < 8; ++i)
    {
        children[i] = nullptr;
    }
}
        
// Fetches pointer to the child at index in children
Node * & Node::get_child(const int index)
{
    if(index > 7 || index < 0) return nullptr;
    return children[index];
}

// Fetches pointer to child which contains point
Node * & Node::get_child(const Vec3 & point)
{
    // If outer bounds don't contain point, return nullptr (no possible match)
    if(!check_contains(point)) return nullptr;
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
// Order goes:  0 - FrontTopLeft
//              1 - FrontTopRight
//              2 - FrontBottomLeft
//              3 - FrontBottomRight
//              4 - BackTopLeft
//              5 - BackTopRight
//              6 - BackBottomLeft
//              7 - BackBottomRight
Bounds get_bounds_from_index(const int index)
{
    Vec3 center = (bounds.min + bounds.max) / 2;
    Bounds to_return;
    switch(index)
    {
        case 0: // FrontTopLeft
            to_return.min = center;
            to_return.max = bounds.max;
            break;
        case 1:
            to_return.min = Vec3(bounds.min.get(X), center.get(Y), center.get(Z));
            to_return.max = Vec3(center.get(X), bounds.max.get(Y), bounds.max.get(Z));
            break;
        case 2:
            to_return.min = Vec3(center.get(X), bounds.min.get(Y), center.get(Z));
            to_return.max = Vec3(bounds.max.get(X), center.get(Y), bounds.max.get(Z));
            break;
        case 3:
            to_return.min = Vec3(bounds.min.get(X), bounds.min.get(Y), center.get(Z));
            to_return.max = Vec3(center.get(X), center.get(Y), bonds.max.get(Z));
            break;
        case 4:
            to_return.min = Vec3(center.get(X), center.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(bounds.max.get(X), bounds.max.get(Y), center.get(Z));
            break;
        case 5:
            to_return.min = Vec3(bounds.min.get(x), center.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(center.get(X), bounds.max.get(Y), center.get(Z));
            break;
        case 6:
            to_return.min = Vec3(center.get(X), bounds.min.get(Y), bounds.min.get(Z));
            to_return.max = Vec3(bounds.max.get(X), center.get(Y), center.get(Z));
            break;
        case 7:
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

    if(point.get(Z) < center.get(Z)) octant |= 4;
    if(point.get(Y) >= center.get(Y)) octant |= 2;
    if(point.get(X) >= center.get(X)) octant |= 1;

    return octant;
}
