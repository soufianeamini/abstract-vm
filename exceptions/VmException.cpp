#include "VmException.hpp"
#include <array>
#include <fmt/format.h>

const char *VmException::what() const noexcept {
  static std::array<const char *, 7> messages{
      "Error: Overflow on a value",
      "Error: Underflow on a value",
      "Error: Instruction pop on empty stack",
      "Error: Division/modulo by 0",
      "Error: Program has no exit instruction",
      "Error: Assertion failed!",
      "Error: Stack has less than two values on arithmetic instruction",
  };

  return messages.at(fmt::underlying(type));
}

std::string format_as(const VmException::Type &t) {
  // clang-format off
	switch (t) {
		case VmException::Type::Overflow: return "Overflow";
		case VmException::Type::Underflow: return "Underflow";
		case VmException::Type::EmptyStack: return "EmptyStack";
		case VmException::Type::DivisionByZero: return "DivisionByZero";
		case VmException::Type::NoExitInstruction: return "NoExitInstruction";
		case VmException::Type::Assert: return "Assert";
		case VmException::Type::TooFewStackValues: return "TooFewStackValues";
	}
  // clang-format on
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
