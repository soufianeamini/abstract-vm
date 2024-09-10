#include "ParserException.hpp"
#include <array>

const char *ParserException::what() const noexcept {
  std::array<const char *, 2> messages{"Error: Syntax Error",
                                       "Error: Unkown Instruction"};

  return messages.at((type));
}

std::string ParserException::getLineInfo() const {
  std::string info = std::string("at line: ") +
                     std::to_string(errorToken.line) + ", token: '" +
                     std::string(errorToken.literal);

  return info;
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
