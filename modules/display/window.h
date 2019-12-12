#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <vector>
#include <string>
#include <utility>

#include <SDL.h>

#include <display/utilities.h>
#include <display/window_component.h>

namespace chip8 {

class Window {
 public:
  Window(std::size_t width, std::size_t height, const std::string& label);
  ~Window();
  void setBackgroundColor(Color color);
  void update();
  void attachNewComponent(std::shared_ptr<WindowComponent> component) {
    component->assign_renderer(m_renderer);
    m_components.push_back(std::move(component));
  }

 private:
  std::vector<std::shared_ptr<WindowComponent>> m_components;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};

}  /// chip8
#endif
