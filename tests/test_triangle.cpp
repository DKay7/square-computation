#include "geometry/Point.h"
#include "geometry/Triangle.h"

#include <gtest/gtest.h>
#include <vector>

TEST(Triangle, Ctor) {
    std::vector<Point> triangle_points {Point {0, 0}, Point {1, 1}, Point {2, 2}};

    Triangle t1(triangle_points[0], triangle_points[1], triangle_points[2]);

    EXPECT_EQ(t1.get_points(), triangle_points);
}

TEST(Triangle, Square) { EXPECT_TRUE(true); }

// TODO tests for:
//  1. special cases (triangle is a line or point)
//  2. dot product, cross product, intersection, triple_orientation etc.
//  3. test square computation
//  4. test that polygon square equals to the sum of its triangle squares after triangulation
