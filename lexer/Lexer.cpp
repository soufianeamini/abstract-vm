#include "Lexer.hpp"
#include "Token.hpp"
#include <map>
#include <string>

Lexer::Lexer() {
  keywords["add"] = TokenType::Add;
  keywords["push"] = TokenType::Push;
  keywords["pop"] = TokenType::Pop;
  keywords["dump"] = TokenType::Dump;
  keywords["assert"] = TokenType::Assert;
  keywords["add"] = TokenType::Add;
  keywords["sub"] = TokenType::Sub;
  keywords["mul"] = TokenType::Mul;
  keywords["div"] = TokenType::Div;
  keywords["mod"] = TokenType::Mod;
  keywords["print"] = TokenType::Print;
  keywords["exit"] = TokenType::Exit;
}

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
      std::string slice(it, it + 1);
      tokens.push_back(
          Token{.type = TokenType::LeftParen, .literal = slice, .line = line});
      break;
    }
    case ')': {
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      std::string slice(it, it + 1);
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
        std::string slice(it, it + 2);
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
      tokens.push_back(
          Token{.type = TokenType::Sep, .literal = "\n", .line = line});
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
  std::string slice(current, it);
  TokenType type = TokenType::Word;

  if (keywords.find(std::string(slice)) != keywords.end()) {
    type = keywords.at(std::string(slice));
  }

  return Token{.type = type, .literal = slice, .line = line};
}

Lexer::~Lexer() {}

Lexer::Lexer(const Lexer &other) : keywords(other.keywords) {}

Lexer &Lexer::operator=(const Lexer &other) {
  if (this == &other)
    return *this;

  this->keywords = std::map<std::string, TokenType>(other.keywords);

  return *this;
}
