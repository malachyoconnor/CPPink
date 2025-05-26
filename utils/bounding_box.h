#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <point.h>
#include <ostream>

struct BoundingBox {
   Point bottomLeft;
   Point topRight;

   bool contains(const Point x) const {
      return bottomLeft <= x && x < topRight;
   }

   friend std::ostream &operator<<(std::ostream &output_stream,
                                   BoundingBox &bounding_box) {
      output_stream << "Bottom left: " << bounding_box.bottomLeft
                    << " Top right: " << bounding_box.topRight;
      return output_stream;
   }
};

#endif  // BOUNDING_BOX_H