/** 
 * Copyright (c) Romain Desarzens
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software 
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include "display_ui/window.h"

#include <vector>

namespace chip8 {

Window::Window(std::size_t width, std::size_t height,
               const std::string& label) {
  // Initialize window and renderer
  SDL_Init(SDL_INIT_VIDEO);

  m_window = SDL_CreateWindow(label.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height, 0);

  m_renderer = SDL_CreateRenderer(m_window, -1, 0);

  setBackgroundColor(makeBlack());
}

Window::~Window() { SDL_Quit(); }

void Window::setBackgroundColor(Color color) {
  SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
  SDL_RenderClear(m_renderer);
}

void Window::update() {
  for (auto& component : m_components) {
    component->render();
  }

  SDL_RenderPresent(m_renderer);
}
} // namespace chip8
