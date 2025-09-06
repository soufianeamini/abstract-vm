#include "Lexer.hpp"
#include "Token.hpp"
#include <fmt/base.h>
#include <map>
#include <string>
#include <vector>

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

Lexer::Lexer(bool preserveComments) : Lexer() {
  this->preserveComments = preserveComments;
}

std::vector<Token> Lexer::lex(const std::string &source) {
  return lex(source, 1);
}

std::vector<Token> Lexer::lex(const std::string &source, int line) {
  std::vector<Token> tokens;
  StrIter current = source.cend();
  bool word = false;

  for (StrIter it = source.cbegin(); it != source.cend(); it++) {
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
        StrIter start_it = it;
        while (it != source.cend() && *it != '\n') {
          it++;
        }
        if (it == source.cend())
          it--;
        line++;
        if (this->preserveComments) {
          std::string comment(start_it, it);
          tokens.push_back(
              Token{.type = TokenType::Comment, .literal = comment, .line = line - 1});
        }
        tokens.push_back(
            Token{.type = TokenType::Sep, .literal = "\n", .line = line - 1});
      }
      break;
    }
    case '\n':
      if (word) {
        tokens.push_back(generateWord(it, current, line));
        word = false;
      }
      line++;
      tokens.push_back(
          Token{.type = TokenType::Sep, .literal = "\n", .line = line - 1});
      [[fallthrough]];
    case '\v':
      [[fallthrough]];
    case '\t':
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

Token Lexer::generateWord(StrIter it, StrIter current, int line) {
  std::string slice(current, it);
  TokenType type = TokenType::Word;

  if (keywords.find(slice) != keywords.end()) {
    type = keywords.at(slice);
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
