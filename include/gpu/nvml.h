#ifndef __CTOP_NVML_H__
#define __CTOP_NVML_H__

class NvmlHandler : public IGpuHandler {
private:

public:
   NvmlHandler();

   bool init() override;
};

#endif // __CTOP_NVML_H__
