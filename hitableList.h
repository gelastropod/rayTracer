#ifndef HITABLELIST_H
#define HITABLELIST_H

#include "hitable.h"

class HitableList: public Hitable {
public:
    std::vector<shared_ptr<Hitable>> objects;

    HitableList() {}

    void clear() { objects.clear(); }
    void add(shared_ptr<Hitable> object) { objects.push_back(object); }

    bool hit(const Ray& r, Interval rayT, HitRecord& record) const override {
        HitRecord crntRecord;
        bool hit = false;
        double closest = rayT.max;
        for (const auto& object : objects) {
            if (object->hit(r, Interval(rayT.min, closest), crntRecord)) {
                hit = true;
                closest = crntRecord.t;
                record = crntRecord;
            }
        }
        return hit;
    }
};

#endif