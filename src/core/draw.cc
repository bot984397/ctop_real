#include "../../include/core/ctop.h"
#include "../../include/core/term.h"

void SystemInformer::draw() {
   std::cout << Term::E::cs << std::flush;
   
   if (m_real_width < m_required_width || m_real_height < m_required_height) {
      draw_size_error_screen();
      return;
   }

   // adjust box sizes / positions according to layout & terminal size

   for (auto& box : m_boxes) {
      box->draw();
   }
}

void SystemInformer::draw_size_error_screen() {
   static constexpr const char *header 
      = "Terminal is too small for the current layout";
   static constexpr const char *l1 = "Current size: ";
   static constexpr const char *l2 = "Required size: ";

   static constexpr size_t header_len = strlen(header);
   static constexpr size_t l1_len = strlen(l1);
   static constexpr size_t l2_len = strlen(l2);

   std::string err_screen;
   err_screen += Term::clear_screen();

   size_t start_y = (m_real_height / 2) - 2;
   
   std::string chxw = std::to_string(m_real_width) + "x" 
      + std::to_string(m_real_height);
   std::string rhxw = std::to_string(m_required_width) + "x"
      + std::to_string(m_required_height);

   err_screen += Term::M::abs((m_real_width / 2) - header_len / 2,
                              start_y);
   err_screen += Term::C::fg(252, 3, 107) + header;
   
   err_screen += Term::M::abs((m_real_width / 2) - 
         ((l1_len + chxw.length()) / 2), start_y + 2);
   err_screen += Term::C::fg(255, 255, 255) + l1 + chxw;

   err_screen += Term::M::abs((m_real_width / 2) - 
         ((l2_len + rhxw.length()) / 2), start_y + 3);
   err_screen += Term::C::fg(36, 252, 3) + l2 + rhxw;

   std::cout << err_screen << std::flush;
}
