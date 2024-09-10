#pragma once

#include "../parser/Instruction.hpp"
#include <deque>
#include <vector>

class Vm {
private:
  // TODO: replace Instruction with a struct containing a string and the type,
  // so that later on whenever the Vm's stack is empty, the Operand Factory's
  // memory gets freed
  std::vector<Instruction> instructions;
  std::deque<const IOperand *> stack;

  // Instruction Pointer
  std::vector<Instruction>::const_iterator ip;

public:
  void interpret();
  void dumpStack() const;
  void vm_assert() const;
  void push();
  void pop();
  void add();
  void sub();
  void mul();
  void div();
  void print() const;

  Vm();
  Vm(const std::vector<Instruction> &instructions);
  Vm(const std::vector<Instruction> &&instructions);
  Vm(const Vm &o);
  Vm &operator=(const Vm &o);
  ~Vm();
};
