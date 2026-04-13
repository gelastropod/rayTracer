#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include "hittable.h"

class HittableList: public Hittable {
private:
    std::vector<shared_ptr<Hittable>> objects;

public:
    HittableList() {}

    // Modify list of objects
    inline void add(shared_ptr<Hittable> hittable);
    inline void pop();
    inline shared_ptr<Hittable> operator[](size_t idx) const;

    bool hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const override;
};

inline void HittableList::add(shared_ptr<Hittable> hittable) {
    objects.push_back(hittable);
}

inline void HittableList::pop() {
    objects.pop_back();
}

inline shared_ptr<Hittable> HittableList::operator[](size_t idx) const {
    return objects[idx];
}

// Iterate through list of objects and check if ray hits any of them
bool HittableList::hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const {
    bool hitSomething = false;
    double currentMax = tInterval.max;
    HittableRecord currentRecord;

    for (const auto& object : objects) {
        if (object->hit(ray, Interval(tInterval.min, currentMax), currentRecord)) {
            currentMax = currentRecord.t;
            hitSomething = true;
            record = currentRecord;
        }
    }

    return hitSomething;
}

#endif