#ifndef RRT_STAR_BICYLE_H
#define RRT_STAR_BICYLE_H

#include "rrt_star.h"

class RRTStarSimpleCar : public RRTStar {
    public:
    using RRTStar::RRTStar;

    

    protected:
    bool isCollisionFree(const Point& from, const Point& to) override;
    ftype CAR_LENGTH = 4.0; // Length of the car
    ftype CAR_WIDTH = 2.0; // Width of the car
};

#endif