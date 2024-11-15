#ifndef POLYGON_H
#define POLYGON_H

#include "geometry/Point.h"

#include <initializer_list>
#include <optional>
#include <vector>

class Triangle;

class Polygon {
public:
    Polygon(std::initializer_list<Point> points);
    Polygon(std::vector<Point> points): points_(points) {}

    virtual ~Polygon() = default;
    virtual float square() const;

    std::vector<Triangle> triangulate() const;

    const std::vector<Point>   &get_points() const;
    std::pair<Polygon, Polygon> split(int a_idx, int b_idx) const;
    bool                        is_chord(int a_idx, int b_idx) const;
    /*Polygon                    &operator=(Polygon &other) = default;*/
    /*Polygon                    &operator=(const Polygon &other) = default;*/
    
    enum class NeighbourDirection {
        CLOCKWISE = 0,
        COUNTER_CLOCKWISE = 1,
    };

    std::pair<const Point &, int> get_neighbour(int idx, NeighbourDirection dir) const;

protected:
    std::vector<Point> points_;

private:
    std::optional<std::pair<const Point &, int>> find_intruding_vertex() const;
    std::pair<const Point &, int>                find_convex_vertex() const;
};

#endif
