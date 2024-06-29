#include "lexer/Lexer.hpp"
#include "operand/IOperand.hpp"
#include "operand/OperandFactory.hpp"
#include "parser/Instruction.hpp"
#include "parser/Parser.hpp"
#include "vm/InputHandler.hpp"
#include "vm/Vm.hpp"
#include <cstdlib>
#include <print>
#include <utility>

void printInstruction(const Instruction &i) {
  if (i.value)
    std::println("Instruction: {}, Value: {}", std::to_underlying(i.command),
                 i.value->toString());
  else
    std::println("Instruction: {}", std::to_underlying(i.command));
}

void printToken(const Token &t) {
  if (t.type != TokenType::Sep)
    std::println("Token: {}, line: {}", t.literal, t.line);
}

void FileMode(const char *arg) {
  std::string filename = arg;
  std::println("Reading from file: {}", filename);

  std::string source = InputHandler::ReadFile(filename);
  Lexer lexer;
  auto tokens = lexer.lex(source);
  Parser parser(tokens);
  auto instructions = parser.parse();

  if (parser.getErrorState()) {
    for (auto &error : parser.getErrors()) {
      std::println("{}", error);
    }
    std::exit(1);
  }

  Vm vm(instructions);

  for (const auto &t : tokens) {
    printToken(t);
  }

  for (const auto &i : instructions) {
    printInstruction(i);
  }
}

void Repl() {}

void printOperand(const IOperand *op) {
  std::println("Op: {}, value: {}", std::to_underlying(op->getType()),
               op->toString());
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::println("Reading from standard input");
    Repl();
  } else if (argc == 2) {
    FileMode(argv[1]);
  } else {
    std::println(stderr, "Usage: ./avm [.avm file]");
  }
  return 0;
}
