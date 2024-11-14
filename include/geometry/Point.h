#ifndef POINT_H
#define POINT_H

class Point final {
public:
    explicit Point(float x, float y): x_(x), y_(y) {}
    explicit Point(float both): x_(both), y_(both) {}

private:
    float x_ = 0;
    float y_ = 0;
};

#endif
