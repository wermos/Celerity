#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

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

        virtual bool hit(const ray& r, double t_min, double t_max, HitRecord& rec) const override;

    private:
        std::vector<std::shared_ptr<HittableObject>> m_objects;
};

#endif // HITTABLE_LIST_HPP
