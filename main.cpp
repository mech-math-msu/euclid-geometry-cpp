#include <iostream>
#include <fstream>

#include "geometry.h"

bool construct_triangle(double a_len, double b_len, double c_len) {
    std::ofstream file;

    Point a1(0, 0);
    Point a2(a_len, 0);
    Point b1(0, 2);
    Point b2(b_len, 2);
    Point c1(0, 4);
    Point c2(c_len, 4);

    Segment a(a1, a2);
    Segment b(b1, b2);
    Segment c(c1, c2);

    file.open("polygons.txt"); // только для красивого вывода
    Vector v(-10, 0); // только для красивого вывода
    file << a.move(v) << "\n"; // только для красивого вывода
    file << b.move(v) << "\n"; // только для красивого вывода
    file << c.move(v) << "\n"; // только для красивого вывода

    Circle circ1(a1, b_len);
    Circle circ2(a2, c_len);

    std::vector<Point> store;

    if (intersects(circ1, circ2, store) == INTERSECT) {
        Triangle t(a1, a2, store.back());

        file << t;
        file.close();

        file.open("circles.txt");
        file << circ1 << "\n";
        file << circ2 << "\n";

        
        return true;
    }
    return false;
}

// bool construct_equal_angle(const Angle& angle) {
//     std::cout << angle;

//     std::ofstream file;
//     file.open("polygons.txt");
//     file << angle;
    
//     return true;
// }

bool test_circles_intersection() {
    Point p1(0, 0);
    Point p2(8, 0);

    Circle c1(p1, 16);
    Circle c2(p2, 10);
    Circle c3(p2, 8);

    std::vector<Point> store;

    if (intersects(c1, c2, store) != INTERSECT) {
        return false;
    }

    if (intersects(c1, c1, store) != SAME) {
        return false;
    }

    if (intersects(c1, c3, store) != TOUCH) {
        return false;
    }
    return true;
}

int main() {

    std::cout << "\n=======================\n\n";
    std::cout << "testing circles...\n";
    
    if (test_circles_intersection()) {
        std::cout << "tests passed\n";
    }
    
    std::cout << "\n=======================\n\n";
    std::cout << "constructing triangle...\n";

    int a, b, c;
    std::ifstream sides;
    sides.open("side.txt");
    sides >> a >> b >> c;

    if (construct_triangle(a, b, c)) {
        std::cout << "constructed triangle\n";
        std::cout << "triangle and segments points written to polygons.txt file\n";
        std::cout << "circle points written to circles.txt file\n";
    } else {
        std::cout << "unable to construct\n";
    }

    return 0;
}