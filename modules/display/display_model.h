#ifndef DISPLAY_MODEL_H
#define DISPLAY_MODEL_H

namespace chip8 {

class DisplayModel {
 public:
  virtual void setPixelValue(std::size_t x, std::size_t y, uint8_t value) = 0;
  virtual uint8_t getPixelValue(std::size_t x, std::size_t y) const = 0;
  virtual std::size_t getWidth() const = 0;
  virtual std::size_t getHeight() const = 0;
};

}  /// chip8
#endif
