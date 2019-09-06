#ifndef DISPLAY_H
#define DISPLAY_H

#include <boost/numeric/ublas/matrix.hpp>
#include <vector>

namespace chip8
{
namespace display
{

struct PixelCoordinate
{
    PixelCoordinate(uint32_t _x, uint32_t _y) : x(_x), y(_y) { }
    uint32_t x = 0;
    uint32_t y = 0;
};


template<typename Pixel>
class Display
{
public:
    Display(uint32_t w, uint32_t l); 
    virtual ~Display() = default;

    uint8_t operator() (uint32_t x, uint32_t y) const
    {
        return m_screen(x,y);
    }

    void setPixel(PixelCoordinate coord, Pixel value);
    void setSprite(PixelCoordinate coord, std::vector<Pixel> sprite);

private: 
    boost::numeric::ublas::matrix<Pixel> m_screen;
};

template<typename Pixel>
Display<Pixel>::Display(uint32_t w, uint32_t l) : m_screen(boost::numeric::ublas::matrix<Pixel>(w,l))
{ }


template<typename Pixel>
void Display<Pixel>::setPixel(PixelCoordinate coord, Pixel value)
{
    m_screen(coord.x, coord.y) ^= value;
}

template<typename Pixel>
void Display<Pixel>::setSprite(PixelCoordinate coord, std::vector<Pixel> sprite)
{
    for(uint8_t i=0;i<8;++i)
    {
       m_screen(coord.x,coord.y+i) ^= sprite[i]; 
    }
}

std::vector<bool> makeSprite(uint8_t byte);

} /// display
} /// chip8
#endif
