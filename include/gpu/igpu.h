#ifndef __CTOP_GPU_H__
#define __CTOP_GPU_H__

#include <memory>
#include <string>
#include <vector>

class IGpuHandler {
private:
   template<typename T>
   static std::unique_ptr<T> try_create() {
      try {
         return std::make_unique<T>();
      } catch (...) {
         return nullptr;
      }
   }
public:
   virtual ~IGpuHandler() = default;

   static std::vector<std::unique_ptr<IGpuHandler>> create_all();

   virtual bool init() = 0;
   virtual std::string get_name() = 0;
   virtual int get_temperature() = 0;
   virtual int get_load() = 0;

protected:
   IGpuHandler();
};

#endif // __CTOP_GPU_H__
