#include "Operand.hpp"
#include "IOperand.hpp"
#include <sstream>

template <eOperandType E, class T>
eOperandType Operand<E, T>::getType(void) const {
  return E;
}

template <eOperandType E, class T>
Operand<E, T>::Operand(const std::string &value) {
  std::stringstream ss(value);

  ss >> this->value;
}

// template <eOperandType E, class T>
// IOperand const *Operand<E, T>::operator+(IOperand const &rhs) const {}
