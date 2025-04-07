#include "gjk.h"

// Support function for GJK
Point support(const std::vector<Point>& shape, const Point& direction) {
    // Initialize the farthest point
    ftype maxDot = -1e15;
    Point farthestPoint;

    for (const auto& point : shape) {
        //Compute the dot product between the point and the direction
        ftype dotProduct = dot(point, direction);
        // If the dot product is greater than the current max, update
        if (dotProduct > maxDot) {
            maxDot = dotProduct;
            farthestPoint = point;
        }
    }

    return farthestPoint;
}

bool handleSimplex(std::vector<Point>& simplex, Point& direction){
    // Check the size of the simplex,
    // if it is 3, we need to check the orientation
    // if it is 2 return false
    if(simplex.size() == 2){
        Point A = simplex[1];
        Point B = simplex[0];
        Point AB = B - A;
        // New direction
        direction = Point(-AB.y, AB.x);
        // Perpendicular and also pointing to the origin
        if (dot(direction, Point(-A.x, -A.y)) < 0){
            direction = Point(direction.x, direction.y);
        }
    } else if (simplex.size() == 3) {
        Point A = simplex[2];
        Point B = simplex[1];
        Point C = simplex[0];

        Point AB = B - A;
        Point AC = C - A;
        Point AO = Point(-A.x, -A.y);

        Point ABperp = Point(-AB.y, AB.x);
        // Check if the perpendicular is pointing to the origin
        // If not, we need to reverse the direction
        if (dot(ABperp, AO) < 0){
            ABperp = Point(-ABperp.x, -ABperp.y);
        }

        Point ACperp = Point(AC.y, -AC.x);
        if (dot(ACperp, AO) < 0){
            ACperp = Point(-ACperp.x, -ACperp.y);
        }

        if (dot(ABperp, AO) > 0) {
            simplex = {B, A};
            direction = ABperp;
        } else if (dot(ACperp, AO) > 0) {
            simplex = {C, A};
            direction = ACperp;
        } else {
            return true; 
        }
    }
    return false;
}