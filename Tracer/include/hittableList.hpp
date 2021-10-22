#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

class hittableList requires HittableObject {
    public:
        hittableList() = default;

        hittableList(std::shared_ptr<hittable> object) {
			add(object);
		}

        void clear() {
			objects.clear();
		}

        void add(std::shared_ptr<hittable> object) {
			m_objects.push_back(object);
		}

        bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

    public:
        std::vector<std::shared_ptr<hittable>> m_objects;
};

#endif // HITTABLE_LIST_HPP
