#ifndef __CTOP_ROCM_H__
#define __CTOP_ROCM_H__

#include "igpu.h"

class RocmHandler : public IGpuHandler {
public:
   RocmHandler();
   ~RocmHandler();

   bool init() override;
   std::string get_name() override;
   int get_temperature() override;
   int get_load() override;

private:
};

#endif // __CTOP_ROCM_H__
