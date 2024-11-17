#include "Vm.hpp"
#include "../exceptions/VmException.hpp"
#include <fmt/base.h>

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
      this->vmAssert();
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

  fmt::println("{}", a->toString());
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

void Vm::push() {
  OperandFactory of;
  const IOperand *operand = of.createOperand(ip->value.type, ip->value.value);
  stack.push_back(operand);
}

void Vm::pop() {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);
  this->stack.pop_back();
}

void Vm::vmAssert() const {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);

  std::string actual = stack.back()->toString();
	// TODO: I think the instruction pointer has to be incremented here
  std::string expected = ip->value.value;

  if (actual != expected)
    throw VmException(VmException::Type::Assert);
}

void Vm::dumpStack() const {
  for (auto it = stack.rbegin(); it != stack.rend(); it++) {

    // TODO: make vm write to an internal buffer, so that the main function
    // writes what's in the buffer to the stdout This allows the vm to be more
    // testable
    fmt::println("{}", (*it)->toString());
  }
}

Vm::~Vm() {}
