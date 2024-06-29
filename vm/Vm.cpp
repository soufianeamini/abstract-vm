#include "Vm.hpp"
#include "../exceptions/customExceptions.hpp"
#include <print>

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
      this->assert();
      break;
    }
    ip++;
  }
}

void Vm::push() { stack.push_back(ip->value); }

void Vm::pop() {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);
  this->stack.pop_back();
}

void Vm::assert() {
  if (stack.size() == 0)
    throw VmException(VmException::Type::EmptyStack);

  std::string actual = stack.back()->toString();
  std::string expected = ip->value->toString();
  if (actual != expected)
    throw VmException(VmException::Type::Assert);
}

void Vm::dumpStack() {
  for (const auto &operand : stack) {
    std::println("{}", operand->toString());
  }
}

Vm::~Vm() {}
