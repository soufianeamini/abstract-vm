#pragma once

#include "../parser/Instruction.hpp"
#include <deque>
#include <vector>

class Vm {
private:
  std::vector<Instruction> instructions;
  std::deque<const IOperand *> stack;

  // Instruction Pointer
  std::vector<Instruction>::const_iterator ip;

public:
  void interpret();
  void dumpStack();
  void assert(const std::string &actual, const std::string &expected);

  Vm();
  Vm(const std::vector<Instruction> &instructions);
  Vm(const std::vector<Instruction> &&instructions);
  Vm(const Vm &o);
  Vm &operator=(const Vm &o);
  ~Vm();
};
