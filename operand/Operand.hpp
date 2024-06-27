#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <cmath>
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
  std::string const &toString(void) const { return toStr; }
  ~Operand(void) {}
};

template <>
inline IOperand const *
Operand<eOperandType::Double, double>::operator%(IOperand const &rhs) const {
  OperandFactory of;
  if (this->getPrecision() >= rhs.getPrecision()) {
    std::stringstream ss(rhs.toString());
    double value;

    ss >> value;
    ss << fmod(this->value, value);

    std::string result;
    return of.createOperand(eOperandType::Double, result);
  } else {
    return rhs % *this;
  }
}

template <>
inline IOperand const *
Operand<eOperandType::Float, float>::operator%(IOperand const &rhs) const {
  OperandFactory of;
  if (this->getPrecision() >= rhs.getPrecision()) {
    std::stringstream ss(rhs.toString());
    float value;

    ss >> value;
    ss << fmod(this->value, value);

    std::string result;
    return of.createOperand(eOperandType::Float, result);
  } else {
    return rhs % *this;
  }
}
