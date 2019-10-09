#ifndef WINDOW_COMPONENT_H
#define WINDOW_COMPONENT_H

#include <memory>
#include <vector>

#include <SDL.h>

namespace chip8 {

class WindowComponent {
 public:
  virtual void render() = 0;

  void assign_renderer(SDL_Renderer* renderer) { m_renderer = renderer; }

  SDL_Renderer* getRenderer() { return m_renderer; }

 private:
  SDL_Renderer* m_renderer;
};

}  /// chip8
#endif
