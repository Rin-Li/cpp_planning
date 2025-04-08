#include "RRT/rrt_star_bicyle.h" 
#include <iostream>

int main() {
    Point start(0, 0);
    Point goal(90, 90);

    Point minRange(0, 0);
    Point maxRange(100, 100);

    // Obstacles
    std::vector<Rectangle> rectangles = {
        Rectangle(Point(30, 40), 0.0, 10.0, 4.0),
        Rectangle(Point(60, 60), 0.3, 8.0, 3.0),
        Rectangle(Point(80, 20), -0.2, 6.0, 6.0),
        Rectangle(Point(50, 80), 0.0, 12.0, 2.0)
    };

    
    RRTStarSimpleCar rrt(start, goal, minRange, maxRange,
                         5.0,    // stepSize
                         0.1,    // goalSampleRate
                         1000,   // maxIter
                         {},     
                         rectangles,
                         5.0);   // search radius


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
