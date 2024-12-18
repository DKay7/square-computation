
#include "geometry/Triangle.h"

#include <iostream>

int main() {
    for (int i = 0; i < 10000000; ++i) {
        Triangle t {Point {0, 0}, Point {static_cast<float>(1. * i), 0}, Point {0, static_cast<float>(2. * i)}};
        Polygon  p {Point {0, 0}, Point {static_cast<float>(1. * i), 0}, Point {0, static_cast<float>(2. * i)}};
        volatile auto t_sqr = t.square();
        volatile auto p_sqr = p.square();

        /*std::cout << t.square() << "\n" << p.square() << "\n";*/
    }
}
