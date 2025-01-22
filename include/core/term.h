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
      const std::string b = "1m";
      const std::string ub = "22m";
      const std::string i = "3m";
      const std::string ui = "23m";
      const std::string u = "4m";
      const std::string uu = "24m";
      const std::string bl = "5m";
      const std::string ubl = "25m";
      const std::string s = "9m";
      const std::string us = "29m";
      const std::string c = "?25h";
      const std::string uc = "?25l";
   }

   void enable_raw_mode();
   void disable_raw_mode();

   void hide_cursor();
   void show_cursor();

   namespace M {
      inline std::string abs(int x, int y) {
         return Term::E::e + std::to_string(y) + ";" + std::to_string(x) + "H";
      }
   }

   namespace C {
      inline std::string fg(int col) {
         return Term::E::e + "38;5;" + std::to_string(col) + "m";
      }
   }

   void move_cursor_abs(int x, int y);
   void move_cursor_right(int x);
   void move_cursor_left(int x);
   void move_cursor_up(int x);
   void move_cursor_down(int x);

   std::string draw_box(Vec2 pos, size_t w, size_t h, bool rounded, int col);
}

#endif // __CTOP_TERM_H__
