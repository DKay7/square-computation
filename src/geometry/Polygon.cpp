#include "geometry/Polygon.h"

#include "geometry/Point.h"
#include "geometry/Triangle.h"
#include "geometry/Vector2.h"

#include <initializer_list>
#include <iterator>
#include <stdexcept>
#include <utility>

Polygon::Polygon(std::initializer_list<Point> points): points_(points) {}

const std::vector<Point> &Polygon::get_points() const { return points_; }

float Polygon::square() const {
    float sum = 0;

    for (int point_idx = 0; point_idx < points_.size(); ++point_idx) {
        int next_point_idx = (point_idx + 1) % points_.size();
        sum += points_[point_idx].x_ * points_[next_point_idx].y_ - points_[next_point_idx].x_ * points_[point_idx].y_;
    }

    return sum / 2;
}

std::vector<Triangle> Polygon::triangulate() const {
    std::vector<Triangle> triangles;

    if (points_.size() == 3) {
        triangles.push_back(Triangle {*this});
        return triangles;
    }

    auto [convex_vertex, convex_vertex_idx] = find_convex_vertex();

    auto intruding_vertex = find_intruding_vertex();

    if (!intruding_vertex.has_value()) {
        int left_neighbour_idx  = (convex_vertex_idx + 1) % points_.size();
        int right_neighbour_idx = (convex_vertex_idx - 1 + points_.size()) % points_.size();

        auto [splitted_part, left_part] = split(left_neighbour_idx, right_neighbour_idx);
        Triangle t {splitted_part};
        triangles.push_back(t);

        auto left_triangles = left_part.triangulate();
        triangles.insert(triangles.end(), left_triangles.begin(), left_triangles.end());
    }
    else {
    }

    return triangles;
}

std::pair<Polygon, Polygon> Polygon::split(int a_idx, int b_idx) const {
    if (!is_chord(a_idx, b_idx))
        throw std::invalid_argument("Vector{a, b} must be a polygon chord to split it");

    // TODO: split
    //
    return {{}, {}};
}

bool Polygon::is_chord(int a_idx, int b_idx) const {
    // just check all vertices on intersection with our potential chord
    Vector2 potential_chord {points_[a_idx], points_[b_idx]};

    for (int vertex_idx = 0; vertex_idx < points_.size(); ++vertex_idx) {
        int next_vertex_idx = (vertex_idx + 1) % points_.size();

        if ((a_idx == vertex_idx and b_idx == next_vertex_idx) or (a_idx == next_vertex_idx and b_idx == vertex_idx))
            continue;

        if (potential_chord.intersect({points_[vertex_idx], points_[next_vertex_idx]}))
            return false;
    }

    return true;
}

std::optional<std::pair<const Point &, int>> Polygon::find_intruding_vertex() const { return {{points_[0], 0}}; }

std::pair<const Point &, int> Polygon::find_convex_vertex() const { return {points_[0], 0}; }
