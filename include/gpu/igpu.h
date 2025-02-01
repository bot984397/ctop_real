#ifndef __CTOP_GPU_H__
#define __CTOP_GPU_H__

class IGpuHandler {
private:
   template<typename T>
   static std::unique_ptr<T> tryCreate() {
      try {
         return std::make_unique<T>();
      } catch (...) {
         return nullptr;
      }
   }
public:
   virtual ~IGpuHandler() = default;

   static std::unique_ptr<IGpuHandler> create();

   virtual void init() = 0;
   virtual std:;string get_name() = 0;
   virtual int get_temperature() = 0;
   virtual int get_load() = 0;

protected:
   IGpuHandler();
};

#endif // __CTOP_GPU_H__
