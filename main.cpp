#include "RRT/rrt.h"
#include "RRT/rrt_star.h"
#include <iostream>
#include <vector>

int main() {

    Point start(0, 0);
    Point goal(90, 90);


    Point minRange(0, 0);
    Point maxRange(100, 100);


    std::vector<Circle> circles = {
        Circle(Point(50, 50), 10),
        Circle(Point(70, 70), 5)
    };


    RRTStar rrt(start, goal, minRange, maxRange,
            5.0,   // stepSize
            0.1,   // goalSampleRate
            1000,  // maxIter
            circles, 5.0);


    std::vector<Point> path = rrt.planning();


    if (path.empty()) {
        std::cout << "No path found!" << std::endl;
    } else {
        std::cout << "Path found! Path length: " << path.size() << std::endl;
        for (const auto& p : path) {
            std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
        }
    }

    return 0;
}
