#include "Lexer.hpp"
#include "Token.hpp"
#include <print>
#include <string_view>

std::vector<Token> Lexer::lex(std::string_view source) {
  std::vector<Token> tokens;
  int line = 1;
  StrViewIter current = nullptr;
  bool word = false;

  for (StrViewIter it = source.cbegin(); it < source.cend(); it++) {
    switch (*it) {
    case '(': {
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      std::string_view slice(it, it + 1);
      tokens.push_back(
          Token{.type = TokenType::LeftParen, .literal = slice, .line = line});
      break;
    }
    case ')': {
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      std::string_view slice(it, it + 1);
      tokens.push_back(
          Token{.type = TokenType::RightParen, .literal = slice, .line = line});
      break;
    }
    case ';': {
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      if (it + 1 != source.cend() && *(it + 1) == ';') {
        std::string_view slice(it, it + 2);
        tokens.push_back(Token{
            .type = TokenType::EndOfProgram, .literal = slice, .line = line});
      } else {
        while (it != source.cend() && *it != '\n') {
          it++;
        }
        line++;
      }
      break;
    }
    case '\n':
      line++;
      [[fallthrough]];
    case ' ':
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      break;
    default:
      if (!word) {
        word = true;
        current = it;
      }
      break;
    }
  }

  return tokens;
}

Token Lexer::generateWord(StrViewIter it, StrViewIter current, int line) {
  std::string_view slice(current, it);

  return Token{.type = TokenType::Word, .literal = slice, .line = line};
}
