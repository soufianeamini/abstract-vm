#include "Operand.hpp"
#include "IOperand.hpp"

template <eOperandType E, class T>
eOperandType Operand<E, T>::getType(void) const {
  return E;
}

template <eOperandType E, class T>
IOperand const *Operand<E, T>::operator+(IOperand const &rhs) const {}
