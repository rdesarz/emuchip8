#include "emulator/display.h"

using namespace boost::numeric::ublas;

namespace chip8
{
namespace display
{

std::vector<bool> makeSprite(uint8_t byte)
{
   std::vector<bool> bools(8);

   for(uint8_t index=0;index<8;++index)
   {
       bools[index] =  ((1 << index) & byte) >> index;
   }

   return bools; 
}

}
}
