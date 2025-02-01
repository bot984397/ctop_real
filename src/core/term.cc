#include "../../include/core/term.h"

#include <iostream>
using std::string;

namespace Term {
   struct termios orig_attr;

   void enable_raw_mode() {
      tcgetattr(STDIN_FILENO, &orig_attr);
      atexit(disable_raw_mode);

      struct termios raw = orig_attr;
      raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
      raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
      raw.c_oflag &= ~(OPOST);
      raw.c_cflag |= (CS8);

      tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
      Term::hide_cursor();
   }

   void disable_raw_mode() {
      std::cout << E::r << std::flush;
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_attr);
      Term::show_cursor();
   }

   void hide_cursor() {
      std::cout << E::uc << std::flush;
   }

   void show_cursor() {
      std::cout << E::c << std::flush;
   }

   void clear_screen_im() {
      std::cout << E::cs << std::flush;
   }

   void paint_screen_im(int r, int g, int b) {
      std::cout << C::bg(r, g ,b) << E::cs << std::flush;
   }

   std::string draw_box(std::string title, Vec2 pos, size_t w, size_t h, 
                        bool rounded, int r, int g, int b) {
      std::string out;
      out += C::fg(r, g, b);
      out += M::abs(pos.x, pos.y);
      
      // draw box outline
      if (h == 1) {
         for (size_t i = 0; i < w; i++) { out += Box::HOR; }
      } else {
         out += (rounded ? Box::RTL : Box::CTL);
         for (size_t i = 0; i < w - 2; i++) { out += Box::HOR; }
         out += (rounded ? Box::RTR : Box::CTR) + "\r\n";
         for (size_t i = 0; i < h - 2; i++) {
            out += Box::VER;
            for (size_t j = 0; j < w - 2; j++) {
               out += ' ';
            }
            out += Box::VER + "\r\n";
         }
         out += (rounded ? Box::RBL : Box::CBL);
         for (size_t i = 0; i < w - 2; i++) { out += Box::HOR; }
         out += (rounded ? Box::RBR : Box::CBR);
      }

      // draw title
      if (title.empty()) return out;
      out += M::abs(pos.x + 3, pos.y);
      out += Box::TCR + E::b + C::fg(245, 81, 66) + "\u00B4";
      out += C::fg(255, 255, 255) + title;
      out += E::ub + C::fg(r, g, b) + Box::TCL;

      return out;
   }
}
