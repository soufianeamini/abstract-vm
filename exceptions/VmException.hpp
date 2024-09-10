#pragma once
#include <exception>

class VmException : public std::exception {
public:
  enum Type {
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
