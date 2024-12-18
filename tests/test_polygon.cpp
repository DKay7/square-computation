#include <gtest/gtest.h>
#include "geometry/Polygon.h"
#include "geometry/Triangle.h"
#include <cmath>

    
static Polygon complex_test_poly{{-2, 1}, {0, 0}, {8, 0}, {3, 1}, {8, 3}, {3, 3}, {2, 1}, {2, 4}, {-10, 4}, {-10, -4}, {-4, 2}, {-4, -2}};

bool are_floats_equal(float a, float b, float epsilon = 1e-5f) {
    return std::fabs(a - b) < epsilon;
}

// Test constructor
TEST(PolygonTest, Constructor) {
    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3)});
    auto points = polygon.get_points();
    
    ASSERT_EQ(points.size(), 3);
    ASSERT_FLOAT_EQ(points[0].x_, 0.0f);
    ASSERT_FLOAT_EQ(points[0].y_, 0.0f);
    ASSERT_FLOAT_EQ(points[1].x_, 4.0f);
    ASSERT_FLOAT_EQ(points[1].y_, 0.0f);
    ASSERT_FLOAT_EQ(points[2].x_, 4.0f);
    ASSERT_FLOAT_EQ(points[2].y_, 3.0f);
}

// Test square calculation
TEST(PolygonTest, Square) {
    Polygon triangle({Point(0, 0), Point(4, 0), Point(4, 3)});
    ASSERT_FLOAT_EQ(triangle.square(), 6.0f); // Area of triangle is 1/2 * base * height

    Polygon rectangle({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});
    ASSERT_FLOAT_EQ(rectangle.square(), 12.0f); // Area of rectangle is width * height
    
    Polygon trapezoid({{-4, 0}, {-7, 3}, {6, 3}, {5, 0}});
    ASSERT_FLOAT_EQ(trapezoid.square(), 33.f); 

    Polygon line({{0, 0}, {100, 100}});
    ASSERT_FLOAT_EQ(line.square(), 0.f); 
  
    ASSERT_FLOAT_EQ(complex_test_poly.square(), 63.5f);
}

/*// Test triangulation*/
/*TEST(PolygonTest, Triangulation) {*/
/*    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});*/
/*    auto triangles = polygon.triangulate();*/
/**/
/*    ASSERT_EQ(triangles.size(), 2); // Rectangle should be split into 2 triangles*/
/*    float triangle_areas = 0.0f;*/
/*    for (const auto &triangle : triangles) {*/
/*        triangle_areas += triangle.square();*/
/*    }*/
/**/
/*    ASSERT_TRUE(are_floats_equal(triangle_areas, polygon.square()));*/
/*}*/
/**/
/*// Test split*/
/*TEST(PolygonTest, Split) {*/
/*    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});*/
/*    auto [part1, part2] = polygon.split(0, 2);*/
/**/
/*    ASSERT_TRUE(part1.get_points().size() >= 3);*/
/*    ASSERT_TRUE(part2.get_points().size() >= 3);*/
/**/
/*    float combined_area = part1.square() + part2.square();*/
/*    ASSERT_TRUE(are_floats_equal(combined_area, polygon.square()));*/
/*}*/

// Test is_chord
/*TEST(PolygonTest, IsChord) {*/
/*    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});*/
/*    ASSERT_TRUE(polygon.is_chord(0, 2)); // Diagonal from (0,0) to (4,3)*/
/*    ASSERT_FALSE(polygon.is_chord(0, 1)); // Edge between adjacent vertices*/
/**/
/*    ASSERT_TRUE(complex_test_poly.is_chord(0, 6)); // A-G*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(1, 6)); // B-G*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(3, 6)); // D-G*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(0, 7)); // A-H*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(1, 7)); // B-H*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(1, 7)); // B-H*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(10, 8)); // K-I*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(10, 0)); // K-A*/
/*    ASSERT_TRUE(complex_test_poly.is_chord(8, 6)); // I-G*/
/**/
/*    ASSERT_FALSE(complex_test_poly.is_chord(0, 9)); // A-J*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(11, 6)); // L-G*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(11, 6)); // L-G*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(7, 5)); // H-F // FIXME: Fails here*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(0, 1)); // A-B*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(0, 1)); // A-B*/
/*    ASSERT_FALSE(complex_test_poly.is_chord(2, 8)); // C-I*/
/**/
/*}*/

// Test neighbor retrieval
TEST(PolygonTest, GetNeighbour) {
    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});
    auto [neighbour_clockwise, idx_clockwise] = polygon.get_neighbour(0, Polygon::NeighbourDirection::CLOCKWISE);
    ASSERT_FLOAT_EQ(neighbour_clockwise.x_, 4.0f);
    ASSERT_FLOAT_EQ(neighbour_clockwise.y_, 0.0f);
    ASSERT_EQ(idx_clockwise, 1);

    auto [neighbour_counter, idx_counter] = polygon.get_neighbour(0, Polygon::NeighbourDirection::COUNTER_CLOCKWISE);
    ASSERT_FLOAT_EQ(neighbour_counter.x_, 0.0f);
    ASSERT_FLOAT_EQ(neighbour_counter.y_, 3.0f);
    ASSERT_EQ(idx_counter, 3);
}

/*// Test triangulation area sum equals original polygon area*/
/*TEST(PolygonTest, TriangulationAreaSum) {*/
/*    Polygon polygon({Point(0, 0), Point(4, 0), Point(4, 3), Point(0, 3)});*/
/*    auto triangles = polygon.triangulate();*/
/*    float original_area = polygon.square();*/
/*    float triangulated_area = 0.0f;*/
/**/
/*    for (const auto &triangle : triangles) {*/
/*        triangulated_area += triangle.square();*/
/*    }*/
/**/
/*    ASSERT_TRUE(are_floats_equal(original_area, triangulated_area));*/
/*}*/
