#ifndef __CTOP_CPU_H__
#define __CTOP_CPU_H__

#include "../core/aggregator.h"
#include "../ui/container.h"

class CpuAggregator : public IResourceAggregator {
private:

public:
   CpuAggregator();

   bool init() override;
   void aggregate() override;
};

class CpuContainer : public IContainer {
private:
   CpuAggregator aggregator;

public:
   CpuContainer();

   bool init() noexcept override;
   void collect() noexcept override;
   void draw() const noexcept override;
   void process_key() noexcept override;
};

#endif // __CTOP_CPU_H__
