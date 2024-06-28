#include "Parser.hpp"
#include "Instruction.hpp"

std::vector<Instruction> Parser::parse() {
  std::vector<Instruction> instructions;

  while (tokens.size() != 0) {
    parseInstruction();
  }

  return instructions;
}

void Parser::parseInstruction() {

}

Token Parser::consume(TokenType type) {
  Token token = tokens.front();
  if (token.type != type) {

  }

  return token;
}

Instruction Parser::generateInstruction(TokenType type) {
  Instruction instruction = Instruction{.command = type, .value = nullptr};

  return instruction;
}

Instruction Parser::generateInstruction(TokenType type,
                                        const IOperand *operand) {
  Instruction instruction = Instruction{.command = type, .value = operand};

  return instruction;
}

Parser::Parser() {}

Parser::Parser(const std::vector<Token> &tokens)
    : tokens(std::deque(tokens.begin(), tokens.end())) {}

Parser::Parser(const Parser &o)
    : tokens(std::deque(o.tokens.begin(), o.tokens.end())) {}

Parser &Parser::operator=(const Parser &o) {
  if (this == &o)
    return *this;

  this->tokens = std::deque(o.tokens.begin(), o.tokens.end());

  return *this;
}

Parser::~Parser() {}
