
#include "geometry/Triangle.h"

#include "geometry/Polygon.h"
#include "geometry/Vector2.h"

#include <stdexcept>
#include <vector>

Triangle::Triangle(Point a, Point b, Point c): Polygon({a, b, c}) {}

Triangle::Triangle(Polygon poly): Polygon(poly) {
    if (points_.size() != 3)
        throw std::invalid_argument("Triangle can not be constructed from polygon with not 3 points");
}

const Point &Triangle::a() const { return points_[0]; }
const Point &Triangle::b() const { return points_[1]; }
const Point &Triangle::c() const { return points_[2]; }

float Triangle::square() const {
    Vector2 ab     = Vector2(a(), b());
    float   ab_len = ab.length();

    Vector2 bc     = Vector2(b(), c());
    float   bc_len = bc.length();

    Vector2 ac     = Vector2(c(), a());
    float   ac_len = ac.length();

    float half_perimeter = (ab_len + bc_len + ac_len) / 2;
    float square =
        std::sqrt(half_perimeter * (half_perimeter - ab_len) * (half_perimeter - bc_len) * (half_perimeter - ac_len));

    return square;
}
