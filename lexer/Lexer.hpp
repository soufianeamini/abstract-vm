#pragma once

#include "Token.hpp"
#include <string_view>
#include <vector>
class Lexer {
private:
  size_t current;

public:
  std::vector<Token> lex(std::string_view);
};
