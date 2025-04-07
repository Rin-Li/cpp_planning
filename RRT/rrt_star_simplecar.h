#ifndef RRT_STAR_SIMPLECAR_H
#define RRT_STAR_SIMPLECAR_H

#include "rrt.h"

class RRTStarSimpleCar : public RRT {
    public:
    RRTStarSimpleCar(Point start, Point goal, Point minRange, Point maxRange,
            ftype stepSize, ftype goalSampleRate, ftype maxIter,
            std::vector<Circle> circles, ftype search_radius);
    

    std::vector<Point> planning() override;

    protected:
    void rewire(Node* newNode, std::vector<Node*>& nearNodes);
    ftype search_radius;
};

#endif