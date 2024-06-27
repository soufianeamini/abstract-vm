#include "lexer/Lexer.hpp"
#include "vm/InputHandler.hpp"
#include <print>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::println("Reading from standard input");
  } else if (argc == 2) {
    std::string filename = argv[1];
    std::println("Reading from file: {}", filename);

    std::string source = InputHandler::ReadFile(filename);
    Lexer lexer;
    lexer.lex(source);
  } else {
    std::println(stderr, "Usage: ./avm [.avm file]");
  }
  return 0;
}
