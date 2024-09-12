#include "ParserException.hpp"
#include <array>
#include <sstream>

const char *ParserException::what() const noexcept {
  static std::array<const char *, 4> messages{
      "Error: Syntax Error", "Error: Unkown Instruction", "Error: Overflow",
      "Error: Underflow"};

  return messages.at((type));
}

std::string ParserException::getLineInfo() const {
  std::stringstream info;
  info << "at line: " << errorToken.line << ", token: '" << errorToken.literal
       << "'.";

  return info.str();
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
