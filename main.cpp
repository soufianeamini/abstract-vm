#include "external-libs/include/fmt/format.h"
#include "fmt/format.h"
#include "lexer/Lexer.hpp"
#include "operand/IOperand.hpp"
#include "parser/Instruction.hpp"
#include "parser/Parser.hpp"
#include "vm/InputHandler.hpp"
#include "vm/Vm.hpp"
#include <cstdio>
#include <fmt/base.h>
#include <iostream>
#include <string>

void printInstruction(const Instruction &i) {
  if (i.value) {
    fmt::println("Instruction: {}, Value: {}", fmt::underlying(i.command),
                 i.value->toString());
  } else
    fmt::println("Instruction: {}", fmt::underlying(i.command));
}

void printToken(const Token &t) {
  if (t.type != TokenType::Sep)
    fmt::println("Token: {}, line: {}", t.literal, t.line);
  else
    fmt::println("TOKEN::SEP");
}

void FileMode(const char *arg) {
  std::string filename = arg;

  std::string source = InputHandler::ReadFile(filename);
  Lexer lexer;
  auto tokens = lexer.lex(source);
  // for (const auto &t : tokens) {
  //   printToken(t);
  // }
  Parser parser(tokens);
  auto instructions = parser.parse(false);

  if (parser.getErrorState()) {
    for (auto &error : parser.getErrors()) {
      fmt::println("{}", error);
    }
    std::exit(1);
  }

  Vm vm(instructions);

  // for (const auto &i : instructions) {
  //   printInstruction(i);
  // }

  vm.interpret();
}

void Repl() {
  std::string line;
  // int lineNumber = 1;
  std::vector<Token> tokens;
  bool breakFromWhile = false;

  while (std::getline(std::cin, line)) {
    Lexer lexer;
    // should pass line as well
    auto nTokens = lexer.lex(line + "\n");
    // lineNumber++;

    tokens.insert(tokens.end(), nTokens.begin(), nTokens.end());

    for (const auto &token : nTokens) {
      if (token.type == TokenType::EndOfProgram)
        breakFromWhile = true;
    }

    if (breakFromWhile)
      break;
  }

  // for (const auto &t : tokens) {
	//   fmt::println("{}", t);
  //   printToken(t);
  // }

  Parser parser(tokens);
  auto instructions = parser.parse(true);
  if (parser.getErrorState()) {
    for (auto &error : parser.getErrors()) {
      fmt::println(stderr, "{}", error);
    }
    std::exit(1);
  }

  Vm vm(instructions);
  vm.interpret();
}

void printOperand(const IOperand *op) {
	// implement format_as instead of using this function
  fmt::println("Op: {}, value: {}", fmt::underlying(op->getType()),
               op->toString());
}

int main(int argc, char *argv[]) {
  try {
    if (argc == 1) {
      Repl();
    } else if (argc == 2) {
      FileMode(argv[1]);
    } else {
      fmt::println(stderr, "Usage: ./avm [.avm file]");
    }
  } catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
  }
  return 0;
}
