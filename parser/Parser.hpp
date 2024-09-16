#pragma once

#include "Instruction.hpp"
#include <deque>
#include <optional>
#include <vector>
class Parser {
private:
  std::deque<Token> tokens;
  std::vector<std::string> errors;
  bool hasErrored;

private:
  Instruction generateInstruction(TokenType type);
  Instruction generateInstruction(TokenType type, const IOperand *operand);

  std::optional<Token> peek();
  Token consume(TokenType type);
  void recoverParser();
  Instruction parseInstruction(bool isRepl);
  Instruction parsePush();
  Instruction parseAssert();
  const IOperand *parseValue();

public:
  Parser();
  Parser(const std::vector<Token> &tokens);
  Parser(const Parser &o);
  Parser &operator=(const Parser &o);
  ~Parser();
  std::vector<Instruction> parse(bool isRepl);
  bool getErrorState();
  std::vector<std::string> getErrors();
};
