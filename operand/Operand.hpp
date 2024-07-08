#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <cmath>
#include <print>
#include <sstream>
#include <string>
#include <utility>
template <eOperandType E, class T> class Operand : public IOperand {
private:
  T value;
  std::string toStr;

public:
  Operand() {}
  Operand(const std::string &value) : toStr(value) {
    this->value = std::stoi(value);
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

      return of.createOperand(E, std::to_string(this->value + value));
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

      return of.createOperand(E, std::to_string(this->value - value));
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

      return of.createOperand(E, std::to_string(this->value * value));
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

      return of.createOperand(E, std::to_string(this->value / value));
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

      return of.createOperand(E, std::to_string(this->value % value));
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

    return of.createOperand(eOperandType::Double,
                            std::to_string(fmod(this->value, value)));
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

    return of.createOperand(eOperandType::Float,
                            std::to_string(fmod(this->value, value)));
  } else {
    return rhs % *this;
  }
}

template <>
inline Operand<eOperandType::Float, float>::Operand(const std::string &value)
    : toStr(value) {
  this->value = std::stof(value);
}

template <>
inline Operand<eOperandType::Double, double>::Operand(const std::string &value)
    : toStr(value) {
  this->value = std::stod(value);
}

// overflow checks 
//
// #include <limits>

// unsigned int a, b;  // from somewhere

// unsigned int diff = std::numeric_limits<unsigned int>::max() - a;

// if (diff < b) { /* error, cannot add a + b */ }
