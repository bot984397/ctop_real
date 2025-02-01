#include "../../include/igpu.h"
#include "../../include/nvml.h"
#include "../../include/rocm.h"
#include "../../include/integrated.h"

IGpuHandler::IGpuHandler() {}

std::unique_ptr<IGpuHandler> IGpuHandler::create() {
   if (auto nvml_handler = try_create<NvmlHandler>()) return nvml_handler;
   if (auto rocm_handler = try_create<RocmHandler>()) return rocm_handler;
   return std::make_unique<IntegratedHandler>();
}
