#include "VmException.hpp"
#include <array>

const char *VmException::what() const noexcept {
  std::array<const char *, 7> messages{
      "Error: Overflow on a value",
      "Error: Underflow on a value",
      "Error: Instruction pop on empty stack",
      "Error: Division/modulo by 0",
      "Error: Program has no exit instruction",
      "Error: Assertion failed!",
      "Error: Stack has less than two values on arithmetic instruction",
  };

  return messages.at((type));
}

VmException::VmException() {}
VmException::VmException(Type type) : type(type) {}
VmException::VmException(const VmException &o) : type(o.type) {}
VmException &VmException::operator=(const VmException &o) {
  if (this == &o)
    return *this;

  type = o.type;

  return *this;
}
VmException::~VmException() {}
