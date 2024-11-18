#pragma once
#include <exception>
#include <string>

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

std::string format_as(const VmException::Type& t);
