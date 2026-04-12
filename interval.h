#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

const double infinity = std::numeric_limits<double>::max();

class Interval {
public:
    double min, max;

    Interval() { min = +infinity, max = -infinity; }
    Interval(double _min, double _max) { min = _min, max = _max; }

    inline double size() const { return max - min; }
    inline bool contains(double x) const { return min <= x && x <= max; }
    inline bool surrounds(double x) const { return min < x && x < max; }

    static const Interval empty, universe;
};

const Interval Interval::empty    = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif