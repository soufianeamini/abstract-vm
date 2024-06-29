#include "Vm.hpp"

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
    // switch (ip->command) {
    //
    // }
    ip++;
  }
}

Vm::~Vm() {}
