#include "display/display_model_impl.h"

namespace chip8
{

DisplayModelImpl::DisplayModelImpl(std::size_t width, std::size_t height) : m_pixels(width,height)
{ 
    m_pixels.clear();
}

}
