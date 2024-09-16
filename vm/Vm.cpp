#include "Vm.hpp"
#include "../exceptions/VmException.hpp"
#include <iostream>

Vm::Vm() {}
Vm::Vm(const std::vector<Instruction> &instructions)
    : instructions(instructions) {}
Vm::Vm(const std::vector<Instruction> &&instructions) {
  this->instructions = std::move(instructions);
}
Vm::Vm(const Vm &o) : instructions(o.instructions) {}
Vm &Vm::operator=(const Vm &o) {
  if (this == &o)
    return *this;

  this->instructions = o.instructions;

  return *this;
}

void Vm::interpret() {
  ip = instructions.cbegin();
  while (ip != instructions.cend()) {
    switch (ip->command) {
    case TokenType::Push:
      this->push();
      break;
    case TokenType::Pop:
      this->pop();
      break;
    case TokenType::Dump:
      this->dumpStack();
      break;
    case TokenType::Assert:
      this->vm_assert();
      break;
    case TokenType::Add:
      this->add();
      break;
    case TokenType::Sub:
      this->sub();
      break;
    case TokenType::Mul:
      this->mul();
      break;
    case TokenType::Div:
      this->div();
      break;
    case TokenType::Print:
      this->print();
      break;
    case TokenType::Exit:
      return;
    case TokenType::EndOfProgram:
      return;
    default:
      // FIX: Remove this line before pushing
      throw "Unreachable!";
    }
    ip++;
  }

  throw VmException(VmException::Type::NoExitInstruction);
}

void Vm::print() const {
  if (stack.size() < 1)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();

	std::cout << a->toString() << std::endl;
}

void Vm::div() {
  if (stack.size() < 2)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();
  this->stack.pop_back();
  const IOperand *b = this->stack.back();
  this->stack.pop_back();

  if (b->toString() == "0")
    throw VmException(VmException::Type::DivisionByZero);

  const IOperand *result = *b / *a;
  this->stack.push_back(result);
}

void Vm::mul() {
  if (stack.size() < 2)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();
  this->stack.pop_back();
  const IOperand *b = this->stack.back();
  this->stack.pop_back();

  const IOperand *result = *b * *a;
  this->stack.push_back(result);
}

void Vm::sub() {
  if (stack.size() < 2)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();
  this->stack.pop_back();
  const IOperand *b = this->stack.back();
  this->stack.pop_back();

  const IOperand *result = *b - *a;
  this->stack.push_back(result);
}

void Vm::add() {
  if (stack.size() < 2)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();
  this->stack.pop_back();
  const IOperand *b = this->stack.back();
  this->stack.pop_back();

  const IOperand *result = *b + *a;
  this->stack.push_back(result);
}

void Vm::push() { stack.push_back(ip->value); }

void Vm::pop() {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);
  this->stack.pop_back();
}

void Vm::vm_assert() const {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);

  std::string actual = stack.back()->toString();
  std::string expected = ip->value->toString();
  if (actual != expected)
    throw VmException(VmException::Type::Assert);
}

void Vm::dumpStack() const {
  for (auto it = stack.rbegin(); it != stack.rend(); it++) {
		std::cout << "Printing value:" << std::endl;
		std::cout << (*it)->toString() << std::endl;
  }
}

Vm::~Vm() {}
