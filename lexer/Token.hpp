#pragma once

#include <string>
enum class TokenType {
  Word,
  Push,
  Pop,
  Dump,
  Assert,
  Add,
  Sub,
  Mul,
  Div,
  Mod,
  Print,
  Exit,
  LeftParen,    // (
  RightParen,   // )
  EndOfProgram, // ;;
  Sep,
  Dummy,
};

struct Token {
  TokenType type;
  std::string literal;
  int line;
};

std::string format_as(const Token& t);
