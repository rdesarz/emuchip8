#include "gtest/gtest.h"
#include "interpreter/clock.h"

using namespace std::chrono_literals;
using namespace chip8;

TEST(Memory, callbackPeriodicCallRequired) {
  bool called = false;
  std::chrono::nanoseconds current_time(0ns);
  Clock clock([&current_time](){ return current_time; });
  bool callback_register_success = clock.registerCallback([&called](){ called = true; }, 1e6);
  
  // We fake to have reached the frequency of the callback
  current_time = 1000ns;
  clock.tick();
  
  EXPECT_EQ(called, true);
  EXPECT_EQ(callback_register_success, true);
}

TEST(Memory, callbackPeriodicCallNonRequired) {
  bool called = false;
  std::chrono::nanoseconds current_time(1000ns);
  Clock clock([&current_time](){ return current_time; });
  bool callback_register_success = clock.registerCallback([&called](){ called = true; }, 1e6);
  
  clock.tick();
  
  EXPECT_EQ(callback_register_success, true);
}

TEST(Memory, TestTwoConsecutiveCallSecondOneNotRequired) {
  bool called = false;
  std::chrono::nanoseconds current_time(0ns);
  Clock clock([&current_time](){ return current_time; });
  clock.registerCallback([&called](){ called = true; }, 1e6); 
  current_time = 1000ns;
  clock.tick();
  called = false;
  
  clock.tick();

  EXPECT_EQ(called, false);
}

