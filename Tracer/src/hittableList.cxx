#include "hittableList.hpp"

bool HittableList::hit(const ray& r, double tMin, double tMax, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object : m_objects) {
        if (object->hit(r, tMin, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
