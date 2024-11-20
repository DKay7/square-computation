#include "geometry/Vector2.h"

#include <cmath>
#include <gtest/gtest.h>

// Test the length() method
TEST(Vector2Test, Length) {
    Point   a = {0, 0};
    Point   b = {3, 4};
    Vector2 v(a, b);

    // Length of the vector from (0,0) to (3,4) should be 5 (3-4-5 triangle)
    ASSERT_FLOAT_EQ(v.length(), 5.0f);
}

// Test the distance_to(Point) method
TEST(Vector2Test, DistanceToPoint) {
    Point   a = {0, 0};
    Point   b = {3, 4};
    Vector2 v(a, b);

    Point p1 = {6, 8};
    ASSERT_FLOAT_EQ(v.distance_to(p1), 5.f);

    Point p2 = {-1, -1};
    ASSERT_FLOAT_EQ(v.distance_to(p2), sqrt(2));

    Point p3 = {10, -2};
    ASSERT_FLOAT_EQ(v.distance_to(p3), 9.2f);

    Point p4 = {1, 3};
    ASSERT_FLOAT_EQ(v.distance_to(p4), 1.f);

    Point   c = {1.5, 2};
    Vector2 v2 {c, b};

    ASSERT_FLOAT_EQ(v2.distance_to(a), 2.5);
}

// Test the distance_to(Vector2) method
TEST(Vector2Test, DistanceToVector) {
    Vector2 v1({0, 0}, {3, 4});

    Vector2 v2({6, 8}, {9, 12});
    ASSERT_FLOAT_EQ(v1.distance_to(v2), 5.f);

    Vector2 v3({-4, 7.5}, {-2, 6});
    ASSERT_FLOAT_EQ(v1.distance_to(v3), 5.2f);

    Vector2 v4({1, -6}, {4, 14});
    ASSERT_NEAR(v1.distance_to(v4), 0.49446, 1e-4);
}

// Test the cross_product() method
TEST(Vector2Test, CrossProduct) {
    Point   a = {1.5, 2};
    Vector2 v1(a, {3, 4});

    Vector2 v2(a, {4, 3});
    ASSERT_FLOAT_EQ(v1.cross_product(v2), -3.5f);

    Vector2 v3(a, {3.5, 0.5});
    ASSERT_FLOAT_EQ(v1.cross_product(v3), -6.25f);

    Vector2 v4(a, {0, 0});
    ASSERT_FLOAT_EQ(v1.cross_product(v4), 0.f);
}

// Test the dot_product() method
TEST(Vector2Test, DotProduct) {
    Point   a = {1.5, 2};
    Vector2 v1(a, {3, 4});

    Vector2 v2(a, {4, 3});
    ASSERT_FLOAT_EQ(v1.dot_product(v2), 5.75);

    Vector2 v3(a, {3.5, 0.5});
    ASSERT_FLOAT_EQ(v1.dot_product(v3), 0.0f);

    Vector2 v4(a, {0, 0});
    ASSERT_FLOAT_EQ(v1.dot_product(v4), -6.25f);
}

// Test the intersect() method
TEST(Vector2Test, Intersect) {
    Point   a = {1.5, 2};
    Vector2 v1(a, {3, 4});

    Vector2 v2(a, {4, 3});
    ASSERT_TRUE(v1.intersect(v2));

    Point   d {2.25, 3};
    Vector2 v3(d, {0, 0});
    ASSERT_TRUE(v1.intersect(v3)); 

    Vector2 v4({0.5, 1}, {2, 3}); 
    ASSERT_FALSE(v1.intersect(v4));

    Point   e {-3.03, 6.96};
    Vector2 v5(d, e);
    ASSERT_TRUE(v1.intersect(v5));
  
    Point f{0.97, 3.96};
    Vector2 v6(e, f);
    ASSERT_FALSE(v1.intersect(v6));
    
    Vector2 v7(f, {7.85, -1.2});
    ASSERT_TRUE(v1.intersect(v7));
}

// Test the get_direction() method
TEST(Vector2Test, GetDirection) {
    Point   a = {0, 0};
    Point   b = {1, 1};
    Vector2 v1(a, b);
    auto direction = v1.get_direction();

    ASSERT_FLOAT_EQ(direction.first, 1.0f);
    ASSERT_FLOAT_EQ(direction.second, 1.0f);

    Vector2 v2({5, 6}, {1, 5});
    direction = v2.get_direction();

    ASSERT_FLOAT_EQ(direction.first, -4.f);
    ASSERT_FLOAT_EQ(direction.second, -1.f);
}
