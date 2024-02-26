#include "shared/hittableList.hpp"

bool HittableList::hit(const ray& r, Float tMin, Float tMax, HitRecord& rec) const {
    HitRecord tempRecord;
    bool hitAnything = false;
    auto closestSoFar = tMax;

    for (const auto& object : m_objects) {
        if (object->hit(r, tMin, closestSoFar, tempRecord)) {
            hitAnything = true;
            closestSoFar = tempRecord.t;
            rec = tempRecord;
        }
    }

    return hitAnything;
}
