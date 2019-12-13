#include "interpreter/clock.h"

static const double SECOND_TO_NANOSECOND = 1e9;

namespace chip8 {

Clock::Clock(std::function<std::chrono::nanoseconds()> get_current_time_cb)
    : m_get_current_time(get_current_time_cb) {}

bool Clock::registerCallback(std::function<void()> cb, double frequency) {
  if (m_get_current_time) {
    m_callbacks.push_back(
        PeriodicCallback{cb, frequency, m_get_current_time()});
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
  if ((m_get_current_time() - periodic_cb.last_call_timestamp) >=
      std::chrono::nanoseconds(
          static_cast<int64_t>(SECOND_TO_NANOSECOND / periodic_cb.frequency))) {
    return true;
  }

  return false;
}

}  // namespace chip8
