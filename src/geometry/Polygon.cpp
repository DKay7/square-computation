#include "geometry/Polygon.h"

#include "geometry/Point.h"
#include "geometry/Triangle.h"
#include "geometry/Vector2.h"

#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <omp.h>
#include <stdexcept>
#include <utility>

Polygon::Polygon(std::initializer_list<Point> points): points_(points) {}

const std::vector<Point> &Polygon::get_points() const { return points_; }

float Polygon::square() const {
    float sum = 0;

#pragma omp parallel for
    for (int point_idx = 0; point_idx < points_.size(); ++point_idx) {
        int next_point_idx = get_neighbour(point_idx, NeighbourDirection::CLOCKWISE).second;
        sum += (points_[point_idx].x_ * points_[next_point_idx].y_ - points_[next_point_idx].x_ * points_[point_idx].y_);
    }

    return std::abs(sum) / 2;
}

std::vector<Triangle> Polygon::triangulate() const {
    std::vector<Triangle> triangles;

    if (points_.size() == 3) {
        triangles.push_back(Triangle {*this});
        return triangles;
    }

    auto [convex_vertex, convex_vertex_idx] = find_convex_vertex();

    auto intruding_vertex_pair = find_intruding_vertex();

    if (!intruding_vertex_pair.has_value()) {
        // If no intruding vertex, just split by AB which connects convex vertex neighbours

        int clockwise_neighbour_idx         = get_neighbour(convex_vertex_idx, NeighbourDirection::CLOCKWISE).second;
        int counter_clockwise_neighbour_idx = get_neighbour(convex_vertex_idx, NeighbourDirection::COUNTER_CLOCKWISE).second;

        auto [splitted_part, left_part] = split(clockwise_neighbour_idx, counter_clockwise_neighbour_idx);
        triangles.push_back(Triangle {splitted_part});

        auto left_triangles = left_part.triangulate();
        triangles.insert(triangles.end(), left_triangles.begin(), left_triangles.end());
    }
    else {
        // If there's intruding vertex, split by CD where C is convex vertex and D is intruding vertex
        auto [part_a, part_b] = split(intruding_vertex_pair->second, convex_vertex_idx);

        auto part_a_triangles = part_a.triangulate();
        triangles.insert(triangles.end(), part_a_triangles.begin(), part_a_triangles.end());

        auto part_b_triangles = part_b.triangulate();
        triangles.insert(triangles.end(), part_b_triangles.begin(), part_b_triangles.end());
    }

    return triangles;
}

std::pair<Polygon, Polygon> Polygon::split(int a_idx, int b_idx) const {
    if (a_idx == b_idx)  // FIXME: Fix is_chord function for outside lines
                         /*if (!is_chord(a_idx, b_idx) or a_idx == b_idx)*/
        throw std::invalid_argument("Vector{a, b} must be a polygon chord to split it");

    std::vector<Point> part_a, part_b;

    for (int vertex_idx = 0; vertex_idx < points_.size(); ++vertex_idx) {
        if (vertex_idx >= a_idx and vertex_idx <= b_idx)
            part_b.push_back(points_[vertex_idx]);
        else
            part_a.push_back(points_[vertex_idx]);
    }

    return {{part_a}, {part_b}};
}

bool Polygon::is_chord(int a_idx, int b_idx) const {
    // just check all vertices on intersection with our potential chord
    Vector2 potential_chord {points_[a_idx], points_[b_idx]};

    for (int vertex_idx = 0; vertex_idx < points_.size(); ++vertex_idx) {
        int next_vertex_idx = get_neighbour(vertex_idx, NeighbourDirection::CLOCKWISE).second;

        // Check if potential chord is a side of poly
        if ((a_idx == vertex_idx and b_idx == next_vertex_idx) or (a_idx == next_vertex_idx and b_idx == vertex_idx))
            return false;

        // Check if potential chord intersects some side of poly, but not in the ends of this side
        if (potential_chord.intersect({points_[vertex_idx], points_[next_vertex_idx]}) and
            (a_idx != vertex_idx and a_idx != next_vertex_idx) and (b_idx != vertex_idx and b_idx != next_vertex_idx))
            return false;
    }

    return true;
}

