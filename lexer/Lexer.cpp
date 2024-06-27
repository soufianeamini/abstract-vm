#include "Lexer.hpp"
#include "Token.hpp"
#include <print>
#include <string_view>

std::vector<Token> Lexer::lex(std::string_view source) {
  std::vector<Token> tokens;

  for (StrViewIter it = source.cbegin(); it < source.cend(); it++) {
    std::println("[*it: {}]", *it);
    std::string_view sub(it, it + 3);
    tokens.push_back(Token{.type=TokenType::Add, .literal = sub});
    break;
  }

  return tokens;
}
