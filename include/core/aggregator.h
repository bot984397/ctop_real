#ifndef __CTOP_AGGREGATOR_H__
#define __CTOP_AGGREGATOR_H__

class IResourceAggregator {
public:
   virtual ~IResourceAggregator() = default;

   virtual bool init() = 0;
   virtual void aggregate() = 0;
protected:
   IResourceAggregator();
};

#endif // __CTOP_AGGREGATOR_H__
