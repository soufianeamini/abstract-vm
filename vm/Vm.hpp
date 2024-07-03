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
  void dumpStack() const;
  void assert() const;
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
