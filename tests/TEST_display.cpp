#include "gtest/gtest.h"
#include "emulator/display.h"

using namespace chip8::display;

TEST(DisplayTest, SetPixelValue) {
    Display<bool> display(64,32);    

    display.setPixel({1,1}, 1);

    EXPECT_EQ(display(1,1), 1);
}

TEST(DisplayTest, SetSpriteValue) {
    Display<bool> display(64,32);    

    display.setPixel({1,1}, 1);

    EXPECT_EQ(display(1,1), 1);
}
