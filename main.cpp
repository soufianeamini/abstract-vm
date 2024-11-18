// #define DEBUG

#include "avm-fmt/Formatter.hpp"
#include "avm-lexer/Lexer.hpp"
#include "avm-parser/Instruction.hpp"
#include "avm-parser/Parser.hpp"
#include "avm-virtual-machine/InputHandler.hpp"
#include "avm-virtual-machine/Vm.hpp"
#include "external-libs/include/fmt/format.h"
#include "fmt/format.h"
#include <cstdio>
#include <fmt/base.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

void printInstruction(const Instruction &i) {
  fmt::println("Instruction: {}, Value: {}", fmt::underlying(i.command),
               i.value.value);
}

void PrintFormattedVersion(const std::string &source) {
  Formatter formatter;
  fmt::println("Formatted Input:");
  fmt::println("{}", *formatter.formatAvm(source));
}

void FileMode(const char *arg) {
  std::string filename = arg;

  // TODO: handle file not existing:
  std::string source = InputHandler::ReadFile(filename);
  PrintFormattedVersion(source);
  Lexer lexer;
  auto tokens = lexer.lex(source);
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
  fmt::print(vm.getOutput());
}

void Repl() {
  std::string line;
  // int lineNumber = 1;
  std::vector<Token> tokens;
  bool breakFromWhile = false;

  // TODO: change std::getline() to InputHandler::ReadLine()
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
  fmt::print(vm.getOutput());
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  try {
    if (argc == 1) {
      Repl();
    } else if (argc == 2) {
      FileMode(argv[1]);
    } else {
      fmt::println(stderr, "Usage: ./avm [.avm file]");
    }
  } catch (std::exception &e) {
    fmt::println(stderr, "error: {}", e.what());
  }
  return 0;
#endif
}
