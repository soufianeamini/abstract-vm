#include "IOperand.hpp"
#include <sstream>
#include <utility>
template <eOperandType E, class T> class Operand : public IOperand {
private:
  T value;
  std::string toStr;

public:
  Operand() {}
  Operand(const std::string &value) : toStr(value) {
    std::stringstream ss(value);
    ss >> this->value;
  }
  Operand(const Operand &o) : value(o.value), toStr(o.toStr) {}
  Operand &operator=(const Operand &o) {
    if (this == &o)
      return *this;

    value = o.value;
    toStr = o.toStr;

    return *this;
  }
  int getPrecision(void) const { return std::to_underlying(E); }
  eOperandType getType(void) const { return E; }
  IOperand const *operator+(IOperand const &rhs) const;
  IOperand const *operator-(IOperand const &rhs) const;
  IOperand const *operator*(IOperand const &rhs) const;
  IOperand const *operator/(IOperand const &rhs) const;
  IOperand const *operator%(IOperand const &rhs) const;
  std::string const &toString(void) const { return toStr; }
  ~Operand(void) {}
};
