#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <initializer_list>

enum INTERSECTION_TYPE {
    SAME,
    TOUCH,
    INTERSECT,
    NO_INTERSECT
};

class Vector;
class Point;
class Segment;
class Circle;
class Polygon;
class Triangle;
class Angle;

class Vector {
private:
    double x, y;
public:
    Vector(double x, double y): x(x), y(y) {}
    Vector(const Vector& p): x(p.x), y(p.y) {}
    Vector& operator=(const Vector& v) { x = v.x; y = v.y; return *this; }

    double length() { return std::sqrt(std::pow(x, 2) + std::pow(y, 2)); }
    Vector rotate90() { return Vector(y, -x); }
    Vector normalize() { double len = length(); return Vector(x / len, y / len); }

    Vector& operator+=(const Vector& v) { x += v.x; y += v.y; return *this; }
    Vector& operator*=(double value) { x *= value; y *= value; return *this; }
    Vector operator-() { return Vector(-x, -y); }
    Vector& operator-=(Vector& v) { *this += -v; return *this; }
    Vector& operator/=(double value) { *this *= (1. / value); return *this; }

    friend std::ofstream& operator<<(std::ofstream&, const Vector&);
    friend std::ostream& operator<<(std::ostream&, const Vector&);
    friend Vector operator*(double value, const Vector&);
    friend Vector operator*(const Vector&, double value);
    friend Vector operator+(const Vector&, const Vector&);
    friend Vector operator-(const Vector&, const Vector&);
    friend Point operator+(const Point&, const Vector&);
    friend Point operator-(const Point&, const Vector&);
    friend Point;
};

class Point {
private:
    double x, y;
    const double EPS = 0.000001;
public:
    Point(double x, double y): x(x), y(y) {}
    Point(const Point& p): x(p.x), y(p.y) {}
    Point& operator=(const Point& p) { x = p.x; y = p.y; return *this; }

    Point& operator+=(const Vector& v) { x += v.x; y += v.y; return *this; }
    Point& operator-=(const Vector& v) { x -= v.x; y -= v.y; return *this; }

    friend double distance(const Point&, const Point&);

    bool operator==(const Point& other) const { return distance(*this, other) < EPS; }

    friend std::ofstream& operator<<(std::ofstream&, const Point&);
    friend std::ofstream& operator<<(std::ofstream&, const Circle&);
    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend Point operator+(const Point&, const Vector&);
    friend Point operator-(const Point&, const Vector&);
    friend Vector operator-(const Point&, const Point&);
};

class Segment {
private:
    Point a, b;
public:
    Segment(const Point& a, const Point& b): a(a), b(b) {}
    Segment(double a, double b, double x, double y): a(a, b), b(x, y) {}
    Segment(const Segment& s): a(s.a), b(s.b) {}
    Segment& operator=(const Segment& s) { a = s.a; b = s.b; return *this; }

    Segment move(const Vector& v) { return Segment(a + v, b + v); }
    double length() { return distance(a, b); }

    friend std::ofstream& operator<<(std::ofstream&, const Segment&);
    friend std::ostream& operator<<(std::ostream&, const Segment&);
};

class Circle {
private:
    Point center;
    double radius;
public:
    Circle(const Point& p, double radius): center(p), radius(radius) {}
    Circle(double x, double y, double radius): center(x, y), radius(radius) {}
    Circle(const Circle& c): center(c.center), radius(c.radius) {}
    Circle& operator=(const Circle& c) { center = c.center; radius = c.radius; return *this; }

    Circle move(const Vector& v) { return Circle(center + v, radius); }

    friend INTERSECTION_TYPE intersects(const Circle& c1, const Circle& c2, std::vector<Point>& store);
    friend INTERSECTION_TYPE intersects(const Circle& c1, const Circle& c2);

    bool operator==(const Circle& other) const { return intersects(*this, other)== SAME; }

    friend std::ofstream& operator<<(std::ofstream&, const Circle&);
    friend std::ostream& operator<<(std::ostream&, const Circle&); 
};

class Polygon {
private:
    std::vector<Point> points;
public:
    Polygon(std::initializer_list<Point> l): points(l) {}
    Polygon(std::vector<Point> points): points(points) {}
    Polygon(const Polygon& p): points(p.points) {}
    Polygon& operator=(const Polygon& p) { points = p.points; return *this; }

    Polygon move(const Vector&);

    friend std::ofstream& operator<<(std::ofstream&, const Polygon&);
    friend std::ostream& operator<<(std::ostream&, const Polygon&);
};

class Triangle: public Polygon {
public:
    Triangle(Point a, Point b, Point c): Polygon({a, b, c}) {}
};

class Angle {
private:
    Point a, b, c;
public:
    Angle(Point a, Point b, Point c): a(a), b(b), c(c) {}
    Angle(const Angle& angle): a(angle.a), b(angle.b), c(angle.c) {}
    Angle& operator=(const Angle& angle) { a = angle.a; b = angle.b; c = angle.c; return *this; }

    Angle move(const Vector& v) { return Angle(a + v, b + v, c + v); }

    friend std::ofstream& operator<<(std::ofstream&, const Angle&);
    friend std::ostream& operator<<(std::ostream&, const Angle&);
};