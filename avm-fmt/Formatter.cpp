#include "Formatter.hpp"
#include "../avm-lexer/Lexer.hpp"
#include "../avm-parser/Parser.hpp"
#include <optional>

static void validateInput(const std::string& input) {
  Lexer lexer{};
  std::vector<Token> tokens = lexer.lex(input);
  Parser parser{tokens};
  auto instructions{parser.parse<NonRepl>()};

  if (parser.getErrorState()) {
    for (auto &error : parser.getErrors()) {
      fmt::println("{}", error);
    }
    std::exit(1);
  }
}

std::optional<std::string> Formatter::formatAvm(const std::string &input) {
  Lexer lexer{true};
  std::vector<Token> tokens = lexer.lex(input);
  validateInput(input);
  std::vector<Token> deduplicatedTokens = removeDuplicateSep(tokens);
  std::string formatted_string = emitStringFromTokens(deduplicatedTokens);

  return formatted_string;
}

std::vector<Token>
Formatter::removeDuplicateSep(const std::vector<Token> &tokens) {
  std::vector<Token> new_tokens;
  int sepCooldown = 0;

  for (Token token : tokens) {
    if (token.type == TokenType::Sep) {
      if (sepCooldown < 2) {
        sepCooldown++;
        new_tokens.push_back(token);
      }
    } else {
      sepCooldown = 0;
      new_tokens.push_back(token);
    }
  }

  return new_tokens;
}

std::string Formatter::emitStringFromTokens(const std::vector<Token> &tokens) {
  std::string result;

  for (const auto &token : tokens) {
    if (token.type == TokenType::Sep) {
      result += "\n";
    } else {
      if (token.type == TokenType::Push or token.type == TokenType::Assert) {
        result += token.literal + " ";
      } else {
        result += token.literal;
      }
    }
  }

  return result;
}
