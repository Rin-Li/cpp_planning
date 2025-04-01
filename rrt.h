#ifndef RRT_H
#define RRT_H

#include "geometry.h"
#include <vector>

struct Node {
    Point pos;
    Node* parent;
    Node(ftype x, ftype y): pos(x, y), parent(nullptr) {}
    Node(Point pos): pos(pos), parent(nullptr) {}
};

class RRT {
public:
    RRT(Point start, Point goal, Point minRange, Point maxRange,
        ftype stepSize, ftype goalSampleRate, ftype maxIter, std::vector<Circle> circles);

    void setStart(Point start);
    void setGoal(Point goal);
    std::vector<Point> planning();

protected:
    virtual bool isCollisionFree(const Point& from, const Point& to);
    ftype randomCoordinate(ftype min, ftype max);
    Point getRandomPoint();
    Node* getNearestNode(const Point& point);
    Point stepFromTo(const Point& from, const Point& to, ftype stepSize);

    Point startPoint, goalPoint;
    Point minRange, maxRange;
    ftype stepSize;
    ftype goalSampleRate;
    ftype maxIter;

    Node* startNode;
    Node* goalNode;
    std::vector<Node*> nodes;
    std::vector<Circle> circles;
    
};

#endif
