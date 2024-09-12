#include "Parser.hpp"
#include "../avm-lib/utils.hpp"
#include "../exceptions/ParserException.hpp"
#include "../operand/OperandFactory.hpp"
#include "Instruction.hpp"
#include <optional>
#include <stdexcept>
#include <string>

std::vector<Instruction> Parser::parse() {
  std::vector<Instruction> instructions;

  while (tokens.size() > 0) {
    try {
      instructions.push_back(parseInstruction());
      while (peek().has_value() && peek()->type == TokenType::Sep)
        consume(TokenType::Sep);
    } catch (ParserException &e) {
			hasErrored = true;
      std::string errMsg = std::string(e.what()) + " " + e.getLineInfo();
      errors.push_back(errMsg);
    }
  }

  return instructions;
}

Instruction Parser::parseInstruction() {
  while (peek().has_value() && peek()->type == TokenType::Sep)
    consume(TokenType::Sep);

  if (!peek().has_value())
    return generateInstruction(consume(TokenType::Dummy).type);

  switch (peek()->type) {
  case TokenType::Push:
    return parsePush();
  case TokenType::Assert:
    return parseAssert();
  case TokenType::Pop:
    tokens.pop_front();
    return generateInstruction(TokenType::Pop);
  case TokenType::Dump:
    tokens.pop_front();
    return generateInstruction(TokenType::Dump);
  case TokenType::Add:
    tokens.pop_front();
    return generateInstruction(TokenType::Add);
  case TokenType::Sub:
    tokens.pop_front();
    return generateInstruction(TokenType::Sub);
  case TokenType::Mul:
    tokens.pop_front();
    return generateInstruction(TokenType::Mul);
  case TokenType::Div:
    tokens.pop_front();
    return generateInstruction(TokenType::Div);
  case TokenType::Mod:
    tokens.pop_front();
    return generateInstruction(TokenType::Mod);
  case TokenType::Print:
    tokens.pop_front();
    return generateInstruction(TokenType::Print);
  case TokenType::Exit:
    tokens.pop_front();
    return generateInstruction(TokenType::Exit);
  case TokenType::EndOfProgram:
    tokens.pop_front();
    return generateInstruction(TokenType::EndOfProgram);
  default:
    consume(TokenType::Dummy);
  }

  return generateInstruction(consume(TokenType::Dummy).type);
}

Instruction Parser::parseAssert() {
  consume(TokenType::Assert);
  const IOperand *operand = parseValue();
  consume(TokenType::Sep);

  return generateInstruction(TokenType::Assert, operand);
}

Instruction Parser::parsePush() {
  consume(TokenType::Push);
  const IOperand *operand = parseValue();
  consume(TokenType::Sep);

  return generateInstruction(TokenType::Push, operand);
}

const IOperand *Parser::parseValue() {
  Token precision = consume(TokenType::Word);
  consume(TokenType::LeftParen);
  Token value = consume(TokenType::Word);
  consume(TokenType::RightParen);

  if (!utils::is_valid_number(value.literal))
    throw std::invalid_argument("invalid_number: " + value.literal);

  const IOperand *operand = nullptr;
  OperandFactory of;
  try {
    if (precision.literal == "int8")
      operand =
          of.createOperand(eOperandType::Int8, std::string(value.literal));
    else if (precision.literal == "int16")
      operand =
          of.createOperand(eOperandType::Int16, std::string(value.literal));
    else if (precision.literal == "int32")
      operand =
          of.createOperand(eOperandType::Int32, std::string(value.literal));
    else if (precision.literal == "float")
      operand =
          of.createOperand(eOperandType::Float, std::string(value.literal));
    else if (precision.literal == "double")
      operand =
          of.createOperand(eOperandType::Double, std::string(value.literal));
    else
      consume(TokenType::Dummy);

  } catch (std::out_of_range &e) {
    if (value.literal[0] == '-')
      throw ParserException(ParserException::Type::Underflow, value);
    else
      throw ParserException(ParserException::Type::Overflow, value);
  }

  return operand;
}

std::optional<Token> Parser::peek() {
  if (tokens.size() != 0)
    return std::make_optional(tokens.front());
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
  while (peek().has_value() && peek()->type != TokenType::Sep)
    tokens.pop_front();
  while (peek().has_value() && peek()->type == TokenType::Sep)
    tokens.pop_front();
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

bool Parser::getErrorState() { return hasErrored; }

std::vector<std::string> Parser::getErrors() { return errors; }

Parser::Parser() : hasErrored(false) {}

Parser::Parser(const std::vector<Token> &tokens)
    : tokens(std::deque(tokens.begin(), tokens.end())), hasErrored(false) {}

Parser::Parser(const Parser &o)
    : tokens(std::deque(o.tokens.begin(), o.tokens.end())), errors(o.errors),
      hasErrored(o.hasErrored) {}

Parser &Parser::operator=(const Parser &o) {
  if (this == &o)
    return *this;

  this->tokens = std::deque(o.tokens.begin(), o.tokens.end());
  this->hasErrored = o.hasErrored;
  this->errors = o.errors;

  return *this;
}

Parser::~Parser() {}
