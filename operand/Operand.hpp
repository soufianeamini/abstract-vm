#include "IOperand.hpp"
template <eOperandType E> class Operand : IOperand {
  eOperandType getType(void) const;
};
