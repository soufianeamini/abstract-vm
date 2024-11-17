#include "../lexer/Lexer.hpp"
#include "../parser/Parser.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ISOLATE_TEST()                                                         \
  pid_t pid = fork();                                                          \
  if (pid == -1) {                                                             \
    ASSERT_EQ(1, 2) << "Unable to create a process for the test";              \
    return;                                                                    \
  } else if (pid != 0) {                                                       \
    int status;                                                                \
    waitpid(pid, &status, 0);                                                  \
    ASSERT_EQ(WEXITSTATUS(status), 0) << "Test didn't exit successfully";      \
    ASSERT_EQ(WTERMSIG(status), 0) << "The program most likely segfaulted.";   \
    ASSERT_EQ(WIFSIGNALED(status), false) << "A signal was not caught";        \
    return;                                                                    \
  }

TEST(Lexer, SimpleTest) {
  ISOLATE_TEST();
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
  exit(EXIT_SUCCESS);
}

#define ADD_TOKEN(tp, lit, ln)                                                 \
  Token { .type = TokenType::tp, .literal = lit, .line = ln }

#define PUSH(tp, val, ln)                                                      \
  Token{.type = TokenType::Push, .literal = "push", .line = ln},                \
      Token{.type = TokenType::Word, .literal = tp, .line = ln},           \
      Token{.type = TokenType::LeftParen, .literal = "(", .line = ln},          \
      Token{.type = TokenType::Word, .literal = val, .line = ln},              \
      Token{.type = TokenType::RightParen, .literal = ")", .line = ln}

TEST(Parser, SubjectProgram) {
  ISOLATE_TEST();

  std::vector<Token> subject_tokens = {
			PUSH("int32", "32", 1),
      Token{.type = TokenType::Push, .literal = "push", .line = 1},
      Token{.type = TokenType::Word, .literal = "int32", .line = 1},
      Token{.type = TokenType::LeftParen, .literal = "(", .line = 1},
      Token{.type = TokenType::Word, .literal = "32", .line = 1},
      Token{.type = TokenType::RightParen, .literal = ")", .line = 1},

      Token{.type = TokenType::Sep, .literal = "<newline>", .line = 1},

      Token{.type = TokenType::Push, .literal = "push", .line = 2},
      Token{.type = TokenType::Word, .literal = "int32", .line = 2},
      Token{.type = TokenType::LeftParen, .literal = "(", .line = 2},
      Token{.type = TokenType::Word, .literal = "32", .line = 2},
      Token{.type = TokenType::RightParen, .literal = ")", .line = 2},

      Token{.type = TokenType::Sep, .literal = "<newline>", .line = 2},

      Token{.type = TokenType::Add, .literal = "add", .line = 3},

      Token{.type = TokenType::Push, .literal = "push", .line = 4},
      Token{.type = TokenType::Word, .literal = "float", .line = 4},
      Token{.type = TokenType::LeftParen, .literal = "(", .line = 4},
      Token{.type = TokenType::Word, .literal = "44.55", .line = 4},
      Token{.type = TokenType::RightParen, .literal = ")", .line = 4},

      Token{.type = TokenType::Sep, .literal = "<newline>", .line = 4},

      Token{.type = TokenType::Mul, .literal = "mul", .line = 5},

      // @clang-format off
  };
  // @clang-format on

  Parser parser;

  exit(EXIT_SUCCESS);
}

TEST(Lexer, Comment) {
  ISOLATE_TEST();
  Lexer lexer;
  auto tokens = lexer.lex("; Hello, this should be completely ignored");
  ASSERT_EQ(tokens.size(), (unsigned long)1);

  auto token = tokens[0];

  ASSERT_EQ(token.type, TokenType::Sep);
  ASSERT_EQ(token.line, 1);
  ASSERT_EQ(token.literal, "\n");
  exit(EXIT_SUCCESS);
}

#undef ISOLATE_TEST
