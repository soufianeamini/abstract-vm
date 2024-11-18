#include "../lexer/Lexer.hpp"
#include "../parser/Parser.hpp"
#include "../vm/Vm.hpp"
#include <cstdlib>
#include <fmt/base.h>
#include <fmt/format.h>
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

#define TOKEN(tp, lit, ln)                                                     \
  Token { .type = TokenType::tp, .literal = lit, .line = ln }

#define SEP(ln) TOKEN(Sep, "\n", ln)
#define ADD(ln) TOKEN(Add, "add", ln), SEP(ln)
#define MUL(ln) TOKEN(Mul, "mul", ln), SEP(ln)
#define DUMP(ln) TOKEN(Dump, "dump", ln), SEP(ln)
#define POP(ln) TOKEN(Pop, "pop", ln), SEP(ln)
#define EXIT(ln) TOKEN(Exit, "exit", ln), SEP(ln)
#define PUSH(tp, val, ln)                                                      \
  Token{.type = TokenType::Push, .literal = "push", .line = ln},               \
      Token{.type = TokenType::Word, .literal = tp, .line = ln},               \
      Token{.type = TokenType::LeftParen, .literal = "(", .line = ln},         \
      Token{.type = TokenType::Word, .literal = val, .line = ln},              \
      Token{.type = TokenType::RightParen, .literal = ")", .line = ln},        \
      SEP(ln)
#define ASSERT(tp, val, ln)                                                    \
  Token{.type = TokenType::Assert, .literal = "assert", .line = ln},           \
      Token{.type = TokenType::Word, .literal = tp, .line = ln},               \
      Token{.type = TokenType::LeftParen, .literal = "(", .line = ln},         \
      Token{.type = TokenType::Word, .literal = val, .line = ln},              \
      Token{.type = TokenType::RightParen, .literal = ")", .line = ln},        \
      SEP(ln)

TEST(Lexer, SimpleTest) {
  ISOLATE_TEST();
  Lexer lexer;

  auto tokens = lexer.lex("push int8(32)\n");

  std::vector<Token> test_tokens = {
      PUSH("int8", "32", 1),
  };

  for (unsigned int i = 0; i < test_tokens.size(); i++) {
    auto a = tokens[i];
    auto b = test_tokens[i];

    ASSERT_EQ(a.type, b.type);
    ASSERT_EQ(a.literal, b.literal);
    ASSERT_EQ(a.line, b.line);
  }
  exit(EXIT_SUCCESS);
}

TEST(Lexer, SubjectProgram) {
  ISOLATE_TEST();

  std::string input = std::string("push int32(42)\n") + "push int32(33)\n" +
                      "add\n" + "push float(44.55)\n" + "mul\n" +
                      "push double(42.42)\n" + "push int32(42)\n" + "dump\n" +
                      "pop\n" + "assert double(42.42)\n" + "exit\n" + ";;";

  std::vector<Token> test_tokens = {
      PUSH("int32", "42", 1),
      PUSH("int32", "33", 2),
      ADD(3),
      PUSH("float", "44.55", 4),
      MUL(5),
      PUSH("double", "42.42", 6),
      PUSH("int32", "42", 7),
      DUMP(8),
      POP(9),
      ASSERT("double", "42.42", 10),
      EXIT(11),
  };
  Lexer lexer;

  auto tokens = lexer.lex(input);

  for (unsigned int i = 0; i < test_tokens.size(); i++) {
    auto a = tokens[i];
    auto b = test_tokens[i];

    ASSERT_EQ(a.type, b.type) << fmt::format("a: {}, b: {}", a, b);
    ASSERT_EQ(a.literal, b.literal) << fmt::format("a: {}, b: {}", a, b);
    ASSERT_EQ(a.line, b.line) << fmt::format("a: {}, b: {}", a, b);
  }

  exit(EXIT_SUCCESS);
}

TEST(Parser, SubjectProgram) {
  ISOLATE_TEST();

  std::vector<Token> subject_tokens = {
      PUSH("int32", "42", 1),
      PUSH("int32", "33", 2),
      ADD(3),
      PUSH("float", "44.55", 4),
      MUL(5),
      PUSH("double", "42", 6),
      PUSH("int32", "42", 7),
      DUMP(8),
      POP(9),
      ASSERT("double", "42.42", 10),
      EXIT(11),
  };

  std::vector<Instruction> test_instructions = {
      // clang-format off
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "42"}},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "33"}},
		Instruction{.command = TokenType::Add, .value = VmValue()},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Float, .value = "44.55"}},
		Instruction{.command = TokenType::Mul, .value = VmValue()},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Double, .value = "42"}},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "42"}},
		Instruction{.command = TokenType::Dump, .value = VmValue()},
		Instruction{.command = TokenType::Pop, .value = VmValue()},
		Instruction{.command = TokenType::Assert, .value = VmValue{.type = eOperandType::Double, .value = "42.42"}},
		Instruction{.command = TokenType::Exit, .value = VmValue()},
      // clang-format on
  };

  Parser parser(subject_tokens);
  std::vector<Instruction> instructions = parser.parse(false);

  ASSERT_EQ(instructions.size(), test_instructions.size());

  for (unsigned int i = 0; i < instructions.size(); i++) {
    auto a = instructions[i];
    auto b = test_instructions[i];

    ASSERT_EQ(a.value.value, b.value.value);
    ASSERT_EQ(a.value.type, b.value.type);
    ASSERT_EQ(a.command, b.command);
  }

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

TEST(VirtualMachine, SubjectProgram) {
  ISOLATE_TEST();

  std::vector<Instruction> test_instructions = {
      // clang-format off
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "42"}},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "33"}},
		Instruction{.command = TokenType::Add, .value = VmValue()},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Float, .value = "44.55"}},
		Instruction{.command = TokenType::Mul, .value = VmValue()},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Double, .value = "42.42"}},
		Instruction{.command = TokenType::Push, .value = VmValue{.type = eOperandType::Int32, .value = "42"}},
		Instruction{.command = TokenType::Dump, .value = VmValue()},
		Instruction{.command = TokenType::Pop, .value = VmValue()},
		Instruction{.command = TokenType::Assert, .value = VmValue{.type = eOperandType::Double, .value = "42.42"}},
		Instruction{.command = TokenType::Exit, .value = VmValue()},
      // clang-format on
  };

  Vm vm(test_instructions);
  vm.interpret();
  std::string actual = vm.getOutput();

  std::string expected = "42\n42.42\n3341.25\n";
  ASSERT_EQ(expected, actual);

  exit(EXIT_SUCCESS);
}

TEST(Parser, InvalidNumbers) {
  ISOLATE_TEST();
  Parser parser;

  std::vector<Token> tokens = {
      PUSH("int32", "42.2", 1),
  };

  exit(EXIT_SUCCESS);
}

// TODO: Test invalid string numbers
// TODO: Test ParserExceptions
// TODO: Test VmExceptions

#undef ISOLATE_TEST
