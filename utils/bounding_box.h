#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <point.h>
#include <ostream>

struct BoundaryBox {
   Point bottomLeft;
   Point topRight;

   bool contains(const Point p) const {
      return bottomLeft <= p && p < topRight;
   }

   friend std::ostream &operator<<(std::ostream &output_stream,
                                   BoundaryBox &bounding_box) {
      output_stream << "Bottom left: " << bounding_box.bottomLeft
                    << " Top right: " << bounding_box.topRight;
      return output_stream;
   }
};

#endif  // BOUNDING_BOX_H