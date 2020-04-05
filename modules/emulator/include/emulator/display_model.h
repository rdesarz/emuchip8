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

#ifndef MODULES_DISPLAY_DISPLAY_MODEL_H_
#define MODULES_DISPLAY_DISPLAY_MODEL_H_

#include "units.h"

namespace chip8 {

/*!
 * Interface for the model of the Chip-8 display (MVC pattern)
 */
class DisplayModel {
 public:
  /*!
   * Set the value of the pixel at coordinates {col, row}
   * @param col column at which the pixel is located
   * @param row row at which the pixel is located
   * @param value value of the new pixel
   */
  virtual void setPixelValue(column_t col, row_t row, uint8_t value) = 0;

  /*!
   * Get the value of the pixel at coordinates {col, row}
   * @param col column at which the pixel is located
   * @param row row at which the pixel is located
   * @return value of the pixel
   */
  virtual uint8_t getPixelValue(column_t col, row_t row) const = 0;

  /*!
   * Set all the pixels value at 0
   */
  virtual void clear() = 0;

  /*!
   *
   * @return Width of the display
   */
  virtual std::size_t getWidth() const = 0;

  /*!
   *
   * @return Height of the display
   */
  virtual std::size_t getHeight() const = 0;
};

}  // namespace chip8
#endif  // MODULES_DISPLAY_DISPLAY_MODEL_H_
