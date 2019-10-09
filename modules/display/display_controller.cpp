#include "display/display_controller.h"

namespace chip8
{

DisplayController::DisplayController(DisplayModel& model, std::shared_ptr<DisplayView> view) : m_model(model), m_view(view) { }

bool DisplayController::setPixel(std::size_t x, std::size_t y, uint8_t value)
{
    // Crop if pixel is outside of the screen
    x = x % m_model.getWidth();

    // Check if pixel is modified or not
    uint8_t old_value = m_model.getPixelValue(x, y);
    m_model.setPixelValue(x, y, old_value ^ value);

    return m_model.getPixelValue(x, y) != old_value;
}

bool DisplayController::setSprite(std::size_t x, std::size_t y, std::vector<uint8_t> sprite)
{
    bool any_pixel_modified = false;
    for(uint8_t i=0;i<8;++i)
    {
        any_pixel_modified |= setPixel(x+i, y, sprite[i]); 
    }

    return any_pixel_modified;
}

}
