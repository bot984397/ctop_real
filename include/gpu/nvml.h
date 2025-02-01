#ifndef __CTOP_NVML_H__
#define __CTOP_NVML_H__

#include "igpu.h"

typedef void *nvmlDevice_t;

typedef struct {
   unsigned long long total;
   unsigned long long free;
   unsigned long long used;
} nvmlMemory_t;

typedef enum {
   NVML_SUCCESS = 0,
   NVML_ERROR_UNINITIALIZED = 1,
   NVML_ERROR_INVALID_ARGUMENT = 2,
   NVML_ERROR_NOT_SUPPORTED = 3,
   NVML_ERROR_NO_PERMISSION = 4,
   NVML_ERROR_ALREADY_INITIALIZED = 5,
   NVML_ERROR_NOT_FOUND = 6,
   NVML_ERROR_INSUFFICIENT_SIZE = 7,
   NVML_ERROR_INSUFFICIENT_POWER = 8,
   NVML_ERROR_DRIVER_NOT_LOADED = 9,
   NVML_ERROR_TIMEOUT = 10,
   NVML_ERROR_IRQ_ISSUE = 11,
   NVML_ERROR_LIBRARY_NOT_FOUND = 12,
   NVML_ERROR_FUNCTION_NOT_FOUND = 13,
   NVML_ERROR_CORRUPTED_INFOROM = 14,
   NVML_ERROR_GPU_IS_LOST = 15,
   NVML_ERROR_RESET_REQUIRED = 16,
   NVML_ERROR_OPERATING_SYSTEM = 17,
   NVML_ERROR_LIB_RM_VERSION_MISMATCH = 18,
   NVML_ERROR_IN_USE = 19,
   NVML_ERROR_MEMORY = 20,
   NVML_ERROR_NO_DATA = 21,
   NVML_ERROR_VGPU_ECC_NOT_SUPPORTED = 22,
   NVML_ERROR_INSUFFICIENT_RESOURCES = 23,
   NVML_ERROR_FREQ_NOT_SUPPORTED = 24,
   NVML_ERROR_ARGUMENT_VERSION_MISMATCH = 25,
   NVML_ERROR_DEPRECATED = 26,
   NVML_ERROR_NOT_READY = 27,
   NVML_ERROR_GPU_NOT_FOUND = 28,
   NVML_ERROR_INVALID_STATE = 29,
   NVML_ERROR_UNKNOWN = 999,
} nvmlReturn_t;

#define DECL_NVML(fn, ret, ...) \
   typedef ret (*fn##_t)(__VA_ARGS__); \
   fn##_t fn

#define LOAD_NVML(fn) \
   fn = (fn##_t)dlsym(m_handle, #fn); \
   if (!fn) { \
      throw std::runtime_error("Failed to load NVML function"); \
   }

class NvmlHandler : public IGpuHandler {
public:
   NvmlHandler();
   ~NvmlHandler();

   bool init() override;
   std::string get_name() override;
   int get_temperature() override;
   int get_load() override;

private:
   void *m_handle;

   DECL_NVML(nvmlInit, nvmlReturn_t, void);
   DECL_NVML(nvmlShutdown, nvmlReturn_t, void);
   DECL_NVML(nvmlDeviceGetCount, nvmlReturn_t, unsigned int*);
   DECL_NVML(nvmlDeviceGetHandleByIndex, nvmlReturn_t, unsigned int, 
             nvmlDevice_t*);
   DECL_NVML(nvmlDeviceGetTemperature, nvmlReturn_t, nvmlDevice_t, 
             unsigned int, unsigned int*);
   DECL_NVML(nvmlDeviceGetMemoryInfo, nvmlReturn_t, nvmlDevice_t,
             nvmlMemory_t*);

   void load_exports();
};

#endif // __CTOP_NVML_H__
