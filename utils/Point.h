#ifndef POINT_H
#define POINT_H

struct BoundaryBox;

class Point {
public:
   int x;
   int y;

   Point(const int newX, const int newY) {
      x = newX;
      y = newY;
   };

   bool operator<(const Point& other) const {
      return x < other.x and y < other.y;
   }

   bool operator>=(const Point& other) const {
      return x >= other.x and y >= other.y;
   }

   bool operator<=(const Point& other) const {
      return x <= other.x and y <= other.y;
   }

   Point operator+(const int scalarToAdd) const {
      return {x + scalarToAdd, y + scalarToAdd};
   }

   Point operator+(const Point& other) const {
      return {x + other.x, y + other.y};
   }

   Point operator-(const Point& other) const {
      return {x - other.x, y - other.y};
   }

   Point operator*(const int& other) const { return {x * other, y * other}; }

   Point operator/(const int& other) const { return {x / other, y / other}; }

   friend std::ostream& operator<<(std::ostream& output_stream,
                                   const Point& point) {
      output_stream << "(" << point.x << ", " << point.y << ")";
      return output_stream;
   }

   [[nodiscard]] bool withinBounds(BoundaryBox bounds) const;

   static Point PointMaximums(Point p1, Point p2) {
      return {std::max(p1.x, p2.x), std::max(p1.y, p2.y)};
   }

   static Point PointMinimums(Point p1, Point p2) {
      return {std::min(p1.x, p2.x), std::min(p1.y, p2.y)};
   }
};

#endif  // POINT_H
