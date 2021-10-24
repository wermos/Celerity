#include "hittableList.hpp"

bool hittableList::hit(const ray& r, double t_min, double t_max, hitRecord& rec) const {
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = t_max;

    for (const auto& object : m_objects) {
        if (object->hit(r, t_min, closestSoFar, tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.m_t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
