#ifndef __CTOP_BOX_H__
#define __CTOP_BOX_H__

#include <utility>
#include <string>
#include <functional>
#include <unordered_map>

#include "util.h"
#include "../core/term.h"

using std::string;

class IBox {
private:
   string m_title;
   bool m_active;

   std::unordered_map<char, std::function<void()>> keybinds;
   std::unordered_map<Vec2, std::function<void()>> clickbinds;

protected:
   std::string m_box;
   size_t m_pos; // top left corner
   Vec2 m_size;
   IBox(string title, size_t pos, Vec2 size, bool active)
      : m_title(title), m_pos(pos), m_size(size), m_active(active) {}

public:
   void set_pos(size_t pos) noexcept {
      m_pos = pos;
   }

   size_t get_pos() const noexcept {
      return m_pos;
   }

   void set_width(size_t width) noexcept {
      m_size.x = width;
   }

   size_t get_width() const noexcept {
      return m_size.x;
   }

   void set_height(size_t height) noexcept {
      m_size.y = height;
   }

   size_t get_height() const noexcept {
      return m_size.y;
   }

   void set_active(bool active) noexcept {
      m_active = active;
   }

   bool get_active() const noexcept {
      return m_active;
   }
   
   void set_title(std::string title) noexcept {
      m_title = title;
   }

   const std::string& get_title() const noexcept {
      return m_title;
   }

   size_t area() const noexcept {
      return m_size.x * m_size.y;
   }

   Vec2 size() const noexcept {
      return m_size;
   }

   virtual bool set_keybind(char key, std::function<void()> func) = 0;
   virtual bool set_clickbind(Vec2 pos, std::function<void()> func) = 0;
   virtual void prepare() noexcept = 0;
   virtual void draw() const noexcept = 0;
};

#endif // __CTOP_BOX_H__
