#include "gjk.h"
#include <iostream>
#include <cmath>


// Support function for GJK
Point support(const std::vector<Point>& shape, const Point& direction) {
    // Initialize the farthest point
    ftype maxDot = -1e15;
    Point farthestPoint;
    for (const auto& point : shape) {
        // Compute the dot product between the point and the direction
        ftype d = dot(point, direction);
        // If the dot product is greater than the current max, update
        if (d > maxDot) {
            maxDot = d;
            farthestPoint = point;
        }
    }
    return farthestPoint;
}

// Handle the simplex and update the search direction
bool handleSimplex(std::vector<Point>& simplex, Point& direction) {
    // 2 Points
    if (simplex.size() == 2) {
        Point A = simplex[1];
        Point B = simplex[0];
        Point AB = B - A;
        Point AO = -A;
        // New direction
        direction = tripleProduct(AB, AO, AB);
        if (std::abs(dot(direction, direction)) < 1e-8) {
            // if the computed direction is nearly zero, choose a perpendicular direction
            direction = Point(-AB.y, AB.x);
        }
    } else if (simplex.size() == 3) {
        // 3 points, A alway the newest point
        Point A = simplex[2];
        Point B = simplex[1];
        Point C = simplex[0];
        Point AO = -A;
        Point AB = B - A;
        Point AC = C - A;
        // Perpendicular directions
        Point ABperp = tripleProduct(AC, AB, AB);
        Point ACperp = tripleProduct(AB, AC, AC);
        // Check if the origin is in the region of AB or AC
        if (dot(ABperp, AO) > 0) {
            simplex.erase(simplex.begin());
            direction = ABperp;
        }
        else if (dot(ACperp, AO) > 0) {
            simplex.erase(simplex.begin() + 1);
            direction = ACperp;
        } else {
            return true; 
        }
    }
    return false;
}

bool gjk(const std::vector<Point>& shape1, const std::vector<Point>& shape2) {
    // Initialize direction and simplex
    Point direction(1, 0);
    std::vector<Point> simplex;
    Point pointA = support(shape1, direction) - support(shape2, -direction);
    simplex.push_back(pointA);
    // Update direction
    direction = -pointA;

    for (int i = 0; i < 100; ++i) {
        // Get the new point
        Point newPoint = support(shape1, direction) - support(shape2, -direction);
        // If the new point is not past the origin in the given direction, there's no collision
        if (dot(newPoint, direction) < 0) {
            return false; 
        }
        // Add the new point to the simplex
        simplex.push_back(newPoint);
        // if collision is detected, return true
        if (handleSimplex(simplex, direction)) {
            return true;
        }
    }
    return false;
}
