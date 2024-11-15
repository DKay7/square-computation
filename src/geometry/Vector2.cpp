
#include "geometry/Vector2.h"

#include "geometry/Point.h"
#include "geometry/Triangle.h"

#include <algorithm>

Vector2::Vector2(Point a, Point b): begin_(a), end_(b) {}

float Vector2::length() const {
    return std::sqrt((begin_.x_ - end_.x_) * (begin_.x_ - end_.x_) + (begin_.y_ - end_.y_) * (begin_.y_ - end_.y_));
}

float Vector2::cross_product(Vector2 other) const {
    auto [x, y]             = get_direction();
    auto [other_x, other_y] = other.get_direction();

    // since we working with 2d vectors, their vector product will
    // only have z-coodrinate, therefore, we need only to compute
    // that coordinate to obtain length of vector product's vector
    float vector_product_len = (x * other_y - y * other_x);

    return vector_product_len;
}

float Vector2::dot_product(Vector2 other) const {
    auto [x, y]             = get_direction();
    auto [other_x, other_y] = other.get_direction();

    return x * other_x + y * other_y;
}

std::pair<float, float> Vector2::get_direction() const {
    float x = end_.x_ - begin_.x_;
    float y = end_.y_ - begin_.y_;

    return {x, y};
}

bool Vector2::intersect(Vector2 other) const {
    // just rough math...
    Point::OrientationType o1 = Point::triple_orientation(begin_, end_, other.begin_);
    Point::OrientationType o2 = Point::triple_orientation(begin_, end_, other.end_);
    Point::OrientationType o3 = Point::triple_orientation(other.begin_, other.end_, begin_);
    Point::OrientationType o4 = Point::triple_orientation(other.begin_, other.end_, end_);

    // General case
    if (o1 != o2 and o3 != o4)
        return true;

    // Special cases
    if (o1 == Point::OrientationType::COLLINEAR and Point::is_on_segment(begin_, other.begin_, end_) or
        o2 == Point::OrientationType::COLLINEAR and Point::is_on_segment(begin_, other.end_, end_) or
        o3 == Point::OrientationType::COLLINEAR and Point::is_on_segment(other.begin_, begin_, other.end_) or
        o4 == Point::OrientationType::COLLINEAR and Point::is_on_segment(other.begin_, end_, other.end_))
        return true;

    return false;
}

float Vector2::distance_to(Point p) const {
    // Project point to line of vector,
    // if its projection belongs to vector, then compute distance from projecion to point.
    // If not, then compute distance from nearest end of the vector to point

    Vector2 ap {Point {0, 0}, p};

    float projection = dot_product(ap) / dot_product(*this);

    if (projection < 0)
        return Vector2 {begin_, p}.length();
    else if (projection > 1)
        return Vector2 {end_, p}.length();

    // Compute distance via area of triangle
    Triangle apb {begin_, p, end_};
    return apb.square() / length();
}

float Vector2::distance_to(Vector2 other) const {
    float d1 = distance_to(other.begin_);
    float d2 = distance_to(other.end_);
    float d3 = other.distance_to(begin_);
    float d4 = other.distance_to(end_);

    return std::min({d1, d2, d3, d4});
}
