#include "../../include/gpu/nvml.h"

#define DECL_NVML(fn, ret, ...) \
   typedef ret (*fn##_t)(__VA_ARGS__); \
   fn##_t fn

#define LOAD_NVML(fn) \
   fn = (fn##_t)dlsym(m_handle, #fn); \
   if (!fn) return false

NvmlHandler::NvmlHandler() : IGpuHandler() {

}

NvmlHandler::init() {

}

NvmlHandler::load_exports() {

}
