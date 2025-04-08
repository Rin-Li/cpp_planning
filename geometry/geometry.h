#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
#include <vector>
#define ftype double
const ftype EPS = 1e-6;

struct Point {
    ftype x, y;
    Point() {}
    Point(ftype x, ftype y): x(x), y(y) {}
    Point& operator+=(const Point& p);
    Point& operator-=(const Point& p);
    Point& operator*=(ftype t);
    Point& operator/=(ftype t);
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    Point operator*(ftype t) const;
    Point operator/(ftype t) const;
    Point operator-() const;
    bool operator==(const Point& p) const;
};

struct Rectangle {
    Point center;
    ftype yaw;
    ftype length;
    ftype width;
    Rectangle() {}
    Rectangle(Point center, ftype yaw, ftype length, ftype width): center(center), yaw(yaw), length(length), width(width) {}
    //Four corners of the car
    std::vector<Point> getVertices() const;

};

Point operator*(ftype a, const Point& b);

ftype distance(const Point& a, const Point& b);
ftype dot(const Point& a, const Point& b);
ftype cross(const Point& a, const Point& b);
Point tripleProduct(const Point& a, const Point& b, const Point& c);

struct Circle {
    Point center;
    ftype radius;
    Circle() {}
    Circle(Point center, ftype radius): center(center), radius(radius) {}
};

bool isSegmentIntersectCircle(const Point& from, const Point& to, const Circle& circle);

#endif

