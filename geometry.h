#ifndef TRIANGLE_UTILS_H
#define TRIANGLE_UTILS_H

#include <iostream>
#include <cmath>
#include <vector>

struct Coord {
    double xCoord, yCoord;
};

struct ShapeTriangle {
    Coord p1, p2, p3;
    double computeArea() const;
    bool isInside(const Coord &pt) const;
    bool isInsideByVector(const Coord &pt) const;
    bool isFlat() const;
};

double getDistance(const Coord &a, const Coord &b);
double calculateHeron(const ShapeTriangle &tri);
double crossProduct(const Coord &start, const Coord &end, const Coord &point);
bool isOnEdge(const Coord& pt, const Coord& start, const Coord& end);

#endif
