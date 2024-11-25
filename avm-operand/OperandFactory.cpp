#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include <cstdint>
#include <fmt/format.h>

IOperand const *OperandFactory::createOperand(eOperandType type,
                                              std::string const &value) const {
  std::function<IOperand const *(const OperandFactory *, std::string const &)>
      createOp = createFunctions[fmt::underlying(type)];

  const IOperand *operand = createOp(this, value);
  return operand;
}

IOperand const *OperandFactory::createInt8(std::string const &value) const {
  return new Operand<eOperandType::Int8, int8_t>(value);
}

IOperand const *OperandFactory::createInt16(std::string const &value) const {
  return new Operand<eOperandType::Int16, int16_t>(value);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const {
  return new Operand<eOperandType::Int32, int32_t>(value);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const {
  return new Operand<eOperandType::Float, float>(value);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const {
  return new Operand<eOperandType::Double, double>(value);
}

std::string format_as(const IOperand &op) {
  return fmt::format("Operand {{ Op: {}, value: {} }}",
                     fmt::underlying(op.getType()), op.toString());
}
