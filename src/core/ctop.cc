#include <cstring>
#include <unistd.h>
#include <sys/ioctl.h>

#include "../../include/core/ctop.h"
#include "../../include/core/term.h"
#include "../../include/ui/container.h"

#include "../../include/core/proc.h"
#include "../../include/core/cpu.h"
#include "../../include/core/gpu.h"

SystemInformer* g_monitor;

SystemInformer::SystemInformer() {
   get_term_size();

   init();
   Term::clear_screen_im();
   Term::paint_screen_im(40, 42, 54);

   m_required_width = 120;
   m_required_height = 30;

   m_boxes.push_back(std::make_unique<CpuContainer>());
   m_boxes.push_back(std::make_unique<GpuContainer>());
   m_boxes.push_back(std::make_unique<ProcContainer>());

   m_next_execution = std::chrono::steady_clock::now() + m_interval;
   m_monitor_thread = std::thread(&SystemInformer::monitor_task, this);
   //m_input_thread = std::thread(&SystemInformer::input_task, this);
}

void SystemInformer::get_term_size() {
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   m_real_width = w.ws_col;
   m_real_height = w.ws_row;
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
   //Term::clear_screen_im();
   std::cout << Term::E::r << std::flush;
}

void SystemInformer::aggregate() {
   for (auto& box : m_boxes) {
      box->collect();
   }
}

void print_info() {
}

char getch_raw() {
   char ch;
   read(STDIN_FILENO, &ch, 1);  // Read one character from the terminal
   return ch;
}

void SystemInformer::sigh(int sig) {
   if (sig == 0) {}
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

   auto systemInformer = SystemInformer();
   g_monitor = &systemInformer;
   bool stop_requested = false;

   signal(SIGWINCH, sig_handler); 

   std::ofstream file;
   while(!stop_requested) {
      char input = getch_raw();
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
