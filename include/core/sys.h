#ifndef __CTOP_SYS_H__
#define __CTOP_SYS_H__

#include "../ui/box.h"

/// System information box is treated specially, as it is always visible,
/// and can only be placed in two locations (top or bottom of the window)
class SysBox : public IBox {
private:
   std::string hostname;
   std::string user;

public:
   SysBox(bool top, Vec2 size);

   bool set_keybind(char key, std::function<void()> func) override;
   bool set_clickbind(Vec2 pos, std::function<void()> func) override;

   void prepare() noexcept override;
   void draw() const noexcept override;
};

#endif // __CTOP_SYS_H__
