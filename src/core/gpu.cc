#include "../../include/core/gpu.h"

#include <iostream>

GpuAggregator::GpuAggregator() : IResourceAggregator() {
   m_device_count = 0;
}

bool GpuAggregator::init() {
   try {
      m_nvml = NvmlHandler();
   } catch (const std::runtime_error& e) {
      return false;
   }
   
   return m_nvml.get_device_count(&m_device_count) == NVML_SUCCESS;
}

void GpuAggregator::aggregate() {
   std::cout << m_device_count << std::endl;
}

GpuContainer::GpuContainer() : IContainer() {}

bool GpuContainer::init() noexcept {
   return aggregator.init();
}

void GpuContainer::collect() noexcept {
   aggregator.aggregate();
}

void GpuContainer::draw() const noexcept {

}

void GpuContainer::process_key() noexcept {

}
