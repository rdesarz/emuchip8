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

#include "interpreter/clock.h"

static const double SECOND_TO_NANOSECOND = 1e9;

namespace chip8 {

Clock::Clock(
    std::function<std::chrono::system_clock::time_point()> get_current_time_cb)
    : m_get_current_time(get_current_time_cb) {}

bool Clock::registerCallback(std::function<void()> cb, double frequency) {
  if (m_get_current_time) {
    m_callbacks.push_back(PeriodicCallback{
        cb,
        std::chrono::nanoseconds(
            static_cast<uint64_t>(SECOND_TO_NANOSECOND / frequency)),
        m_get_current_time()});
    return true;
  }

  return false;
}

void Clock::tick() {
  for (auto& callback : m_callbacks) {
    if (needsToBeCalled(callback)) {
      callback.callback();
      callback.last_call_timestamp = m_get_current_time();
    }
  }
}

bool Clock::needsToBeCalled(const PeriodicCallback& periodic_cb) {
  std::chrono::nanoseconds elapsed_time =
      m_get_current_time() - periodic_cb.last_call_timestamp;

  return elapsed_time >= periodic_cb.period;
}

}  // namespace chip8
