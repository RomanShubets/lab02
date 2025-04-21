#include "geometry.h"

using std::fabs;

double getDistance(const Coord &a, const Coord &b) {
    return std::sqrt(std::pow(b.xCoord - a.xCoord, 2) + std::pow(b.yCoord - a.yCoord, 2));
}

double calculateHeron(const ShapeTriangle &tri) {
    double len1 = getDistance(tri.p1, tri.p2);
    double len2 = getDistance(tri.p2, tri.p3);
    double len3 = getDistance(tri.p3, tri.p1);
    double semiPerim = (len1 + len2 + len3) / 2;
    return std::sqrt(semiPerim * (semiPerim - len1) * (semiPerim - len2) * (semiPerim - len3));
}

double crossProduct(const Coord &start, const Coord &end, const Coord &point) {
    return (end.xCoord - start.xCoord) * (point.yCoord - start.yCoord) - (end.yCoord - start.yCoord) * (point.xCoord - start.xCoord);
}

bool ShapeTriangle::isInsideByVector(const Coord &pt) const {
    if (isFlat()) return false;

    double cp1 = crossProduct(p1, p2, pt);
    double cp2 = crossProduct(p2, p3, pt);
    double cp3 = crossProduct(p3, p1, pt);

    return (cp1 >= 0 && cp2 >= 0 && cp3 >= 0) || (cp1 <= 0 && cp2 <= 0 && cp3 <= 0);
}

bool ShapeTriangle::isInside(const Coord &pt) const {
    ShapeTriangle tA = {p1, p2, pt};
    ShapeTriangle tB = {p2, p3, pt};
    ShapeTriangle tC = {p3, p1, pt};

    double mainArea = computeArea();
    double areaSum = tA.computeArea() + tB.computeArea() + tC.computeArea();

    return std::fabs(mainArea - areaSum) < 1e-9;
}

double ShapeTriangle::computeArea() const {
    return calculateHeron(*this);
}

bool ShapeTriangle::isFlat() const {
    return std::fabs(crossProduct(p1, p2, p3)) < 1e-9;
}

bool isOnEdge(const Coord& pt, const Coord& start, const Coord& end) {
    if (std::fabs(crossProduct(start, end, pt)) > 1e-9) return false;

    double dot = (pt.xCoord - start.xCoord) * (end.xCoord - start.xCoord) + (pt.yCoord - start.yCoord) * (end.yCoord - start.yCoord);
    if (dot < 0) return false;

    double lenSq = std::pow(end.xCoord - start.xCoord, 2) + std::pow(end.yCoord - start.yCoord, 2);
    if (dot > lenSq) return false;

    return true;
}
