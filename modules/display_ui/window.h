/**
 * Copyright (c) Romain Desarzens
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef MODULES_DISPLAY_WINDOW_H_
#define MODULES_DISPLAY_WINDOW_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <SDL.h>

#include "utilities.h"
#include "window_component.h"

namespace chip8 {

class Window {
 public:
  Window(std::size_t width, std::size_t height, const std::string& label);
  ~Window();
  void setBackgroundColor(Color color);
  void update();
  void attachNewComponent(WindowComponent* component) {
    component->assign_renderer(m_renderer);
    m_components.push_back(component);
  }

 private:
  std::vector<WindowComponent*> m_components;
  SDL_Window* m_window;
  SDL_Renderer* m_renderer;
};

}  // namespace chip8
#endif  // MODULES_DISPLAY_UTILITIES_H_
