#include "geometry.h"

Vector operator*(const Vector& v, double value) {
    Vector copy = v;
    copy *= value;
    return copy;
}

Vector operator*(double value, const Vector& v) {
    Vector copy = v;
    copy *= value;
    return copy;
}

Vector operator+(const Vector& a, const Vector& b) {
    return Vector(a.x + b.x, a.y + b.y);
}

Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a.x - b.x, a.y - b.y);
}

Point operator+(const Point& p, const Vector& v) {
    return Point(p.x + v.x, p.y + v.y);
}

Point operator-(const Point& p, const Vector& v) {
    return Point(p.x - v.x, p.y - v.y);
}

Vector operator-(const Point& a, const Point& b) {
    return Vector(a.x - b.x, a.y - b.y);
}

std::ofstream& operator<<(std::ofstream& file, const Point& p) {
    file << p.x << " " << p.y << "\n";
    return file;
}

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

double distance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}