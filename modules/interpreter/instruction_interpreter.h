#ifndef MODULES_INTERPRETER_INSTRUCTION_INTERPRETER_H_
#define MODULES_INTERPRETER_INSTRUCTION_INTERPRETER_H_

#include "interpreter/control_unit.h"

namespace chip8 {

class InstructionInterpreter {
 public:
  explicit InstructionInterpreter(ControlUnit* ctrl_unit);
  void interpret(uint16_t instruction);

 private:
  ControlUnit* m_ctrl_unit;
};

}  // namespace chip8
#endif  // MODULES_INTERPRETER_INSTRUCTION_INTERPRETER_H_