#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

class hittableList : public hittableObject {
    public:
        hittableList() = default;

        hittableList(std::shared_ptr<hittableObject> object) {
			add(object);
		}

        void clear() {
			m_objects.clear();
		}

        void add(std::shared_ptr<hittableObject> object) {
			m_objects.push_back(object);
		}

        bool hit(const ray& r, double t_min, double t_max, hitRecord& rec) const;

    public:
        std::vector<std::shared_ptr<hittableObject>> m_objects;
};

#endif // HITTABLE_LIST_HPP
