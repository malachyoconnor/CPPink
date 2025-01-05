#ifndef POINT_H
#define POINT_H

class Point {
public:
    int x;
    int y;

    Point(const int newX, const int newY) {
        x = newX;
        y = newY;
    };

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator*(const int &other) const {
        return {x * other, y * other};
    }

    Point operator/(const int &other) const {
        return {x / other, y / other};
    }
};


#endif //POINT_H
