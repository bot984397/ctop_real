#ifndef __CTOP_BOX_H__
#define __CTOP_BOX_H__

class IContainer {
private:

protected:

public:
   virtual bool init() noexcept = 0;
   virtual void collect() noexcept = 0;
   virtual void draw() const noexcept = 0;
   virtual void process_key() noexcept = 0;
};

#endif // __CTOP_BOX_H__
