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

#ifndef MODULES_DISPLAY_DISPLAY_VIEW_IMPL_H_
#define MODULES_DISPLAY_DISPLAY_VIEW_IMPL_H_

#include <vector>

#include <SDL.h>
#include <SDL_rect.h>
#include <boost/numeric/ublas/matrix.hpp>

#include <display/display_model.h>
#include <display/display_view.h>
#include <display/pixel.h>
#include <display/window_component.h>

namespace chip8 {

class SDLDisplayView : public DisplayView, public WindowComponent {
 public:
  explicit SDLDisplayView(const DisplayModel* model) : m_model(model) {}
  void render() override;

 private:
  const DisplayModel* m_model;
};

}  // namespace chip8
#endif  // MODULES_DISPLAY_DISPLAY_VIEW_IMPL_H_
