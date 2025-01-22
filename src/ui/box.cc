#include "../../include/ui/box.h"

class DiskBox : public IBox {
public:
   DiskBox(size_t pos, Vec2 size, bool active)
      : IBox("disk", pos, size, active) {}
};

class ProcBox : public IBox {
public:
   ProcBox(size_t pos, Vec2 size, bool active)
      : IBox("proc", pos, size, active) {}
};

class NetBox : public IBox {
public:
   NetBox(size_t pos, Vec2 size, bool active)
      : IBox("net", pos, size, active) {}
};

class GpuBox : public IBox {
public:
   GpuBox(size_t pos, Vec2 size, bool active)
      : IBox("gpu", pos, size, active) {}
};
