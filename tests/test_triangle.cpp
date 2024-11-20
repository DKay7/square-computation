#include "geometry/Point.h"
#include "geometry/Triangle.h"

#include <gtest/gtest.h>
#include <vector>


std::vector<std::pair<Triangle, float>> generate_test_triangles() {
    return {
        { Triangle({0, 0}, {2, 0}, {1, static_cast<float>(std::sqrt(3))}), 1.732},
        { Triangle({0, 0}, {4, 0}, {2, 3}), 6},
        { Triangle({0, 0}, {3, 0}, {0, 4}), 6},
        { Triangle({0, 0}, {5, 0}, {1, 1}), 2.5},
        { Triangle({0, 0}, {2, 1}, {1, 3}), 2.5}
    };
}
TEST(Triangle, Ctor) {
    std::vector<Point> triangle_points {Point {0, 0}, Point {1, 1}, Point {2, 2}};

    Triangle t1(triangle_points[0], triangle_points[1], triangle_points[2]);

    EXPECT_EQ(t1.a(), triangle_points[0]);
    EXPECT_EQ(t1.b(), triangle_points[1]);
    EXPECT_EQ(t1.c(), triangle_points[2]);

}

TEST(Triangle, Square) {
    auto triangles = generate_test_triangles();
    for (const auto& [triangle, ans] : triangles) {
        EXPECT_NEAR(triangle.square(), ans, 1e3);
    }
}

TEST(Triangle, PointInside) {
    auto triangles = generate_test_triangles();
    std::vector<Point> inside_points = {
        {1, 1}, {2, 1.5}, {1, 2}, {3, 0.25}, {0.5, 0.5}
    };
    std::vector<Point> outside_points = {
        {10, 10}, {5, 5}, {3, 3}, {-1, -1}, {6, 6}
    };

    for (size_t i = 0; i < triangles.size(); ++i) {
        EXPECT_TRUE(triangles[i].first.is_point_inside(inside_points[i]));
        EXPECT_FALSE(triangles[i].first.is_point_inside(outside_points[i]));
    }
}
