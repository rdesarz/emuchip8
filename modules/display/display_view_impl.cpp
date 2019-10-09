#include "display/display_view_impl.h"

#include <vector>

using namespace chip8::pixel;

namespace chip8
{

void SDLDisplayView::render()
{
    if (getRenderer() == nullptr) { return; }
    
    for (std::size_t x = 0; x < m_model.getWidth();++x)
    {
        for (std::size_t y = 0; y < m_model.getHeight();++y)
        {
            if (m_model.getPixelValue(x,y) == 0)
            {
                Pixel pixel(getRenderer(), Position(x,y), makeBlack(), ScaleFactor(10));
                pixel.render();
            }
            else
            {
                Pixel pixel(getRenderer(), Position(x,y), makeWhite(), ScaleFactor(10));
                pixel.render();
            }
        }
    }
}


}
