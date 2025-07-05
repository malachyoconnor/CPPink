#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H
#include <vector>

template <typename T>
struct BitVector : std::vector<T> {
   using std::vector<T>::vector;

   bool operator[](const int location) {
      const int byte = this->at(location / (sizeof(T) * 8));
      const int bit = location % (sizeof(T) * 8);

      return (byte >> bit) == 1;
   }

   bool operator[](const int location) const {
      const int byte = this->at(location / (sizeof(T) * 8));
      const int bit = location % (sizeof(T) * 8);

      return (byte >> bit) == 1;
   }
};

#endif //BIT_ARRAY_H
