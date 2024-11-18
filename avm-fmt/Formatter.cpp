#include "Formatter.hpp"
#include "../avm-lexer/Lexer.hpp"
#include <optional>

std::optional<std::string> Formatter::format_avm(const std::string &input) {

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
  // TODO: remove duplicate SEP tokens, however other whitespaces is already
  // removed from the lexing step
  // NOTE: If there are more than 2 sep tokens, reduce them to 2 instead. But if
  // there are 2 or 1 sep token just leave them as is
  std::vector<Token> new_tokens;

  return new_tokens;
}
