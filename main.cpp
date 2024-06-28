#include "lexer/Lexer.hpp"
#include "operand/IOperand.hpp"
#include "operand/OperandFactory.hpp"
#include "parser/Parser.hpp"
#include "vm/InputHandler.hpp"
#include <print>
#include <utility>

void FileMode(const char *arg) {
  std::string filename = arg;
  std::println("Reading from file: {}", filename);

  std::string source = InputHandler::ReadFile(filename);
  Lexer lexer;
  auto tokens = lexer.lex(source);

  for (const auto &t : tokens) {
    if (t.type != TokenType::Sep)
      std::println("Token: {}, line: {}", t.literal, t.line);
  }

  Parser parser(tokens);
  auto instructions = parser.parse();

  for (const auto &i : instructions) {
    if (i.value)
      std::println("Instruction: {}, Value: {}", std::to_underlying(i.command),
                   i.value->toString());
    else
      std::println("Instruction: {}", std::to_underlying(i.command));
  }
}

void Repl() {}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::println("Reading from standard input");
    Repl();
  } else if (argc == 2) {
    FileMode(argv[1]);
  } else {
    std::println(stderr, "Usage: ./avm [.avm file]");
  }
  OperandFactory of;

  auto op1 = of.createOperand(eOperandType::Int16, "3");
  auto op2 = of.createOperand(eOperandType::Int16, "5");

  auto res = *op1 + *op2;
  std::println("value: {}", res->toString());
  return 0;
}
