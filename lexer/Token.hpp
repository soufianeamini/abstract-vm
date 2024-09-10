#pragma once

#include <string>
enum TokenType {
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
