#include <dlfcn.h>

#include "../../include/gpu/nvml.h"

NvmlHandler::NvmlHandler() : IGpuHandler() {
   m_handle = dlopen("libnvidia-ml.so.1", RTLD_LAZY);
   if (!m_handle) {
      throw std::runtime_error("Failed to load NVML library");
   }
   
   load_exports();

   if (nvmlInit() != NVML_SUCCESS) {
      throw std::runtime_error("Failed to initialize NVML");
   }
}

NvmlHandler::~NvmlHandler() {
   if (m_handle) {
      nvmlShutdown();
      dlclose(m_handle);
   }
}

void NvmlHandler::load_exports() {
   LOAD_NVML(nvmlInit);
   LOAD_NVML(nvmlShutdown);
   LOAD_NVML(nvmlDeviceGetCount);
   LOAD_NVML(nvmlDeviceGetHandleByIndex);
   LOAD_NVML(nvmlDeviceGetTemperature);
   LOAD_NVML(nvmlDeviceGetMemoryInfo);
}

bool NvmlHandler::init() {
   return true;
}

std::string NvmlHandler::get_name() {
   return "";
}

int NvmlHandler::get_temperature() {
   return 0;
}

int NvmlHandler::get_load() {
   return 0;
}
