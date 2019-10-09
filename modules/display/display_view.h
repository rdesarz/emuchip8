#ifndef DISPLAY_VIEW_H
#define DISPLAY_VIEW_H

namespace chip8 {

class DisplayView {
 public:
  virtual void render() = 0;
};

}  /// chip8
#endif
