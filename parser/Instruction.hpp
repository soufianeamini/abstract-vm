#pragma once

#include "../lexer/Token.hpp"
#include "../operand/IOperand.hpp"
#include "VmValue.hpp"

struct Instruction {
  TokenType command;
  VmValue value;
};
