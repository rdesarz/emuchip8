#ifndef DISPLAY_CONTROLLER_H
#define DISPLAY_CONTROLLER_H

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>
#include "display/display_model.h"
#include "display/display_view.h"

namespace chip8 {

// Generate a vector of bit representing a sprite
template <typename SpriteType>
std::vector<SpriteType> makeSprite(uint8_t byte) {
  std::vector<SpriteType> sprite(8);

  for (std::size_t index = 0; index < 8; ++index) {
    sprite[index] = ((1 << index) & byte) >> index;
  }

  return sprite;
}

class DisplayController {
 public:
  DisplayController(DisplayModel& model, std::shared_ptr<DisplayView> view);
  DisplayController(const DisplayController&) = delete;
  DisplayController(DisplayController&&) = delete;
  DisplayController& operator=(const DisplayController&) = delete;
  DisplayController& operator=(DisplayController&&) = delete;

  // Set a pixel value following the logic of the chip 8 emulator
  bool setPixel(std::size_t x, std::size_t y, uint8_t value);
  // Set a sprite value following the logic of the chip 8 emulator
  bool setSprite(std::size_t x, std::size_t y, std::vector<uint8_t> sprite);

 private:
  DisplayModel& m_model;
  std::shared_ptr<DisplayView> m_view;
};

}  /// chip8
#endif
