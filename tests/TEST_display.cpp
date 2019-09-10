#include "gtest/gtest.h"
#include "interpreter/display.h"
#include "iostream"

using namespace chip8::display;


class TestDisplayFixture : public ::testing::Test
{
protected:
    TestDisplayFixture() : display(64,32)
    { }

    Display<uint8_t> display;
};

TEST_F(TestDisplayFixture, SetPixelValue) {

    display.setPixel({1,1}, 1);

    EXPECT_EQ(display(1,1), 1);
}

TEST_F(TestDisplayFixture, SetSpriteValue) {

    display.setPixel({1,1}, 1);

    EXPECT_EQ(display(1,1), 1);
}

TEST_F(TestDisplayFixture, TestModifiedPixelFlag) {

    auto modified = display.setPixel({1,1}, 1);

    EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedPixelFlag) {
    display.setPixel({1,1}, 1);

    auto modified = display.setPixel({1,1}, 0);

    EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestModifiedSpriteFlag) {

    auto modified = display.setSprite({1,1}, makeSprite<uint8_t>(0b11111111));
    
    EXPECT_EQ(modified, true);
}

TEST_F(TestDisplayFixture, TestNonModifiedSpriteFlag) {

    auto modified = display.setSprite({1,1}, makeSprite<uint8_t>(0b000000000));
    
    EXPECT_EQ(modified, false);
}

TEST_F(TestDisplayFixture, TestSpriteOutsideOfScreen) {

    display.setSprite({63,1}, makeSprite<uint8_t>(0b11111111));
    
    EXPECT_EQ(display(0,1), 1);
    EXPECT_EQ(display(6,1), 1);
    EXPECT_EQ(display(7,1), 0);
}
