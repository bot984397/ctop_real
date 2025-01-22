#ifndef __CTOP_CORE_H__
#define __CTOP_CORE_H__

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <cstring>
#include <fstream>

#include "../ui/box.h"
#include "../../include/core/input.h"

class SystemInformer {
private:
   std::atomic<bool> m_term_too_small{false};

   std::mutex m_mutex;
   std::condition_variable m_cv;
   std::atomic<bool> m_stop_requested{false};

   std::chrono::milliseconds m_interval{100};
   std::chrono::steady_clock::time_point m_next_execution;

   std::thread m_monitor_thread;

   size_t m_term_w;
   size_t m_term_h;

   void test_draw();
   void monitor_task();

   void get_term_size();

   std::vector<std::unique_ptr<IBox>> m_boxes;
public:
   SystemInformer();
   ~SystemInformer();

   void update_interval(std::chrono::milliseconds new_interval) {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_interval = new_interval;
      auto now = std::chrono::steady_clock::now();
      m_next_execution = now + m_interval;
      m_cv.notify_one();
   }

   void sigh(int sig);

   void stop() noexcept;

   bool init();
   void run();

   void aggregate();
   void draw();
   void draw_size_error_screen();
};

static SystemInformer* g_monitor = nullptr;

#endif // __CORE_CTOP_H__
