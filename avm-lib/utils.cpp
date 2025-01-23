#include "utils.hpp"
#include <cctype>

namespace utils {
bool is_valid_number(const std::string &value) {
  bool has_dot = false;
  for (std::string::const_iterator it = value.cbegin(); it != value.cend();
       ++it) {
    if (it == value.cbegin() && (*it == '+' || *it == '-'))
      continue;
    if (*it == '.') {
      if (has_dot)
        return false;
      has_dot = true;
      continue;
    }
    if (!std::isdigit(*it))
      return false;
  }

  return true;
}
} // namespace utils
