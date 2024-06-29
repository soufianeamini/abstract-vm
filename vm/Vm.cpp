#include "Vm.hpp"
#include "../exceptions/customExceptions.hpp"
#include <ostream>
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
      stack.push_back(ip->value);
      break;
    case TokenType::Pop:
      stack.pop_back();
      break;
    case TokenType::Dump:
      dumpStack();
      break;
    case TokenType::Assert:
      std::string top = stack.back()->toString();
      std::string assertValue = ip->value->toString();
      this->assert(top, assertValue);
      break;
    }
    ip++;
  }
}

void Vm::assert(const std::string &actual, const std::string &expected) {
  if (actual != expected)
    throw VmException(VmException::Type::Assert);
}

void Vm::dumpStack() {
  for (auto operand : stack) {
    std::println("{}", operand->toString());
  }
}

Vm::~Vm() {}
