#include "Formatter.hpp"
#include "../avm-lexer/Lexer.hpp"
#include <optional>

// TODO: handle keeping comments, perhaps the lexer can handle different modes
std::optional<std::string> Formatter::formatAvm(const std::string &input) {
  Lexer lexer;
  std::vector<Token> tokens = lexer.lex(input);
  // TODO: Parse it to verify that it's a valid string, and only return a valid
  // string if it's valid, if not it's an error, return std::nullopt

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
      if (token.type == TokenType::Push) {
        result += token.literal + " ";
      } else {
        result += token.literal;
      }
    }
  }

  return result;
}
