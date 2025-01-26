#pragma once

#include "../avm-exceptions/ParserException.hpp"
#include "Instruction.hpp"
#include "VmValue.hpp"
#include <deque>
#include <optional>
#include <vector>

// Parse line by line and enable EndOfProgram token
class Repl;

// Parse an entire file and disable EndOfProgram token
class NonRepl;

template <class ReplMode> constexpr static void checkReplInvariants() {
  static_assert(std::is_same<ReplMode, Repl>() ||
                    std::is_same<ReplMode, NonRepl>(),
                "Invalid ReplMode parameter");
}

class Parser {
private:
  std::deque<Token> tokens;
  std::vector<std::string> errors;
  bool hasErrored;

private:
  Instruction generateInstruction(TokenType type);
  Instruction generateInstruction(TokenType type, VmValue operand);

  std::optional<Token> peek();
  Token consume(TokenType type);
  void recoverParser();
  template <class ReplMode> Instruction parseInstruction() {

    checkReplInvariants<ReplMode>();
    while (peek() && peek()->type == TokenType::Sep)
      consume(TokenType::Sep);

    if (!peek())
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
      if constexpr (std::is_same<ReplMode, Repl>()) {
        consume(TokenType::Dummy);
      }
      tokens.pop_front();
      return generateInstruction(TokenType::EndOfProgram);
    default:
      consume(TokenType::Dummy);
    }

    return generateInstruction(consume(TokenType::Dummy).type);
  };
  Instruction parsePush();
  Instruction parseAssert();
  VmValue parseValue();

public:
  Parser();
  Parser(const std::vector<Token> &tokens);
  Parser(const Parser &o);
  Parser &operator=(const Parser &o);
  ~Parser();
  template <class ReplMode> std::vector<Instruction> parse() {
    checkReplInvariants<ReplMode>();
    std::vector<Instruction> instructions{};

    while (tokens.size() > 0) {
      try {
        instructions.push_back(parseInstruction<ReplMode>());
        while (peek() && peek()->type == TokenType::Sep)
          consume(TokenType::Sep);
      } catch (ParserException &e) {
        hasErrored = true;
        recoverParser();
        std::string errMsg{fmt::format("{} {}", e.what(), e.getLineInfo())};
        errors.push_back(errMsg);
      }
    }

    return instructions;
  };
  bool getErrorState();
  std::vector<std::string> getErrors();
};
