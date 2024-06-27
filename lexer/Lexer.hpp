#pragma once

#include "Token.hpp"
#include <map>
#include <string>
#include <string_view>
#include <vector>
class Lexer {
private:
  std::map<std::string, TokenType> keywords;
  using StrViewIter = std::string_view::const_iterator;
  Token generateWord(StrViewIter it, StrViewIter current, int line);

public:
  Lexer();
  Lexer(const Lexer& other);
  Lexer& operator=(const Lexer&other);
  ~Lexer();
  std::vector<Token> lex(std::string_view);
};
