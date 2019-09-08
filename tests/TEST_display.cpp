#include "gtest/gtest.h"
#include "interpreter/display.h"
#include "iostream"

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

TEST(DisplayTest, TestModifiedPixelFlag) {
    Display<bool> display(64,32);    

    auto modified = display.setPixel({1,1}, 1);

    EXPECT_EQ(modified, true);
}

TEST(DisplayTest, TestNonModifiedPixelFlag) {
    Display<bool> display(64,32);    
    display.setPixel({1,1}, 1);

    auto modified = display.setPixel({1,1}, 0);

    EXPECT_EQ(modified, false);
}

TEST(DisplayTest, TestModifiedPixelWhenModifyingSpriteFlag) {
    Display<bool> display(64,32);    
    display.setPixel({1,1}, 1);
    display.setPixel({1,2}, 1);

    auto modified = display.setSprite({1,1}, makeSprite(0b11111111));
    
    EXPECT_EQ(modified, true);
}

TEST(DisplayTest, TestNonModifiedPixelWhenModifyingSpriteFlag) {
    Display<bool> display(64,32);    

    auto modified = display.setSprite({1,1}, makeSprite(0b000000000));
    
    EXPECT_EQ(modified, false);
}
