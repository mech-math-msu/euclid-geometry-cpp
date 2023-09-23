#include "geometry.h"

std::ostream& operator<<(std::ostream& out, const Segment& s) {
    out << s.a << s.b;
    return out;
}

std::ofstream& operator<<(std::ofstream& file, const Segment& s) {
    file << s.a << s.b;
    return file;
}