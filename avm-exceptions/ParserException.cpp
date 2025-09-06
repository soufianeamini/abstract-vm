#include "ParserException.hpp"
#include <array>
#include <fmt/format.h>
#include <sstream>
#include <stdexcept>

const char *ParserException::what() const noexcept {
  static std::array<const char *, 4> messages{
      "Error: Syntax Error", "Error: Unkown Instruction", "Error: Overflow",
      "Error: Underflow"};

  return messages.at(fmt::underlying(type));
}

std::string ParserException::getLineInfo() const {
  std::stringstream info;
  info << "at line: " << errorToken.line << ", token: '" << errorToken.literal
       << "'.";

  return info.str();
}

std::string format_as(const ParserException::Type &t) {
  // clang-format off
  switch (t) {
		case ParserException::Type::SyntaxError: return "SyntaxError";
		case ParserException::Type::UnknownInstruction: return "UnknownInstruction";
		case ParserException::Type::Overflow: return "Overflow";
		case ParserException::Type::Underflow: return "Underflow";
		default: return "(Unknown ParserException type)";
  }
  // clang-format on
}

ParserException::ParserException() : std::runtime_error("") {}
ParserException::ParserException(Type type, Token errorToken)
    : std::runtime_error(""), type(type), errorToken(errorToken) {}
ParserException::ParserException(const ParserException &o)
    : std::runtime_error(""), type(o.type), errorToken(o.errorToken) {}
ParserException &ParserException::operator=(const ParserException &o) {
  if (this == &o)
    return *this;

  type = o.type;
  errorToken = o.errorToken;

  return *this;
}
ParserException::~ParserException() {}
