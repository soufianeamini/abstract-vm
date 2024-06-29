#pragma once

#include "../parser/Instruction.hpp"
#include <stack>
#include <vector>

class Vm {
private:
  std::vector<Instruction> instructions;
  std::stack<Instruction> stack;

  // Instruction Pointer
  std::vector<Instruction>::const_iterator ip;

public:
  Vm();
  void interpret();
  Vm(const std::vector<Instruction> &instructions);
  Vm(const std::vector<Instruction> &&instructions);
  Vm(const Vm &o);
  Vm &operator=(const Vm &o);
  ~Vm();
};
