#ifndef ROM_LOADER_H
#define ROM_LOADER_H

#include <cstdint>
#include <iostream>
#include <vector>

#include "interpreter/memory.h"

namespace chip8 {

void loadProgram(RAM& buffer, std::istream& input_stream);

}  /// chip8
#endif
