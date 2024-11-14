#include "geometry/Triangle.h"
#include "geometry/Line.h"
#include <cmath>

float Triangle::square() const { 
    Vector2 ab = Vector2(a_, b_); // TODO: maybe triangle need to store these lines
	float ab_len = ab.length();

    Vector2 bc = Vector2(b_, c_);
	float bc_len = bc.length();

    Vector2 ac = Vector2(c_, a_);
	float ac_len = ac.length();

    float half_perimeter = (ab_len + bc_len + ac_len) / 2;
    float square = std::sqrt(half_perimeter * (half_perimeter - ab_len) * (half_perimeter - bc_len) * (half_perimeter - ac_len));

    return square; 
}
