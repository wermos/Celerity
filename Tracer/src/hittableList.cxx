#include "hittableList.hpp"

bool hittableList::hit(const ray& r, double t_min, double t_max, hitRecord& rec) const {
    hitRecord tempRec;
    bool hitAnything = false;
    auto closestSoFar = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}
