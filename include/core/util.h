#ifndef __CTOP_UTIL_H__
#define __CTOP_UTIL_H__

#include <deque>

template<typename T, size_t Capacity>
class StaticFiloQueue {
private:
   std::deque<T> m_buffer;
public:
   void push(const T& v) {
      if (m_buffer.size() >= Capacity) {
         m_buffer.pop_front();
      }
      m_buffer.push_back(v);
   }

   void pop() {
      if (!m_buffer.empty()) {
         m_buffer.pop_front();
      }
   }

   T front() const {
      return m_buffer.front();
   }

   bool empty() const {
      return m_buffer.empty();
   }

   bool full() const {
      return m_buffer.size() == Capacity;
   }

   size_t size() const {
      return m_buffer.size();
   }
};

#endif // __CTOP_UTIL_H__
