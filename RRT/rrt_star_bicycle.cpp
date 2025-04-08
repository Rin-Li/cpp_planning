#include "rrt_star_bicycle.h"
#include "collision/gjk.h"
#include <iostream>
#include <fstream> 


bool RRTStarSimpleCar::isCollisionFree(const Point& from, const Point& to) {
    // Calculate the yaw angle
    ftype dx = to.x - from.x;
    ftype dy = to.y - from.y;
    ftype yaw = atan2(dy, dx);
    Rectangle car;
    // Check the path from to to all collision free
    const int numChecks = 10;
    for (int idx = 0; idx < numChecks; ++idx){
        ftype t = static_cast<ftype>(idx) / (numChecks - 1);
        Point checkPoint = from + (to - from) * t;
        car = Rectangle(checkPoint, yaw, CAR_LENGTH, CAR_WIDTH);
        for (const auto& r : rectangles){
            if(gjk(car.getVertices(), r.getVertices())){
                return false;
            }
        }
    }

    return true;
}