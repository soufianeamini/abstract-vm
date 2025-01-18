#include "avm-fmt/Formatter.hpp"
#include "avm-lexer/Lexer.hpp"
#include "avm-parser/Instruction.hpp"
#include "avm-parser/Parser.hpp"
#include "avm-virtual-machine/InputHandler.hpp"
#include "avm-virtual-machine/Vm.hpp"
#include "external-libs/include/fmt/format.h"
#include "fmt/format.h"
#include <cstdio>
#include <deque>
#include <fmt/base.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

void printInstruction(const Instruction &i) {
  fmt::println("Instruction: {}, Value: {}", fmt::underlying(i.command),
               i.value.value);
}

// TODO: Change PascalCase to camelCase

void FileMode(std::string filename) {
  std::string source = InputHandler::ReadFile(filename);
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
  vm.interpret();
  fmt::print(vm.getOutput());
}

void Repl() {
  int lineNumber = 1;
  std::vector<Token> tokens;
  bool breakFromWhile = false;

  while (auto line = InputHandler::ReadLine()) {
    Lexer lexer;
    auto nTokens = lexer.lex(*line + "\n", lineNumber);
    lineNumber++;

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

void formatFile(std::string filename, std::deque<std::string> args) {
  (void)args;
  Formatter formatter;
  std::string source = InputHandler::ReadFile(filename);

  if (auto formattedString = formatter.formatAvm(source)) {
    fmt::println("{}", *formattedString);
  } else {
    fmt::println(stderr, "Error, couldn't format file: Invalid avm program.");
  }
}

void handleOptions(std::deque<std::string> args) {
  args.pop_front(); // Remove program name
  try {
    std::string option = args.at(0);
    std::string value = args.at(1);
    if (option == "--format") {
      args.pop_front();
      formatFile(value, args);
    }
  } catch (std::out_of_range &e) {
    fmt::println(stderr, "Usage: ./avm --<opt> <value>");
  }
}

std::deque<std::string> getArgs(int argc, char *argv[]) {
  std::deque<std::string> args;
  for (int i = 0; i < argc; i++) {
    args.push_back(argv[i]);
  }

  return args;
}

constexpr bool test_mode = false;

int main(int argc, char *argv[]) {
  if constexpr (test_mode) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
  } else {
    std::deque<std::string> args = getArgs(argc, argv);
    try {
      if (args.size() == 1) {
        Repl();
      } else if (args.size() == 2) {
        FileMode(args[1]);
      } else if (args.size() > 2) {
        handleOptions(args);
      } else {
        fmt::println(stderr, "Usage: ./avm [.avm file]");
      }
    } catch (std::exception &e) {
      fmt::println(stderr, "error: {}", e.what());
    }
    return 0;
  }
}
