#ifndef __CTOP_GPU_H__
#define __CTOP_GPU_H__

#include <dlfcn.h>
#include <stdexcept>

#include "../core/aggregator.h"
#include "../ui/container.h"

typedef void *nvmlDevice_t;
typedef struct {
   unsigned long long total;
   unsigned long long free;
   unsigned long long used;
} nvmlMemory_t;

typedef enum {
   NVML_SUCCESS                     = 0,
   NVML_ERROR_UNINITIALIZED         = 1,
   NVML_ERROR_INVALID_ARGUMENT      = 2,
   NVML_ERROR_NOT_SUPPORTED         = 3,
   NVML_ERROR_NO_PERMISSION         = 4,
   NVML_ERROR_ALREADY_INITIALIZED   = 5,
   NVML_ERROR_UNKNOWN               = 999
} nvmlReturn_t;

#define DECL_NVML_EXPORT(fn, ret, ...) \
   typedef ret (*fn##_t)(__VA_ARGS__); \
   fn##_t fn

#define LOAD_NVML_EXPORT(fn) \
   fn = (fn##_t)dlsym(m_handle, #fn); \
   if (!fn) { \
      return false; \
   }

class NvmlHandler {
private:
   void *m_handle;

   DECL_NVML_EXPORT(nvmlInit, nvmlReturn_t, void);
   DECL_NVML_EXPORT(nvmlShutdown, nvmlReturn_t, void);
   DECL_NVML_EXPORT(nvmlDeviceGetCount, nvmlReturn_t, unsigned int*);
   DECL_NVML_EXPORT(nvmlDeviceGetHandleByIndex, nvmlReturn_t, unsigned int, nvmlDevice_t*);
   DECL_NVML_EXPORT(nvmlDeviceGetTemperature, nvmlReturn_t, nvmlDevice_t, unsigned int, unsigned int*);
   DECL_NVML_EXPORT(nvmlDeviceGetMemoryInfo, nvmlReturn_t, nvmlDevice_t, nvmlMemory_t*);

   bool loadExports() {
      LOAD_NVML_EXPORT(nvmlInit);
      LOAD_NVML_EXPORT(nvmlShutdown);
      LOAD_NVML_EXPORT(nvmlDeviceGetCount);
      LOAD_NVML_EXPORT(nvmlDeviceGetHandleByIndex);
      LOAD_NVML_EXPORT(nvmlDeviceGetTemperature);
      LOAD_NVML_EXPORT(nvmlDeviceGetMemoryInfo);
      return true;
   }

public:
   NvmlHandler() : m_handle(nullptr) {
      m_handle = dlopen("libnvidia-ml.so.1", RTLD_LAZY);
      if (!m_handle) {
         throw std::runtime_error("Failed to load NVML library");
      }

      if (!loadExports()) {
         throw std::runtime_error("Failed to load NVML exports");
      }

      if (nvmlInit() != NVML_SUCCESS) {
         throw std::runtime_error("Failed to initialize NVML");
      }
   }

   ~NvmlHandler() {
      if (m_handle) {
         nvmlShutdown();
         dlclose(m_handle);
      }
   }

   nvmlReturn_t get_device_count(unsigned int *count) {
      return nvmlDeviceGetCount(count);
   }
};

class GpuAggregator : public IResourceAggregator {
private:
   NvmlHandler m_nvml;

   unsigned int m_device_count;

public:
   GpuAggregator();

   bool init() override;
   void aggregate() override;
};

class GpuContainer : public IContainer {
private:
   GpuAggregator aggregator;

public:
   GpuContainer();

   bool init() noexcept override;
   void collect() noexcept override;
   void draw() const noexcept override;
   void process_key() noexcept override;
};

#endif // __CTOP_GPU_H__
