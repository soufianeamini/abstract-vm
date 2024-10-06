#include <nlohmann/json.hpp>
#include "fmt/format.h"
#include "lexer/Lexer.hpp"
#include "nlohmann/json_fwd.hpp"
#include "operand/IOperand.hpp"
#include "parser/Instruction.hpp"
#include "parser/Parser.hpp"
#include "vm/InputHandler.hpp"
#include "vm/Vm.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

void printInstruction(const Instruction &i) {
  if (i.value) {
    std::cout << "Instruction: " << i.command
              << ", Value: " << i.value->toString() << "\n";
  } else
    std::cout << "Instruction: " << i.command << std::endl;
}

void printToken(const Token &t) {
  if (t.type != TokenType::Sep)
    std::cout << "Token: " << t.literal << ", line: " << t.line << std::endl;
  else
    std::cout << "TOKEN::SEP" << std::endl;
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
      std::cout << error << std::endl;
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

  for (const auto &t : tokens) {
    printToken(t);
  }

  Parser parser(tokens);
  auto instructions = parser.parse(true);
  if (parser.getErrorState()) {
    for (auto &error : parser.getErrors()) {
      std::cerr << error << std::endl;
    }
    std::exit(1);
  }

  Vm vm(instructions);
  vm.interpret();
}

void printOperand(const IOperand *op) {
  std::cout << "Op: " << op->getType() << ", value: " << op->toString()
            << std::endl;
}

int main(int argc, char *argv[]) {
  try {
    if (argc == 1) {
			std::cout << fmt::format("Test");
			nlohmann::json x;
      Repl();
    } else if (argc == 2) {
      FileMode(argv[1]);
    } else {
      std::cerr << "Usage: ./avm [.avm file]";
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
