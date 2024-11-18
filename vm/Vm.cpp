#include "Vm.hpp"
#include "../exceptions/VmException.hpp"
#include <fmt/base.h>
#include <fmt/format.h>

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

// TODO: move this function into the utils namespace
static std::string trimZeroes(std::string value) {
  size_t i = value.length() - 1;
  bool hasDot = value.find('.') != value.npos;

  if (!hasDot)
    return value;

  for (; i >= 0; i--) {
    if (value[i] != '0')
      break;
  }

  std::string trimmedValue = value.substr(0, i + 1);
  return trimmedValue;
}

void Vm::writeOutput(std::string out) { this->output += out; }

void Vm::print() {
  if (stack.size() < 1)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();

  this->writeOutput(trimZeroes(a->toString()) + "\n");
}

void Vm::div() {
  if (stack.size() < 2)
    throw VmException(VmException::Type::TooFewStackValues);
  const IOperand *a = this->stack.back();
  this->stack.pop_back();
  const IOperand *b = this->stack.back();
  this->stack.pop_back();

  if (b->toString() == "0") {
    delete a;
    delete b;
    throw VmException(VmException::Type::DivisionByZero);
  }

  const IOperand *result = *b / *a;
  delete a;
  delete b;
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
  delete a;
  delete b;
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
  delete a;
  delete b;
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
  delete a;
  delete b;
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
  delete this->stack.back();
  this->stack.pop_back();
}

void Vm::vmAssert() const {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);

  // TODO: Use operator == from IOperand instead of comparing strings
  std::string actual = stack.back()->toString();
  std::string expected = ip->value.value;

  if (actual != expected)
    throw VmException(VmException::Type::Assert);
}

void Vm::dumpStack() {
  for (auto it = stack.rbegin(); it != stack.rend(); it++) {
    this->writeOutput(trimZeroes((*it)->toString()) + "\n");
  }
}

std::string Vm::getOutput() { return this->output; }

Vm::~Vm() {
  for (auto ptr : this->stack) {
    delete ptr;
  }
}
