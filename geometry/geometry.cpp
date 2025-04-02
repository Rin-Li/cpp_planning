#include "geometry.h"

Point& Point::operator+=(const Point& p){ x += p.x; y += p.y; return *this; }
Point& Point::operator-=(const Point& p){ x -= p.x; y -= p.y; return *this; }
Point& Point::operator*=(ftype t){ x *= t; y *= t; return *this; }
Point& Point::operator/=(ftype t){ x /= t; y /= t; return *this; }

Point Point::operator+(const Point& p) const { return Point(*this) += p; }
Point Point::operator-(const Point& p) const { return Point(*this) -= p; }
Point Point::operator*(ftype t) const { return Point(*this) *= t; }
Point Point::operator/(ftype t) const { return Point(*this) /= t; }

bool Point::operator==(const Point& p) const {
    return std::abs(x - p.x) < EPS && std::abs(y - p.y) < EPS;
}

Point operator*(ftype a, const Point& b) { return b * a; }

ftype distance(const Point& a, const Point& b){
    return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

ftype dot(const Point& a, const Point& b){
    return a.x * b.x + a.y * b.y;
}

ftype cross(const Point& a, const Point& b){
    return a.x * b.y - a.y * b.x;
}

bool isSegmentIntersectCircle(const Point& from, const Point& to, const Circle& circle){
    Point d = to - from;
    Point f = from - circle.center;
    ftype a = dot(d, d);
    ftype b = 2 * dot(f, d);
    ftype c = dot(f, f) - circle.radius * circle.radius;

    ftype discriminant = b*b - 4*a*c;
    if (discriminant < 0) return false;

    discriminant = std::sqrt(discriminant);
    ftype t1 = (-b - discriminant) / (2*a);
    ftype t2 = (-b + discriminant) / (2*a);
    return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}
