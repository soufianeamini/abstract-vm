#include "./Token.hpp"
#include <fmt/format.h>

std::string format_as(const Token &t) {
  auto literal = t.literal;
  if (t.type == TokenType::Sep)
    literal = "<newline>";
  return fmt::format("Token {{ type: {}, literal: {}, line: {} }}",
                     fmt::underlying(t.type), literal, t.line);
}
