#include "../../include/core/input.h"

#include <iostream>
#include <fstream>

/*
bool InputProcessor::read_to_buffer() {
   if (m_buffer_pos < m_buffer_size) {
      return true;
   }
   m_buffer_pos = 0;
   m_buffer_size = read(STDIN_FILENO, m_buffer, BUFFER_SIZE);
   return m_buffer_size > 0;
}

char InputProcessor::read_byte() {
   if (read_to_buffer()) {
      return m_buffer[m_buffer_pos++];
   }
   return '\0';
}

std::optional<InputEvent> InputProcessor::parse_escape_sequence() {
   struct timespec ts = {0, 100000000};
   nanosleep(&ts, nullptr);

   if (!read_to_buffer()) {
      return InputEvent{InputEvent::Type::Special,
                        '\0',
                        InputEvent::SpecialKey::Escape};
   }

   if (m_buffer_pos < m_buffer_size && m_buffer[m_buffer_pos] == '[') {
      m_buffer_pos++;
      if (m_buffer_pos >= m_buffer_size && !read_to_buffer()) {
         return std::nullopt;
      }

      char next = m_buffer[m_buffer_pos++];
      if (next == 'M' || next == '<') {
         InputEvent event{InputEvent::Type::Mouse};
         if (m_buffer_pos + 2 >= m_buffer_size && !read_to_buffer()) {
            return std::nullopt;
         }

         unsigned char b = m_buffer[m_buffer_pos++];
         unsigned char x = m_buffer[m_buffer_pos++];
         unsigned char y = m_buffer[m_buffer_pos++];

         event.mouse.left_button = (b & 0x20) != 0;
         event.mouse.middle_button = (b & 0x21) != 0;
         event.mouse.right_button = (b & 0x22) != 0;
         event.mouse.drag = (b & 0x40) != 0;
         event.mouse.x = x - 32;
         event.mouse.y = y - 32;
         return event;
      }

      switch(next) {
         case 'A': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::Up};
         case 'B': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::Down};
         case 'C': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::Right};
         case 'D': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::Left};
         case 'H': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::Home};
         case 'F': return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::End};
         case '5': 
            if (read_byte() == '~') {
               return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::PageUp};
            }
            break;
         case '6':
            if (read_byte() == '~') {
               return InputEvent{InputEvent::Type::Special, '\0', InputEvent::SpecialKey::PageDown};
            }
            break;
      }
   }
   return std::nullopt;
}

std::optional<InputEvent> InputProcessor::read_event() {
   if (!read_to_buffer()) {
      return std::nullopt;
   }
   char c = m_buffer[m_buffer_pos++];
   std::ofstream file;
   file.open("debug.log");
   file << c << std::endl;
   file.close();
   if (c == '\033') {
      return parse_escape_sequence();
   }

   return InputEvent{InputEvent::Type::Key, c};
}
*/
