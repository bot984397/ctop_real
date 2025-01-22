#ifndef __CTOP_MEM_H__
#define __CTOP_MEM_H__

#include "../ui/box.h"

class MemBox : public IBox {
public:
   MemBox(size_t pos, Vec2 size, bool active)
      : IBox("mem", pos, size, active) {}

   bool set_keybind(char key, std::function<void()> func) override;
   bool set_clickbind(Vec2 pos, std::function<void()> func) override;
   void draw() const noexcept override;
};

#endif // __CTOP_MEM_H__
