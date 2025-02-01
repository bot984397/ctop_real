#include "../../include/gpu/igpu.h"
#include "../../include/gpu/nvml.h"
#include "../../include/gpu/rocm.h"
#include "../../include/gpu/integrated.h"

IGpuHandler::IGpuHandler() {}

std::vector<std::unique_ptr<IGpuHandler>> IGpuHandler::create_all() {
   std::vector<std::unique_ptr<IGpuHandler>> handlers;

   if (auto nvml_handler = try_create<NvmlHandler>()) {
      handlers.push_back(std::move(nvml_handler));
   }
   if (auto rocm_handler = try_create<RocmHandler>()) {
      handlers.push_back(std::move(rocm_handler));
   }
   if (auto integrated_handler = try_create<IntegratedHandler>()) {
      handlers.push_back(std::move(integrated_handler));
   }

   return handlers;
}
