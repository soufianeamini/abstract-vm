#pragma once
#include "../avm-lexer/Token.hpp"
#include <optional>
#include <string>
#include <vector>

class Formatter {
private:
  std::vector<Token> removeDuplicateSep(const std::vector<Token> &tokens);
	std::string emitStringFromTokens(const std::vector<Token> &tokens);

public:
  std::optional<std::string> format_avm(const std::string &input);
};
