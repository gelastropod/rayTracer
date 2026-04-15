#ifndef INTERVAL_H
#define INTERVAL_H

#include <limits>

double INF = std::numeric_limits<double>::infinity();
double MAX = std::numeric_limits<double>::max();

class Interval {
public:
    double min, max;

    Interval() : min(INF), max(-INF) {}
    Interval(double _min, double _max) : min(_min), max(_max) {}

    inline bool contains(double x) const;
    inline bool surrounds(double x) const;
    inline double clamp(double x) const;

    static const Interval empty, reals;
};

inline bool Interval::contains(double x) const {
    return min <= x && x <= max;
}

inline bool Interval::surrounds(double x) const {
    return min < x && x < max;
}

inline double Interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

const Interval Interval::empty(INF, -INF);
const Interval Interval::reals(-INF, INF);

#endif