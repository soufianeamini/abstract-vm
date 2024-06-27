#pragma once

#include "Token.hpp"
#include <string_view>
#include <vector>
class Lexer {
private:
  using StrViewIter = std::string_view::const_iterator;
  Token generateWord(StrViewIter it, StrViewIter current, int line);

public:
  std::vector<Token> lex(std::string_view);
};
