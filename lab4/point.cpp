#include <limits>
#include <math.h>
#include "point.h"

/**
 * Slope between this point and p
 *
 * If the points are the same, negative infinity is returned
 * If the line between the points is horizontal positive zero is returned
 * If the line between the points is vertical positive infinity is returned
 */
double Point::slopeTo(const Point &p) const {
    if (x == p.x && y == p.y)
        return  -std::numeric_limits<double>::infinity();
    else if (y == p.y) // horizontal line segment
        return 0.0;
    else if (x == p.x) // vertical line segment
        return  std::numeric_limits<double>::infinity();
    else
        return (static_cast<double>(p.y) - static_cast<double>(y)) /
            (static_cast<double>(p.x) - static_cast<double>(x));
}

/**
 * Is this point lexicographically smaller than p?
 * Comparing x-ccordinates and breaking ties by y-coordinates
 */
bool Point::operator<(const Point &other) const {
    if (x == other.x)
        return y < other.y;
    else
        return x < other.x;
}

bool Point::operator>(const Point &other) const {
    return other < *this;
}

std::ostream &operator<<(std::ostream &out, const Point& p) {
    return out << "(" << p.x << ", " << p.y << ")";
}
