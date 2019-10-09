#include "display/pixel.h"

namespace chip8 {
namespace pixel {

void Pixel::render() {
  m_rect.x = m_position.x() * m_scale_factor;
  m_rect.y = m_position.y() * m_scale_factor;
  m_rect.w = m_scale_factor;
  m_rect.h = m_scale_factor;
  SDL_SetRenderDrawColor(m_renderer, m_color.red(), m_color.green(),
                         m_color.blue(), m_color.alpha());
  SDL_RenderFillRect(m_renderer, &m_rect);
}

Color makeBlack() { return Color(0, 0, 0, 255); }

Color makeWhite() { return Color(255, 255, 255, 255); }

}  // namespace pixel
}  // namespace chip8
