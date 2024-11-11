#include "../lexer/Lexer.hpp"
#include <cstdlib>
#include <gtest/gtest.h>
#include <iostream>
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

TEST(Lexer, Comment) {
  ISOLATE_TEST();
  std::cout << "Inside thread\n";
  Lexer lexer;

  std::cout << "Before calling lexer" << std::endl;
  auto tokens = lexer.lex("; Hello, this should be completely ignored");
  std::cout << "After calling lexer" << std::endl;

  ASSERT_EQ(tokens.size(), (unsigned long)0);
  exit(EXIT_SUCCESS);
}

#undef ISOLATE_TEST
