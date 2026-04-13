#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "color.h"
#include "interval.h"
#include "ray.h"

using std::shared_ptr;
using std::make_shared;

double randDouble() {
    return (double)(rand()) / (RAND_MAX + 1.0);
}

#endif