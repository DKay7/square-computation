#include "geometry/Vector2.h"

Vector2::Vector2(Point a, Point b): begin_(a), end_(b) {}

float Vector2::length() const {
    return std::sqrt((begin_.x_ - end_.x_) * (begin_.x_ - end_.x_) + (begin_.y_ - end_.y_) * (begin_.y_ - end_.y_));
}

bool Vector2::intersect(Vector2 other) {
    enum OrientationType {
        COLLINEAR         = 0,
        CLOCKWISE         = 1,
        COUNTER_CLOCKWISE = 2
    };

    auto orientation = [](const Point p, const Point q, const Point r) {
        float product = (q.y_ - p.y_) * (r.x_ - q.x_) - (q.x_ - p.x_) * (r.y_ - q.y_);

        bool is_zero = std::fabs(product) < std::numeric_limits<double>::epsilon();

        if (is_zero)
            return COLLINEAR;

        return product > 0 ? CLOCKWISE : COUNTER_CLOCKWISE;
    };

    auto on_segment = [](const Point p, const Point q, const Point r) {
        return ((q.x_ <= std::max(p.x_, r.x_) and q.x_ >= std::min(p.x_, r.x_)) and
                (q.y_ <= std::max(p.y_, r.y_) and q.y_ >= std::min(p.y_, r.y_)));
    };

    // just rough math...

    OrientationType o1 = orientation(begin_, end_, other.begin_);
    OrientationType o2 = orientation(begin_, end_, other.end_);
    OrientationType o3 = orientation(other.begin_, other.end_, begin_);
    OrientationType o4 = orientation(other.begin_, other.end_, end_);

    // General case
    if (o1 != o2 and o3 != o4)
        return true;

    // Special cases
    if (o1 == COLLINEAR and on_segment(begin_, other.begin_, end_) or
        o2 == COLLINEAR and on_segment(begin_, other.end_, end_) or
        o3 == COLLINEAR and on_segment(other.begin_, begin_, other.end_) or
        o4 == COLLINEAR and on_segment(other.begin_, end_, other.end_))
        return true;

    return false;
}
