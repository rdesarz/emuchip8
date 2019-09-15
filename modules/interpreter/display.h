#ifndef DISPLAY_H
#define DISPLAY_H

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

namespace chip8
{

// Generate a vector of bit representing a sprite 
template<typename SpriteType>
std::vector<SpriteType> makeSprite(uint8_t byte)
{
   std::vector<SpriteType> sprite(8);

   for(std::size_t index=0;index<8;++index)
   {
       sprite[index] =  ((1 << index) & byte) >> index;
   }

   return sprite; 
}

// Store a pixel coordinate to use with the display
struct PixelCoordinate
{
    PixelCoordinate(std::size_t _x, std::size_t _y) : x(_x), y(_y) { }
    std::size_t x = 0;
    std::size_t y = 0;
};


// Store display information
template<typename Pixel>
class Display
{
public:
    Display(std::size_t width, std::size_t height);
    virtual ~Display() = default;

    Pixel operator() (std::size_t x, std::size_t y) const
    {
        return m_pixels(x,y);
    }

    bool setPixel(PixelCoordinate coord, Pixel value);
    bool setSprite(PixelCoordinate coord, std::vector<Pixel> sprite);

private:
    boost::numeric::ublas::matrix<Pixel> m_pixels;
};

template<typename Pixel>
Display<Pixel>::Display(std::size_t width, std::size_t height) : m_pixels(width,height)
{ 
    m_pixels.clear();
}


template<typename Pixel>
bool Display<Pixel>::setPixel(PixelCoordinate coord, Pixel value)
{
    // Crop if pixel is outside of the screen
    coord.x = coord.x % m_pixels.size1();

    // Check if pixel is modified or not
    Pixel old_value = m_pixels(coord.x, coord.y);
    m_pixels(coord.x, coord.y) ^= value;

    return m_pixels(coord.x, coord.y) != old_value;
}

template<typename Pixel>
bool Display<Pixel>::setSprite(PixelCoordinate coord, std::vector<Pixel> sprite)
{
    bool any_pixel_modified = false;
    for(uint8_t i=0;i<8;++i)
    {
        any_pixel_modified |= setPixel({ coord.x+i,coord.y }, sprite[i]); 
    }

    return any_pixel_modified;
}

std::vector<bool> makeSprite(uint8_t byte);

} /// chip8
#endif
