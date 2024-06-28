#pragma once

#include "Instruction.hpp"
#include <deque>
#include <vector>
class Parser {
private:
  std::deque<Token> tokens;
  Instruction generateInstruction(TokenType type);
  Instruction generateInstruction(TokenType type, const IOperand *operand);

  Token consume(TokenType type);
  void parseInstruction();

public:
  Parser();
  Parser(const std::vector<Token> &tokens);
  Parser(const Parser &o);
  Parser &operator=(const Parser &o);
  ~Parser();
  std::vector<Instruction> parse();
};
