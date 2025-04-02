#ifndef RRT_STAR_H
#define RRT_STAR_H

#include "rrt.h"

class RRTStar : public RRT {
    public:
    RRTStar(Point start, Point goal, Point minRange, Point maxRange,
            ftype stepSize, ftype goalSampleRate, ftype maxIter,
            std::vector<Circle> circles, ftype search_radius);
    

    std::vector<Point> planning() override;

    protected:
    void rewire(Node* newNode, std::vector<Node*>& nearNodes);
    std::vector<Node*> getNearNodes(Node* newNode);
    ftype search_radius;
};
#endif
