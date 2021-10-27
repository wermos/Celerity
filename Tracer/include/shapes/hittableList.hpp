#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

//This goes inside the shapes directory because it defines a shape-related
//data structure.

class HittableList : public HittableObject {
    public:
        HittableList() = default;

        HittableList(std::shared_ptr<HittableObject> object) : m_objects({object})
		{}

        void clear() {
			m_objects.clear();
		}

        void add(std::shared_ptr<HittableObject> object) {
			m_objects.push_back(object);
		}

        virtual bool hit(const ray& r, double tMin, double tMax, HitRecord& rec) const override;

    private:
        std::vector<std::shared_ptr<HittableObject>> m_objects;
};

#endif // HITTABLE_LIST_HPP
