/**
 * Copyright (c) Romain Desarzens
 * All rights reserved.
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "gtest/gtest.h"
#include "emulator/clock.h"

using namespace std::chrono_literals;
using namespace chip8;

TEST(Memory, callbackPeriodicCallRequired) {
  bool called = false;
  std::chrono::time_point<std::chrono::system_clock> current_time{};
  Clock clock([&current_time]() { return current_time; });
  bool callback_register_success =
      clock.registerCallback([&called]() { called = true; }, 1e6);

  // We fake to have reached the frequency of the callback
  current_time += 1000ns;
  clock.tick();

  EXPECT_EQ(called, true);
  EXPECT_EQ(callback_register_success, true);
}

TEST(Memory, callbackPeriodicCallNonRequired) {
  bool called = false;
  std::chrono::time_point<std::chrono::system_clock> current_time{};
  Clock clock([&current_time]() { return current_time; });
  bool callback_register_success =
      clock.registerCallback([&called]() { called = true; }, 1e6);

  clock.tick();

  EXPECT_EQ(callback_register_success, true);
}

TEST(Memory, TestTwoConsecutiveCallSecondOneNotRequired) {
  bool called = false;
  std::chrono::time_point<std::chrono::system_clock> current_time{};
  Clock clock([&current_time]() { return current_time; });
  clock.registerCallback([&called]() { called = true; }, 1e6);
  current_time += 1000ns;
  clock.tick();
  called = false;

  clock.tick();

  EXPECT_EQ(called, false);
}
