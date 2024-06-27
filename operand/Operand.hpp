#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <cmath>
#include <sstream>
#include <type_traits>
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
  IOperand const *operator+(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (this->value + value);

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs + *this;
    }
  }
  IOperand const *operator-(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (this->value - value);

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs - *this;
    }
  }
  IOperand const *operator*(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (this->value * value);

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs * *this;
    }
  }
  IOperand const *operator/(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (this->value / value);

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs / *this;
    }
  }
  template <typename Integer,
            std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
  IOperand const *operator%(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (this->value % value);

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs % *this;
    }
  }
  template <
      typename Floating,
      std::enable_if_t<std::is_floating_point<Floating>::value, bool> = true>
  IOperand const *operator%(IOperand const &rhs) const {
    OperandFactory of;
    if (this->getPrecision() >= rhs.getPrecision()) {
      std::stringstream ss(rhs.toString());
      T value;

      ss >> value;
      ss << (fmod(this->value, value));

      std::string result;
      return of.createOperand(E, result);
    } else {
      return rhs % *this;
    }
  }
  std::string const &toString(void) const { return toStr; }
  ~Operand(void) {}
};
