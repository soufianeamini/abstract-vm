#pragma once

#include "../lexer/Token.hpp"
#include <exception>

class ParserException : public std::exception {
public:
  enum class Type {
    SyntaxError,
    UnknownInstruction,
  };

  ParserException();
  ParserException(Type type, Token errorToken);
  ParserException(const ParserException &o);
  ParserException &operator=(const ParserException &o);
  ~ParserException();
  const char *what() const noexcept override;
  std::string getLineInfo() const;

private:
  Type type;
  Token errorToken;
};

class VmException : public std::exception {
public:
  enum class Type {
    Overflow,
    Underflow,
    EmptyStack,
    DivisionByZero,
    NoExitInstruction,
    Assert,
    TooFewStackValues,
  };

  VmException();
  VmException(Type type);
  VmException(const VmException &o);
  VmException &operator=(const VmException &o);
  ~VmException();
  const char *what() const noexcept override;

private:
  Type type;
};
