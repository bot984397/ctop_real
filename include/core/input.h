#ifndef __CTOP_INPUT_H__
#define __CTOP_INPUT_H__

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
#include <vector>
#include <optional>

struct InputEvent {
   enum class Type {
      Key,
      Special,
      Mouse,
      WindowSize
   };

   enum class SpecialKey {
      None,
      Up,
      Down,
      Left,
      Right,
      Home,
      End,
      PageUp,
      PageDown,
      Delete,
      Insert,
      F1,
      F2,
      F3,
      F4,
      Escape
   };

   struct MouseInfo {
      int x;
      int y;
      bool left_button;
      bool middle_button;
      bool right_button;
      bool drag;
      bool scroll_up;
      bool scroll_down;
   };

   Type type;
   char key;
   SpecialKey special_key;
   MouseInfo mouse;

   struct {
      int rows;
      int columns;
   } window_size;
};

class InputProcessor {
private:
   static constexpr size_t BUFFER_SIZE = 32;
   char m_buffer[BUFFER_SIZE];
   size_t m_buffer_pos;
   size_t m_buffer_size;

   bool read_to_buffer();
   char read_byte();

   std::optional<InputEvent> parse_escape_sequence();

public:
   std::optional<InputEvent> read_event();
};

#endif // __CTOP_INPUT_H__
