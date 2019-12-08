#include "interpreter/rom_loader.h"

#include <iterator>
#include <algorithm>

namespace chip8 {

void loadProgram(RAM& ram, std::istream& input_stream) {
  std::copy(std::istream_iterator<uint8_t>(input_stream),
            std::istream_iterator<uint8_t>(), ram.begin() + 0x200);
}
}
