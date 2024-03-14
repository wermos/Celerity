#pragma once

#include "vec3.hpp"
#include "shared/hittableList.hpp"

struct AABB {
    vec3 min;
    vec3 max;
};

class BoundingVolume {
    public:
        BoundingVolume(const HittableList& list) {
            // TODO: Calculate the bounding volume of the whole list.
        }
    private:
    AABB aabb;
};

// code from the blog post
struct BVHNode {
    AABB nodeBounds;
    BVHNode* left, *right;
    bool isLeaf;
    vector<Tri*> primitives;
};