std::pair<const Point &, int> Polygon::get_neighbour(int idx, NeighbourDirection dir) const {
    if (dir == NeighbourDirection::CLOCKWISE) {
        int clockwice_neighbour_idx = (idx + 1) % points_.size();
        return {points_[clockwice_neighbour_idx], clockwice_neighbour_idx};
    }

    int counter_clockwice_neighbour_idx = (idx - 1 + points_.size()) % points_.size();
    return {points_[counter_clockwice_neighbour_idx], counter_clockwice_neighbour_idx};
}

std::pair<const Point &, int> Polygon::find_convex_vertex() const {
    if (points_.size() < 3)
        return {points_[0], 0};

    for (int convex_candidate_idx = 0; convex_candidate_idx < points_.size(); ++convex_candidate_idx) {
        auto clockwice_neighbour         = get_neighbour(convex_candidate_idx, NeighbourDirection::CLOCKWISE);
        auto counter_clockwice_neighbour = get_neighbour(convex_candidate_idx, NeighbourDirection::COUNTER_CLOCKWISE);

        auto orientation = Point::triple_orientation(counter_clockwice_neighbour.first, points_[convex_candidate_idx],
                                                     clockwice_neighbour.first);

        if (orientation == Point::OrientationType::CLOCKWISE)
            return {points_[convex_candidate_idx], convex_candidate_idx};
    }

    // the only way we came up here is that all our points are laying on one line,
    // so, just return any of them

    return {points_[0], 0};
}

std::optional<std::pair<const Point &, int>> Polygon::find_intruding_vertex() const {
    /*
        The algorithm is simple. First, we find convex vertex (let it be B) and its neighbours:
        counter-clockwice (let it be A) and clockwise (let it be C).

        We define an intruding vertex as a vertex D which lays inside of the ABC triangle,
        and the distance from D to AC is_chord maximum (if we have several possible intruding points,
        we choose the one with maximum distance to CA).

        So, to do that, we just iterate over poly and check if another vertice is inside of the ABC,
        and if so, check its' distance to CA.
    */

    auto [convex_vertex, convex_vertex_idx]             = find_convex_vertex();
    auto [clockwice_neighbour, clockwice_neighbour_idx] = get_neighbour(convex_vertex_idx, NeighbourDirection::CLOCKWISE);
    auto [counter_clockwice_neighbour, counter_clockwice_neighbour_idx] =
        get_neighbour(convex_vertex_idx, NeighbourDirection::COUNTER_CLOCKWISE);

    Vector2  ca_edge(counter_clockwice_neighbour, clockwice_neighbour);
    Triangle abc {counter_clockwice_neighbour, convex_vertex, clockwice_neighbour};

    std::optional<std::pair<Point, int>> intrudind_candidate = std::nullopt;
    float                                max_distance        = -1;

    // iterate throught whole polygon, but start from convex vertex clockwise neighbour
    for (int vertex_idx = clockwice_neighbour_idx; vertex_idx != convex_vertex_idx;
         vertex_idx     = get_neighbour(vertex_idx, NeighbourDirection::CLOCKWISE).second)
    {
        Point current_vertex = points_[vertex_idx];

        // if another vertex is not inside our triangle, just skip it
        if (!abc.is_point_inside(current_vertex))
            continue;

        // check distance
        double distance_to_ca = ca_edge.distance_to(current_vertex);
        if (distance_to_ca > max_distance) {
            intrudind_candidate = {current_vertex, vertex_idx};
            max_distance        = distance_to_ca;
        }
    }

    return intrudind_candidate;
}
