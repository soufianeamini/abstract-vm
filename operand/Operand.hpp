#include "IOperand.hpp"
template <eOperandType E, class T> class Operand : IOperand {
public:
  int getPrecision(void) const;
  eOperandType getType(void) const;
  IOperand const *operator+(IOperand const &rhs) const;
  IOperand const *operator-(IOperand const &rhs) const;
  IOperand const *operator*(IOperand const &rhs) const;
  IOperand const *operator/(IOperand const &rhs) const;
  IOperand const *operator%(IOperand const &rhs) const;
  std::string const &toString(void) const;
  ~Operand(void) {}
};

// Example specialization:
//
// Operand<Int8, int8_t>;
//
// For creating Operands, a OperandFactory is needed
