#ifndef __CTOP_UTIL_H__
#define __CTOP_UTIL_H__

#include <functional>
#include <cstddef>

struct Vec2 {
   size_t x;
   size_t y;

   bool operator==(const Vec2& r) const {
      return x == r.x && y == r.y;
   }

   Vec2(size_t x, size_t y) : x(x), y(y) {}
};

namespace std {
   template <>
   struct hash<Vec2> {
      size_t operator()(const Vec2& v) const {
         return hash<size_t>()(v.x) ^ (hash<size_t>()(v.y) << 1);
      }
   };
}

namespace Ui {
   void draw_outline(Vec2 pos, Vec2 size);
   void draw_corners(Vec2 pos, Vec2 size, bool rounded);
}

#endif // __CTOP_UTIL_H__
