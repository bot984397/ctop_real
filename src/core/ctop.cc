#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../../include/core/ctop.h"
#include "../../include/core/term.h"
#include "../../include/ui/box.h"
#include "../../include/core/cpu.h"
#include "../../include/core/mem.h"
#include "../../include/core/sys.h"

/*
SystemInformer::SystemInformer() {
   m_boxes.push_back(std::make_unique<CpuBox>(0, Vec2(1,1), true));
   m_boxes.push_back(std::make_unique<MemBox>(0, Vec2(1,1), true));
}
*/

void clear_screen() {
   const char* clear = "\033[2J\033[H";
   write(STDOUT_FILENO, clear, strlen(clear));
}

SystemInformer::SystemInformer() {
   get_term_size();

   init();
   clear_screen();

   m_boxes.push_back(std::make_unique<SysBox>(true, Vec2(m_term_w, m_term_h)));

   m_next_execution = std::chrono::steady_clock::now() + m_interval;
   m_monitor_thread = std::thread(&SystemInformer::monitor_task, this);
   //m_input_thread = std::thread(&SystemInformer::input_task, this);
}

void SystemInformer::get_term_size() {
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   m_term_w = w.ws_col;
   m_term_h = w.ws_row;
}

SystemInformer::~SystemInformer() {

}

bool SystemInformer::init() {
   Term::enable_raw_mode();
   std::cout << "\033[?25l";
   std::cout.flush();

   return true;
}

void SystemInformer::monitor_task() {
   while (!m_stop_requested) {
      auto now = std::chrono::steady_clock::now();
      if (m_next_execution <= now) {
         aggregate();
         draw();
         m_next_execution = now + m_interval;
      }

      std::unique_lock<std::mutex> lock(m_mutex);
      m_cv.wait_until(lock, m_next_execution, [this] {
         return m_stop_requested
         || std::chrono::steady_clock::now() >= m_next_execution;
      });
   }
}

void SystemInformer::stop() noexcept {
   m_stop_requested = true;
   m_cv.notify_all();
   if (m_monitor_thread.joinable()) {
      m_monitor_thread.join();
   }
}

void SystemInformer::aggregate() {
   for (auto& box : m_boxes) {
      //box->aggregate();
   }
}

void SystemInformer::draw() {
   clear_screen();
   if (m_term_w < 30 || m_term_h < 20) {
      draw_size_error_screen();
      return;
   }

   for (auto& box : m_boxes) {
      box->prepare();
      box->draw();
   }

}

void SystemInformer::draw_size_error_screen() {
   clear_screen();
   Term::M::abs(0, 0);
   std::cout << "width: " << m_term_w << " height: " << m_term_h << std::flush;
}

void print_info() {
}

char getch_raw() {
   char ch;
   read(STDIN_FILENO, &ch, 1);  // Read one character from the terminal
   return ch;
}

void SystemInformer::sigh(int sig) {
   get_term_size();
   draw();
}

void sig_handler(int signal) {
   g_monitor->sigh(signal);
}

int main(int argc, char* argv[]) {
   if (argc == 2 && strncmp(argv[1], "info", 5) == 0) {
      print_info();
      return 1;
   }

   SystemInformer systemInformer;
   g_monitor = &systemInformer;
   bool stop_requested = false;

   signal(SIGWINCH, sig_handler); 

   std::ofstream file;
   while(!stop_requested) {
      char input = getch_raw();
      std::cout << input << std::endl;
      switch (input) {
         case '1':
            systemInformer.update_interval(std::chrono::milliseconds(100));
            break;
         case '2':
            systemInformer.update_interval(std::chrono::milliseconds(200));
            break;
         case '3':
            systemInformer.update_interval(std::chrono::milliseconds(300));
            break;
         case '4':
            systemInformer.update_interval(std::chrono::milliseconds(400));
            break;
         case '5':
            systemInformer.update_interval(std::chrono::milliseconds(500));
            break;
         case '0':
            systemInformer.update_interval(std::chrono::milliseconds(10000000));
            break;
         case 'q':
            systemInformer.stop();
            stop_requested = true;
            break;
         default:
            break;
      }
   }
}
