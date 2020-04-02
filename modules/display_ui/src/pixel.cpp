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

#include "display_ui/pixel.h"

namespace chip8 {
namespace pixel {

void Pixel::render() {
  m_rect.x = m_position.col() * m_scale_factor;
  m_rect.y = m_position.row() * m_scale_factor;
  m_rect.w = m_scale_factor;
  m_rect.h = m_scale_factor;
  SDL_SetRenderDrawColor(m_renderer, m_color.red(), m_color.green(),
                         m_color.blue(), m_color.alpha());
  SDL_RenderFillRect(m_renderer, &m_rect);
}

Color makeBlack() { return Color(0, 0, 0, 255); }

Color makeWhite() { return Color(255, 255, 255, 255); }

}  // namespace pixel
}  // namespace chip8
