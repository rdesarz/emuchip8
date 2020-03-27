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

#include <fstream>
#include <iostream>
#include <optional>

#include "interpreter/emulator.h"

#include "interpreter/user_input.h"
#include "interpreter/user_input_impl.h"

#include "display/display_controller.h"
#include "display/display_model.h"
#include "display/display_model_impl.h"
#include "display/display_view.h"
#include "display/display_view_impl.h"
#include "display/window.h"

using namespace chip8;

int main(int argc, char** argv) {
  // First program argument is the path to the ROM
  // std::cout.flags ( std::ios::right | std::ios::hex | std::ios::showbase );
  std::ifstream rom_file;
  //if (argc > 1) {
  rom_file.open("/home/lenovo/Projects/Chip8/chip8_emulator/tests/test.ch8",
                std::ios_base::out | std::ios_base::binary);

  if(!rom_file)
  {
    std::cout << "Cannot open file";
    return 1;
  }
  //} else {
  // std::cout << "No ROM file specified"
  //<< "\n";
  // return -1;
  //}

  // Initialize input controller
  SDLInputToKeyMap key_to_map;
  SDLKeyboardUserInputController keyboard_controller(key_to_map);

  // Initialize display
  std::unique_ptr<DisplayModel> display_model(new DisplayModelImpl());
  std::unique_ptr<SDLDisplayView> display_view(
      new SDLDisplayView(display_model.get()));
  std::unique_ptr<DisplayController> display_controller(
      new DisplayController(display_model.get(), display_view.get()));

  // Add the display element to the window
  Window main_window(640, 320, "Chip8 emulator");
  main_window.attachNewComponent(display_view.get());

  // Initialize emulator
  Emulator emulator(rom_file, std::move(display_controller),
                    &keyboard_controller);

  // main loop
  bool quit = false;
  SDL_Event event;
  while (!quit) {
    if (SDL_PollEvent(&event) != 0) {
      // Process keyboard event
      if (keyboard_controller.processEvent(event)) continue;

      switch (event.type) {
        case SDL_QUIT:
          quit = true;
          break;
      }
    }

    emulator.update();

    main_window.update();

    SDL_Delay(20);
  }

  return 0;
}
