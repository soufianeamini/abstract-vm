#pragma once

#include "../parser/Instruction.hpp"
#include <vector>

class Vm {
private:
  std::vector<Instruction> instructions;
};
