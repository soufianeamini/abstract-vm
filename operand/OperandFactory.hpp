#pragma once

#include "IOperand.hpp"
#include <array>
#include <functional>
class OperandFactory {
private:
  std::array<std::function<IOperand const *(const OperandFactory *,
                                            std::string const &)>,
             5>
      createFunctions{
          &OperandFactory::createInt8,   &OperandFactory::createInt16,
          &OperandFactory::createInt32,  &OperandFactory::createFloat,
          &OperandFactory::createDouble,
      };

  IOperand const *createInt8(std::string const &value) const;
  IOperand const *createInt16(std::string const &value) const;
  IOperand const *createInt32(std::string const &value) const;
  IOperand const *createFloat(std::string const &value) const;
  IOperand const *createDouble(std::string const &value) const;

public:
  IOperand const *createOperand(eOperandType type,
                                std::string const &value) const;
};
