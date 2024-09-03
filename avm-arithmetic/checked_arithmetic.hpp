#include "../avm-lib/safe-math.h"
#include <cstdint>
#include <stdexcept>

namespace checked_arithmetic {
template <class T> bool checked_add(T *res, T a, T b) {
  throw std::runtime_error(
      "checked_arithmetic was not implemented for a type.");
}

template <class T> bool checked_sub(T *res, T a, T b) {
  throw std::runtime_error(
      "checked_arithmetic was not implemented for a type.");
}

template <class T> bool checked_mul(T *res, T a, T b) {
  throw std::runtime_error(
      "checked_arithmetic was not implemented for a type.");
}

template <class T> bool checked_div(T *res, T a, T b) {
  throw std::runtime_error(
      "checked_arithmetic was not implemented for a type.");
}
} // namespace checked_arithmetic

template <>
inline bool checked_arithmetic::checked_add<int8_t>(int8_t *res, int8_t a,
                                                    int8_t b) {
  return psnip_safe_int8_add(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_sub<int8_t>(int8_t *res, int8_t a,
                                                    int8_t b) {
  return psnip_safe_int8_sub(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_mul<int8_t>(int8_t *res, int8_t a,
                                                    int8_t b) {
  return psnip_safe_int8_mul(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_div<int8_t>(int8_t *res, int8_t a,
                                                    int8_t b) {
  return psnip_safe_int8_div(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_add<int16_t>(int16_t *res, int16_t a,
                                                     int16_t b) {
  return psnip_safe_int16_add(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_sub<int16_t>(int16_t *res, int16_t a,
                                                     int16_t b) {
  return psnip_safe_int16_sub(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_mul<int16_t>(int16_t *res, int16_t a,
                                                     int16_t b) {
  return psnip_safe_int16_mul(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_div<int16_t>(int16_t *res, int16_t a,
                                                     int16_t b) {
  return psnip_safe_int16_div(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_add<int32_t>(int32_t *res, int32_t a,
                                                     int32_t b) {
  return psnip_safe_int32_add(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_sub<int32_t>(int32_t *res, int32_t a,
                                                     int32_t b) {
  return psnip_safe_int32_sub(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_mul<int32_t>(int32_t *res, int32_t a,
                                                     int32_t b) {
  return psnip_safe_int32_mul(res, a, b);
}

template <>
inline bool checked_arithmetic::checked_div<int32_t>(int32_t *res, int32_t a,
                                                     int32_t b) {
  return psnip_safe_int32_div(res, a, b);
}
