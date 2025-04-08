#ifndef RRT_STAR_H
#define RRT_STAR_H

#include "rrt.h"

class RRTStar : public RRT {
    public:
    using RRT::RRT;

    std::vector<Point> planning() override;

    protected:
    void rewire(Node* newNode, std::vector<Node*>& nearNodes);
};
#endif
