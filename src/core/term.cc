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
   }

   void disable_raw_mode() {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_attr);
   }

   std::string draw_box(Vec2 pos, size_t w, size_t h, bool rounded, int col) {
      std::string out;
      out += Term::C::fg(col);
      out += M::abs(pos.x, pos.y);
      
      if (h == 1) {
         out += Box::TCL;
         for (size_t i = 0; i < w - 2; i++) { out += Box::HOR; }
         out += Box::TCR;
         return out;
      }

      out += (rounded ? Box::CTL : Box::RTL);
      for (size_t i = 0; i < w - 2; i++) { out += Box::HOR; }
      out += (rounded ? Box::CTR : Box::RTR) + "\r\n";
      for (size_t i = 0; i < h - 2; i++) {
         out += Box::VER;
         for (size_t j = 0; j < w - 2; j++) {
            out += ' ';
         }
         out += Box::VER + "\r\n";
      }
      out += (rounded ? Box::CBL : Box::RBL);
      for (size_t i = 0; i < w - 2; i++) { out += Box::HOR; }
      out += (rounded ? Box::CBR : Box::RBR);
      
      return out;
   }

   void add_label(string& box, bool top, bool left, size_t off, string s) {

   }
}
