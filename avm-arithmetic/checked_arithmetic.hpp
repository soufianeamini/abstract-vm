#pragma once
#include "../avm-lib/safe-math.h"
#include <cstdint>
#include <limits>

static_assert(std::numeric_limits<float>::has_infinity,
              "infinity is not supported on this platform!");
static_assert(std::numeric_limits<double>::has_infinity,
              "infinity is not supported on this platform!");

enum class CheckedArithmeticResult {
  CA_SUCCESS,
  CA_OVERFLOW,
  CA_UNDERFLOW,
  CA_INVALID
};

namespace checked_arithmetic {
template <class T> CheckedArithmeticResult checked_add(T *res, T a, T b) {
  static_assert(sizeof(T) == -1,
                "checked_arithmetic was not implemented for a type.");
  return CheckedArithmeticResult::CA_INVALID;
}

template <class T> CheckedArithmeticResult checked_sub(T *res, T a, T b) {
  static_assert(sizeof(T) == -1,
                "checked_arithmetic was not implemented for a type.");
  return CheckedArithmeticResult::CA_INVALID;
}

template <class T> CheckedArithmeticResult checked_mul(T *res, T a, T b) {
  static_assert(sizeof(T) == -1,
                "checked_arithmetic was not implemented for a type.");
  return CheckedArithmeticResult::CA_INVALID;
}

template <class T> CheckedArithmeticResult checked_div(T *res, T a, T b) {
  static_assert(sizeof(T) == -1,
                "checked_arithmetic was not implemented for a type.");
  return CheckedArithmeticResult::CA_INVALID;
}
} // namespace checked_arithmetic

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_add<int8_t>(int8_t *res, int8_t a, int8_t b) {

  if (psnip_safe_int8_add(res, a, b)) {
    if ((a < 0) == (b < 0))
      return CheckedArithmeticResult::CA_OVERFLOW;
    else
      return CheckedArithmeticResult::CA_UNDERFLOW;
  }
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_sub<int8_t>(int8_t *res, int8_t a, int8_t b) {
  if (psnip_safe_int8_sub(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_mul<int8_t>(int8_t *res, int8_t a, int8_t b) {
  if (psnip_safe_int8_mul(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_div<int8_t>(int8_t *res, int8_t a, int8_t b) {
  if (psnip_safe_int8_div(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_add<int16_t>(int16_t *res, int16_t a, int16_t b) {
  if (psnip_safe_int16_add(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_sub<int16_t>(int16_t *res, int16_t a, int16_t b) {
  if (psnip_safe_int16_sub(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_mul<int16_t>(int16_t *res, int16_t a, int16_t b) {
  if (psnip_safe_int16_mul(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_div<int16_t>(int16_t *res, int16_t a, int16_t b) {
  if (psnip_safe_int16_div(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_add<int32_t>(int32_t *res, int32_t a, int32_t b) {
  if (psnip_safe_int32_add(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_sub<int32_t>(int32_t *res, int32_t a, int32_t b) {
  if (psnip_safe_int32_sub(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_mul<int32_t>(int32_t *res, int32_t a, int32_t b) {
  if (psnip_safe_int32_mul(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_div<int32_t>(int32_t *res, int32_t a, int32_t b) {
  if (psnip_safe_int32_div(res, a, b))
    return CheckedArithmeticResult::CA_OVERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_add<float>(float *res, float a, float b) {
  *res = a + b;
  if (*res == std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_sub<float>(float *res, float a, float b) {
  *res = a - b;
  if (*res == std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_mul<float>(float *res, float a, float b) {
  *res = a * b;
  if (*res == std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_div<float>(float *res, float a, float b) {
  *res = a / b;
  if (*res == std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<float>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_add<double>(double *res, double a, double b) {
  *res = a + b;
  if (*res == std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_sub<double>(double *res, double a, double b) {
  *res = a - b;
  if (*res == std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_mul<double>(double *res, double a, double b) {
  *res = a * b;
  if (*res == std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}

template <>
inline CheckedArithmeticResult
checked_arithmetic::checked_div<double>(double *res, double a, double b) {
  *res = a / b;
  if (*res == std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_OVERFLOW;
  if (*res == -std::numeric_limits<double>::infinity())
    return CheckedArithmeticResult::CA_UNDERFLOW;
  return CheckedArithmeticResult::CA_SUCCESS;
}
