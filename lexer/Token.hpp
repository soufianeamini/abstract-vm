#pragma once

#include <string_view>
enum class TokenType {
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
};

struct Token {
  TokenType type;
  std::string_view literal;
};
