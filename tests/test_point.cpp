
#include <gtest/gtest.h>
#include "geometry/Point.h"

// Test the constructor
TEST(PointTest, Constructor) {
    Point p1(3.0f, 4.0f);
    ASSERT_FLOAT_EQ(p1.x_, 3.0f);
    ASSERT_FLOAT_EQ(p1.y_, 4.0f);

    Point p2(2.0f); 
    ASSERT_FLOAT_EQ(p2.x_, 2.0f);
    ASSERT_FLOAT_EQ(p2.y_, 2.0f);
}

// Test the equality operator
TEST(PointTest, EqualityOperator) {
    Point p1(1.0f, 1.0f);
    Point p2(1.0f, 1.0f);
    Point p3(2.0f, 3.0f);

    ASSERT_TRUE(p1 == p2); // Points with identical coordinates should be equal
    ASSERT_FALSE(p1 == p3); // Points with different coordinates should not be equal
}

// Test the orientation of a triple of points
TEST(PointTest, TripleOrientation) {
    Point p(0.0f, 0.0f);
    Point q(4.0f, 4.0f);
    Point r1(1.0f, 1.0f); // Collinear point
    Point r2(1.0f, 2.0f); // Counter-clockwise
    Point r3(2.0f, 1.0f); // Clockwise

    ASSERT_EQ(Point::triple_orientation(p, q, r1), Point::OrientationType::COLLINEAR);
    ASSERT_EQ(Point::triple_orientation(p, q, r2), Point::OrientationType::COUNTER_CLOCKWISE);
    ASSERT_EQ(Point::triple_orientation(p, q, r3), Point::OrientationType::CLOCKWISE);
}

// Test if a point lies on a segment
TEST(PointTest, IsOnSegment) {
    Point segment_start(0.0f, 0.0f);
    Point segment_end(4.0f, 4.0f);
    Point p1(2.0f, 2.0f); // Point lies on the segment
    Point p2(5.0f, 5.0f); // Point lies outside the segment
    Point p3(1.0f, 2.0f); // Point does not lie on the line

    ASSERT_TRUE(Point::is_on_segment(segment_start, segment_end, p1));
    ASSERT_FALSE(Point::is_on_segment(segment_start, segment_end, p2));
    ASSERT_FALSE(Point::is_on_segment(segment_start, segment_end, p3));
}

// Test edge cases
TEST(PointTest, EdgeCases) {
    Point p1(0.0f, 0.0f);
    Point p2(0.0f, 0.0f);

    // Two identical points
    ASSERT_TRUE(p1 == p2);

    // Orientation test for identical points
    ASSERT_EQ(Point::triple_orientation(p1, p1, p1), Point::OrientationType::COLLINEAR);

    // Check for very close points
    Point close1(1e-7f, 1e-7f);
    Point close2(1e-7f, 2e-7f);
    ASSERT_EQ(Point::triple_orientation(p1, close1, close2), Point::OrientationType::COUNTER_CLOCKWISE);
}
