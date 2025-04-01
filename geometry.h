#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>
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
    bool operator==(const Point& p) const;
};

Point operator*(ftype a, const Point& b);

ftype distance(const Point& a, const Point& b);
ftype dot(const Point& a, const Point& b);
ftype cross(const Point& a, const Point& b);

struct Circle {
    Point center;
    ftype radius;
    Circle() {}
    Circle(Point center, ftype radius): center(center), radius(radius) {}
};

bool isSegmentIntersectCircle(const Point& from, const Point& to, const Circle& circle);

#endif

