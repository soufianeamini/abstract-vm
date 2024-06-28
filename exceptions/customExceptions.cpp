#include "customExceptions.hpp"
#include <array>
#include <format>
#include <utility>

const char *ParserException::what() const noexcept {
  std::array<const char *, 2> messages{"Error: Syntax Error",
                                       "Error: Unkown Instruction"};

  return messages.at(std::to_underlying(type));
}

std::string ParserException::getLineInfo() const {
  std::string info = std::format("at line: {}, token: '{}'", errorToken.line,
                                 errorToken.literal);

  return info;
}

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

  return messages.at(std::to_underlying(type));
}

ParserException::ParserException() {}
ParserException::ParserException(Type type, Token errorToken)
    : type(type), errorToken(errorToken) {}
ParserException::ParserException(const ParserException &o)
    : type(o.type), errorToken(o.errorToken) {}
ParserException &ParserException::operator=(const ParserException &o) {
  if (this == &o)
    return *this;

  type = o.type;
  errorToken = o.errorToken;

  return *this;
}
ParserException::~ParserException() {}

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
