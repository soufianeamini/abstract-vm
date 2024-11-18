#pragma once

#include <string>
#include "../avm-operand/Operand.hpp"

struct VmValue {
	eOperandType type;
  std::string value;
};
