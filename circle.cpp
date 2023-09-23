#include "geometry.h"

INTERSECTION_TYPE intersects(const Circle& c1, const Circle& c2, std::vector<Point>& store) {
    double r1 = c1.radius;
    double r2 = c2.radius;
    double d = distance(c1.center, c2.center);

    if (d > r1 + r2) { return NO_INTERSECT; }
    if (std::fabs(r1 - r2) > d) { return NO_INTERSECT; }
    if (c1.center == c2.center) { return SAME; }

    double b = (std::pow(r2, 2) - std::pow(r1, 2) + std::pow(d, 2)) / (2 * d);
    double a = d - b;
    double h = std::sqrt(std::pow(r1, 2) - std::pow(a, 2));

    Point p0 = c1.center + (a / d) * (c2.center - c1.center);
    Vector v = h * (c2.center - c1.center).rotate90().normalize();
    Point p1 = p0 + v;
    Point p2 = p0 - v;
    if (p1 == p2) { store.push_back(p0 + v); return TOUCH; }
    store.push_back(p0 + v);
    store.push_back(p0 - v);
    return INTERSECT;
}

INTERSECTION_TYPE intersects(const Circle& c1, const Circle& c2) {
    double r1 = c1.radius;
    double r2 = c2.radius;
    double d = distance(c1.center, c2.center);

    if (d > r1 + r2) { return NO_INTERSECT; }
    if (std::fabs(r1 - r2) > d) { return NO_INTERSECT; }
    if (c1.center == c2.center) { return SAME; }

    double b = (std::pow(r2, 2) - std::pow(r1, 2) + std::pow(d, 2)) / (2 * d);
    double a = d - b;
    double h = std::sqrt(std::pow(r1, 2) - std::pow(a, 2));

    Point p0 = c1.center + (a / d) * (c2.center - c1.center);
    Vector v = h * (c2.center - c1.center).rotate90().normalize();
    Point p1 = p0 + v;
    Point p2 = p0 - v;
    if (p1 == p2) { return TOUCH; }
    return INTERSECT;
}

Polygon Polygon::move(const Vector& v) {
    Polygon copy(points);
    for (auto point : copy.points) {
        point += v;
    }
    return copy;
}

std::ofstream& operator<<(std::ofstream& file, const Circle& c) {
    file << "\n";
    for (double t = 0; t < 2 * M_PI; t += 0.001) {
        file << c.center.x + c.radius * std::sin(t) << " " << c.center.y + c.radius * std::cos(t) << "\n";
    }
    file << "\n";
    return file;
}

std::ostream& operator<<(std::ostream& out, const Circle& c) {
    out << "○(" << c.center << ", " << c.radius << ")";
    return out;
}

std::ofstream& operator<<(std::ofstream& file, const Polygon& p) {
    for (auto point : p.points) {
        file << point;
    }
    file << p.points[0];
    return file;
}

std::ostream& operator<<(std::ostream& out, const Polygon& p) {
    out << "△(";
    for (auto point : p.points) {
        out << point;
    } 
    out << ")";
    return out;
}

std::ofstream& operator<<(std::ofstream& file, const Angle& angle) {
    file << angle.a;
    file << angle.b;
    file << angle.c;
    return file;
}

std::ostream& operator<<(std::ostream& out, const Angle& angle) {
    out << "∠(" << angle.a << ", " << angle.b << ", " << angle.c << ")";
    return out;
}
