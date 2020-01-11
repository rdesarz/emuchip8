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

#ifndef MODULES_INTERPRETER_CLOCK_H_
#define MODULES_INTERPRETER_CLOCK_H_

// std
#include <chrono>
#include <functional>
#include <vector>

namespace chip8 {

struct PeriodicCallback {
  std::function<void()> callback;
  std::chrono::nanoseconds period;
  std::chrono::system_clock::time_point last_call_timestamp;
};

class Clock {
 public:
  explicit Clock(std::function<std::chrono::system_clock::time_point()>
                     get_current_time_cb);
  bool registerCallback(std::function<void()> cb, double frequency);
  void tick();

 private:
  bool needsToBeCalled(const PeriodicCallback& periodic_cb);

 private:
  std::vector<PeriodicCallback> m_callbacks;
  std::function<std::chrono::system_clock::time_point()> m_get_current_time;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CLOCK_H
