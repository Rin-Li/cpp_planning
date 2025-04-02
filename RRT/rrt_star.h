#ifndef RRT_STAR_H
#define RRT_STAR_H

#include "rrt.h"

class RRTStar : public RRT {
    using RRT::RRT;

    std::vector<Point> planning() override;
};
#endif
