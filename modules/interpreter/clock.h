#ifndef MODULES_INTERPRETER_CHIP_CLOCK_H
#define MODULES_INTERPRETER_CHIP_CLOCK_H

// std
#include <chrono>
#include <functional>
#include <vector>

namespace chip8 {

struct PeriodicCallback {
  std::function<void()> callback;
  double frequency;
  std::chrono::nanoseconds last_call_timestamp;
};

class Clock {
 public:
  explicit Clock(std::function<std::chrono::nanoseconds()> get_current_time_cb);
  bool registerCallback(std::function<void()> cb, double frequency);
  void tick();

 private:
  bool needsToBeCalled(const PeriodicCallback& periodic_cb);

 private:
  std::vector<PeriodicCallback> m_callbacks;
  std::function<std::chrono::nanoseconds()> m_get_current_time;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_CHIP_CLOCK_H
