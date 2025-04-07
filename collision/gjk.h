#ifndef GJK_H
#define GJK_H

#include "geometry/geometry.h"
#include <vector>

bool gjk(const std::vector<Point>& shape1, const std::vector<Point>& shape2);

#endif