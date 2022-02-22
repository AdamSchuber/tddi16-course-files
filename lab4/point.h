#pragma once
#include <iostream>

/**
 * An immutable data type for points in the plane.
 */
class Point {
public:
    // No default constructor.
    Point() = delete;

    // Initialize with coordinates.
    Point(unsigned int x, unsigned int y) : x{x}, y{y} {}

    // Position
    unsigned int x, y;

    // Compute the slope to another point.
    //
    // If the points are the same, negative infinity is returned
    // If the line between the points is horizontal positive zero is returned
    // If the line between the points is vertical positive infinity is returned
    double slopeTo(const Point&) const;

    // Is this point lexicographically smaller than p?
    // Comparing x-ccordinates and breaking ties by y-coordinates
    bool operator <(const Point&) const;
    bool operator >(const Point&) const;

    // Output.
    friend std::ostream& operator<<(std::ostream&, const Point&);
};


/**
 * Sort points according to their slope relative to 'origin'.
 */
class PolarSorter {
public:
    PolarSorter(const Point &origin) : origin{origin} {}

    bool operator() (const Point& p1, const Point& p2) const {
        return origin.slopeTo(p1) < origin.slopeTo(p2);
    }

private:
    Point origin;
};
