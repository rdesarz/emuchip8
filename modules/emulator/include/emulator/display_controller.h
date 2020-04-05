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

#ifndef MODULES_DISPLAY_DISPLAY_CONTROLLER_H_
#define MODULES_DISPLAY_DISPLAY_CONTROLLER_H_

// std
#include <memory>
#include <vector>

#include "units.h"

namespace chip8 {

class DisplayModel;
class DisplayView;

/*!
 * Helper function to extract each bit of a byte and store it into an array
 * @param byte byte from which the bits are extracted
 * @return vector where each index is an extracted bit
 */
std::vector<std::uint8_t> byteToSprite(uint8_t byte);

/*!
 * This controller is used to modify the output of the emulator.
 */
class DisplayController {
 public:
  /*!
   * Constructor
   * @param model model of the display, which stores the state of the pixels
   * (MVC pattern)
   * @param view view of the display which outputs a graphical representation of
   * the model (MVC pattern)
   */
  DisplayController(DisplayModel* model, DisplayView* view);

  /*!
   * Update a pixel with a new value with the Chip-8 update mode (XOR)
   * @param col column at which the pixel is located
   * @param row row at which the pixel is located
   * @param value value of the updated pixel
   * @return true if the corresponding was modified (0->1 or 1->0)
   */
  bool setPixel(column_t col, row_t row, uint8_t value);

  /*!
   * Update the display with several sprites. A sprite is a line of eight
   * pixels.
   * @param col column at which the first pixel is located
   * @param row row at which the first pixel is located
   * @param sprite sprite used for the update
   * @return true if any pixels was modified (0->1 or 1->0)
   */
  bool setSprite(column_t col, row_t row, std::vector<uint8_t> sprite);

  /*!
   * Clear the display (all pixels at 0)
   */
  void clear();

 private:
  DisplayModel* m_model;
  DisplayView* m_view;
};

}  // namespace chip8
#endif  // MODULES_DISPLAY_DISPLAY_CONTROLLER_H_
