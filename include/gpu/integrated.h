#ifndef __CTOP_INTEGRATED_H__
#define __CTOP_INTEGRATED_H__

#include "igpu.h"

class IntegratedHandler : public IGpuHandler {
public:
   IntegratedHandler();
   ~IntegratedHandler();

   bool init() override;
   std::string get_name() override;
   int get_temperature() override;
   int get_load() override;

private:
};

#endif // __CTOP_INTEGRATED_H__
