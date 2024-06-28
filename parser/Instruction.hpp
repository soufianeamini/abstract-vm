#pragma once

#include "../lexer/Token.hpp"
#include "../operand/IOperand.hpp"

struct Instruction {
  TokenType command;
  const IOperand *value;
};
