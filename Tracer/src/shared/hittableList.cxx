#include "hittableList.hpp"

bool HittableList::hit(const ray& r, double tMin, double tMax, HitRecord& rec) const {
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