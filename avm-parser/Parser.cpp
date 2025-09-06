#include "Parser.hpp"
#include "../avm-exceptions/ParserException.hpp"
#include "../avm-lib/utils.hpp"
#include "Instruction.hpp"
#include "VmValue.hpp"
#include <fmt/base.h>
#include <fmt/format.h>
#include <optional>
#include <stdexcept>
#include <string>

// TODO: if you face an error when the previous token is a newline, recover immediately instead of going to the next newline
Instruction Parser::parseAssert() {
  consume(TokenType::Assert);
  VmValue operand = parseValue();
  consume(TokenType::Sep);

  return generateInstruction(TokenType::Assert, operand);
}

Instruction Parser::parsePush() {
  consume(TokenType::Push);
  VmValue operand = parseValue();
  consume(TokenType::Sep);

  return generateInstruction(TokenType::Push, operand);
}

VmValue Parser::parseValue() {
  Token precision = consume(TokenType::Word);
  consume(TokenType::LeftParen);
  Token value = consume(TokenType::Word);
  consume(TokenType::RightParen);

  if (!utils::is_valid_number(value.literal)) {
    hasErrored = true;
    throw ParserException(ParserException::Type::SyntaxError, value);
  }

  VmValue operand{};
  OperandFactory of{};
  const IOperand *ptr{nullptr}; // Used to check underflow/overflow
  try {
    if (precision.literal == "int8") {
      ptr = of.createOperand(eOperandType::Int8, value.literal);
      operand = VmValue{.type = eOperandType::Int8, .value = value.literal};
    } else if (precision.literal == "int16") {
      ptr = of.createOperand(eOperandType::Int16, value.literal);
      operand = VmValue{.type = eOperandType::Int16, .value = value.literal};
    } else if (precision.literal == "int32") {
      ptr = of.createOperand(eOperandType::Int32, value.literal);
      operand = VmValue{.type = eOperandType::Int32, .value = value.literal};
    } else if (precision.literal == "float") {
      ptr = of.createOperand(eOperandType::Float, value.literal);
      operand = VmValue{.type = eOperandType::Float, .value = value.literal};
    } else if (precision.literal == "double") {
      ptr = of.createOperand(eOperandType::Double, value.literal);
      operand = VmValue{.type = eOperandType::Double, .value = value.literal};
    } else
      consume(TokenType::Dummy);

  } catch (std::out_of_range &e) {
    delete ptr;
    if (value.literal[0] == '-')
      throw ParserException(ParserException::Type::Underflow, value);
    else
      throw ParserException(ParserException::Type::Overflow, value);
  }

  delete ptr;
  return operand;
}

std::optional<Token> Parser::peek() {
  if (tokens.size() != 0)
    return tokens.front();
  return std::nullopt;
}

Token Parser::consume(TokenType type) {
  Token token = tokens.front();
  if (token.type != type) {
    hasErrored = true;
    recoverParser();
    throw ParserException(ParserException::Type::SyntaxError, token);
  }

  tokens.pop_front();
  return token;
}

void Parser::recoverParser() {
  while (peek() && peek()->type != TokenType::Sep)
    tokens.pop_front();
  while (peek() && peek()->type == TokenType::Sep)
    tokens.pop_front();
}

Instruction Parser::generateInstruction(TokenType type) {
  Instruction instruction{type, VmValue()};

  return instruction;
}

Instruction Parser::generateInstruction(TokenType type, VmValue operand) {
  Instruction instruction{type, operand};

  return instruction;
}

bool Parser::getErrorState() { return hasErrored; }

std::vector<std::string> Parser::getErrors() { return errors; }

Parser::Parser() : hasErrored{false} {}

Parser::Parser(const std::vector<Token> &tokens)
    : tokens{std::deque(tokens.begin(), tokens.end())}, hasErrored{false} {}

Parser::Parser(const Parser &o)
    : tokens{std::deque{o.tokens}}, errors{o.errors}, hasErrored{o.hasErrored} {
}

Parser &Parser::operator=(const Parser &o) {
  if (this == &o)
    return *this;

  this->tokens = std::deque(o.tokens.begin(), o.tokens.end());
  this->hasErrored = o.hasErrored;
  this->errors = o.errors;

  return *this;
}

Parser::~Parser() {}
