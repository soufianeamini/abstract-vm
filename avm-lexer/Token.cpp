#include "./Token.hpp"
#include <fmt/format.h>

std::string format_as(const Token &t) {
  auto literal = t.literal;
  if (t.type == TokenType::Sep)
    literal = "<newline>";
  return fmt::format("Token {{ type: {}, literal: {}, line: {} }}",
                     fmt::underlying(t.type), literal, t.line);
}

std::string format_as(const TokenType &t) {
  // clang-format off
	switch (t) {
		case TokenType::Word: return "Word";
		case TokenType::Push: return "Push";
		case TokenType::Pop: return "Pop";
		case TokenType::Dump: return "Dump";
		case TokenType::Assert: return "Assert";
		case TokenType::Add: return "Add";
		case TokenType::Sub: return "Sub";
		case TokenType::Mul: return "Mul";
		case TokenType::Div: return "Div";
		case TokenType::Mod: return "Mod";
		case TokenType::Print: return "Print";
		case TokenType::Exit: return "Exit";
		case TokenType::LeftParen: return "LeftParen";
		case TokenType::RightParen: return "RightParen";
		case TokenType::EndOfProgram: return "EndOfProgram";
		case TokenType::Sep: return "Sep";
		case TokenType::Dummy: return "Dummy";
		default: return "(Unknown TokenType type)";
	}
  // clang-format on
}
