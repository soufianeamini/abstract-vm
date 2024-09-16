#include "lexer/Lexer.hpp"
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

  try {
    vm.interpret();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void Repl() {
  Vm vm;
  std::string line;
  std::string input;
  std::vector<Token> tokens;
  bool breakFromWhile = false;

  while (std::getline(std::cin, line)) {
    Lexer lexer;
    input += line + "\n";
    auto nTokens = lexer.lex(line + "\n");

    tokens.insert(tokens.end(), nTokens.begin(), nTokens.end());

    for (auto token : nTokens) {
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
      std::cerr << error << std::endl;
    }
    std::exit(1);
  }

  try {
    vm.interpret();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}

void printOperand(const IOperand *op) {
  std::cout << "Op: " << op->getType() << ", value: " << op->toString()
            << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    Repl();
  } else if (argc == 2) {
    FileMode(argv[1]);
  } else {
    std::cerr << "Usage: ./avm [.avm file]";
  }
  return 0;
}
