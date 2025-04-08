#include "collision/gjk.h"
#include "geometry/geometry.h"
#include <iostream>

int main() {
 
    std::vector<Point> shape1 = {
        Point(0, 0),
        Point(2, 0),
        Point(2, 2),
        Point(0, 2)
    };

    std::vector<Point> shape2 = {
        Point(1, 1),  
        Point(3, 1),
        Point(3, 3),
        Point(1, 3)
    };

    std::vector<Point> shape3 = {
        Point(5, 5), 
        Point(7, 5),
        Point(7, 7),
        Point(5, 7)
    };

    std::cout << "Shape1 vs Shape2 (should collide): " 
              << (gjk(shape1, shape2) ? "Collision" : "No collision") << std::endl;

    std::cout << "Shape1 vs Shape3 (should NOT collide): " 
              << (gjk(shape1, shape3) ? "Collision" : "No collision") << std::endl;

    return 0;
}
