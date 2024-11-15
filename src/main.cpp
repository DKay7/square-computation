
#include "geometry/Triangle.h"
#include <iostream>

int main() {
    Triangle t{Point{0, 0}, Point{1, 0}, Point{0, 2}};
    Polygon p{Point{0, 0}, Point{1, 0}, Point{0, 2}};

    std::cout << t.square() << "\n" << p.square() << "\n"; 
}
