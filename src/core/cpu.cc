#include "../../include/core/cpu.h"

#include <iostream>

CpuAggregator::CpuAggregator() : IResourceAggregator() {}

bool CpuAggregator::init() {
   return true;
}

void CpuAggregator::aggregate() {

}

CpuContainer::CpuContainer() : IContainer() {}

bool CpuContainer::init() noexcept {
   return aggregator.init();
}

void CpuContainer::collect() noexcept {
   aggregator.aggregate();
}

void CpuContainer::draw() const noexcept {

}

void CpuContainer::process_key() noexcept {

}
