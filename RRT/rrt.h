#ifndef RRT_H
#define RRT_H

#include "geometry/geometry.h"
#include <vector>

struct Node {
    Point pos;
    Node* parent;
    ftype cost;
    Node(ftype x, ftype y): pos(x, y), parent(nullptr), cost(0) {}
    Node(Point pos): pos(pos), parent(nullptr), cost(0) {}
};

class RRT {
public:
    RRT(Point start, Point goal, Point minRange, Point maxRange,
        ftype stepSize, ftype goalSampleRate, ftype maxIter, 
        std::vector<Circle> circles, ftype search_radius=0.0);

    void setStart(Point start);
    void setGoal(Point goal);
    virtual std::vector<Point> planning();

protected:
    virtual bool isCollisionFree(const Point& from, const Point& to);
    ftype randomCoordinate(ftype min, ftype max);
    Point getRandomPoint();
    Node* getNearestNode(const Point& point);
    Point stepFromTo(const Point& from, const Point& to, ftype stepSize);
    std::vector<Node*> getNearNodes(Node* newNode);

    Point startPoint, goalPoint;
    Point minRange, maxRange;
    ftype stepSize;
    ftype goalSampleRate;
    ftype maxIter;
    ftype search_radius;

    Node* startNode;
    Node* goalNode;
    std::vector<Node*> nodes;
    std::vector<Circle> circles;
    
};

#endif
