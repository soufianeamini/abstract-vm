#include "../lexer/Lexer.hpp"
#include <gtest/gtest.h>

TEST(Lexer, SimpleTest) {
  Lexer lexer;

  auto tokens = lexer.lex("push int8(32)");

  std::vector<Token> test_tokens = {
      Token{.type = TokenType::Push, .literal = "push", .line = 1},
      Token{.type = TokenType::Word, .literal = "int8", .line = 1},
      Token{.type = TokenType::LeftParen, .literal = "(", .line = 1},
      Token{.type = TokenType::Word, .literal = "32", .line = 1},
      Token{.type = TokenType::RightParen, .literal = ")", .line = 1}};

  for (unsigned int i = 0; i < test_tokens.size(); i++) {
    auto a = tokens[i];
    auto b = test_tokens[i];

    ASSERT_EQ(a.type, b.type);
    ASSERT_EQ(a.literal, b.literal);
		ASSERT_EQ(a.line, b.line);
  }
}
