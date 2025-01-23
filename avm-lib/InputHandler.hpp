#pragma once

#include <optional>
#include <string>
class InputHandler {
public:
  static std::string readFile(const std::string &filename);
  std::optional<std::string> readLine();
};
