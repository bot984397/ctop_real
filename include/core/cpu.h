#ifndef __CTOP_CPU_H__
#define __CTOP_CPU_H__

#include "../ui/box.h"

class CpuBox : public IBox {
public:
   CpuBox(size_t pos, Vec2 size, bool active)
      : IBox("cpu", pos, size, active) {}

   bool set_keybind(char key, std::function<void()> func) override;
   bool set_clickbind(Vec2 pos, std::function<void()> func) override;
   void draw() const noexcept override;
};

#endif // __CTOP_CPU_H__
