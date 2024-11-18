#pragma once

#include "Token.hpp"
#include <map>
#include <string>
#include <vector>
class Lexer {
private:
  std::map<std::string, TokenType> keywords;
  using StrIter = std::string::const_iterator;
  Token generateWord(StrIter it, StrIter current, int line);

public:
  Lexer();
  Lexer(const Lexer &other);
  Lexer &operator=(const Lexer &other);
  ~Lexer();
  std::vector<Token> lex(const std::string &);
  std::vector<Token> lex(const std::string &, int line);
};
