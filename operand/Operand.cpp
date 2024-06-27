#include "Operand.hpp"
#include "IOperand.hpp"
template <eOperandType E> eOperandType Operand<E>::getType(void) const {
  return E;
}
