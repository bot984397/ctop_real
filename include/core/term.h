#ifndef __CTOP_TERM_H__
#define __CTOP_TERM_H__

#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <string>

#include "../ui/util.h"

namespace Term {
   namespace Box {
      const std::string CTR = "┐";
      const std::string CBL = "└";
      const std::string TCB = "┴";
      const std::string TCT = "┬";
      const std::string TCL = "├";
      const std::string HOR = "─";
      const std::string CRO = "┼";
      const std::string CBR = "┘";
      const std::string CTL = "┌";
      const std::string VER = "│";
      const std::string TCR = "┤";

      const std::string RTL = "╭";
      const std::string RTR = "╮";
      const std::string RBL = "╰";
      const std::string RBR = "╯";
   }

   namespace E {
      const std::string e = "\x1b[";
      const std::string b = "\x1b[1m";
      const std::string ub = "\x1b[22m";
      const std::string i = "\x1b[3m";
      const std::string ui = "\x1b[23m";
      const std::string u = "\x1b[4m";
      const std::string uu = "\x1b[24m";
      const std::string bl = "\x1b[5m";
      const std::string ubl = "\x1b[25m";
      const std::string s = "\x1b[9m";
      const std::string us = "\x1b[29m";
      const std::string c = "\x1b[?25h";
      const std::string uc = "\x1b[?25l";

      const std::string cs = "\x1b[2J\x1b[H";
      const std::string r = "\x1b[0m";
   }

   namespace C {
      inline std::string fg(int r, int g, int b) {
         return Term::E::e + "38;2;" + std::to_string(r) + ";"
            + std::to_string(g) + ";" + std::to_string(b) + "m";
      }

      inline std::string bg(int r, int g, int b) {
         return Term::E::e + "48;2;" + std::to_string(r) + ";"
            + std::to_string(g) + ";" + std::to_string(b) + "m";
      }
   }

   void enable_raw_mode();
   void disable_raw_mode();

   inline std::string clear_screen() { return E::cs; }
   void clear_screen_im();

   inline std::string paint_screen(int r, int g, int b) { 
      return C::bg(r, g, b) + E::cs; 
   }
   void paint_screen_im(int r, int g, int b);

   void hide_cursor();
   void show_cursor();

   namespace M {
      inline std::string abs(int x, int y) {
         return Term::E::e + std::to_string(y) + ";" + std::to_string(x) + "H";
      }
   }

   void move_cursor_abs(int x, int y);
   void move_cursor_right(int x);
   void move_cursor_left(int x);
   void move_cursor_up(int x);
   void move_cursor_down(int x);

   /*
   std::string draw_box(std::string title, UI_UTIL::Vec2 pos, size_t w, size_t h, 
                        bool rounded, int r, int g, int b);
   */
}

#endif // __CTOP_TERM_H__
