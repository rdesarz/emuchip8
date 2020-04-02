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

#include "rom_loader.h"

#include <algorithm>
#include <iterator>

namespace chip8 {

bool loadProgramFromStream(RAM& ram, std::istream& input_stream) {
  if (input_stream) {
    // Get length of file:
    input_stream.seekg (0, std::istream::end);
    int length = input_stream.tellg();
    input_stream.seekg (0, std::istream::beg);

    std::cout << length;

    char * buffer = new char [length];
    input_stream.read (buffer,length);

    // TODO: move memory to avoid huge copy
    std::copy(buffer, buffer+length, ram.begin() + 0x200);

    delete[] buffer;

    return true;
  }

  return false;
}
}  // namespace chip8
