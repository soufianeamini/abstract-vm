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

  // NOTE: The stack is only allowed to contain pointers to IOperand
  std::deque<const IOperand *> stack;

  // Instruction Pointer
  std::vector<Instruction>::const_iterator ip;
  std::string output;

  // Buffers output to a string before being used in the main function
  void writeOutput(std::string out);

  // Instructions
  void dumpStack();
  void vmAssert() const;
  void push();
  void pop();
  void add();
  void sub();
  void mul();
  void div();
  void print();

public:
  void interpret();
	std::string getOutput();

  Vm();
  Vm(const std::vector<Instruction> &instructions);
  Vm(const std::vector<Instruction> &&instructions);
  Vm(const Vm &o);
  Vm &operator=(const Vm &o);
  ~Vm();
};
