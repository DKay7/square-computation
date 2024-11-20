#include "geometry/Polygon.h"
#include <gtest/gtest.h>


TEST(Polyogn, Square) { EXPECT_TRUE(true); }

// TODO tests for:
//  1. special cases (triangle is a line or point)
//  2. dot product, cross product, intersection, triple_orientation etc.
//  3. test square computation
//  4. test that polygon square equals to the sum of its triangle squares after triangulation
