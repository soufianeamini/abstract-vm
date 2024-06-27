#include "Lexer.hpp"
#include "Token.hpp"
#include <print>
#include <string_view>

std::vector<Token> Lexer::lex(std::string_view source) {
  std::vector<Token> tokens;

  for (std::string_view::const_iterator it = source.cbegin();
       it < source.cend(); it++) {
    std::println("[*it: {}]", *it);
  }

  return tokens;
}
