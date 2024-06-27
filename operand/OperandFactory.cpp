
#include "OperandFactory.hpp"
#include "IOperand.hpp"
#include <memory>
#include <utility>

std::vector<std::unique_ptr<const IOperand>> OperandFactory::operands;

IOperand const *OperandFactory::createOperand(eOperandType type,
                                              std::string const &value) const {
  std::function<IOperand const *(const OperandFactory *, std::string const &)>
      function = createFunctions[std::to_underlying(type)];

  const IOperand *operand = function(this, value);
  std::unique_ptr<const IOperand> ptr(operand);
  operands.emplace_back(std::move(ptr));
  return operand;
}

// IOperand const *OperandFactory::createInt8(std::string const &value) const {}
// IOperand const *OperandFactory::createInt16(std::string const &value) const
// {} IOperand const *OperandFactory::createInt32(std::string const &value)
// const {} IOperand const *OperandFactory::createFloat(std::string const
// &value) const {} IOperand const *OperandFactory::createDouble(std::string
// const &value) const {}
