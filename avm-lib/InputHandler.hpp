#pragma once

#include <optional>
#include <string>
#include <vector>
class InputHandler {
private:
  std::vector<std::string> history{};

public:
  static std::string readFile(const std::string &filename);
  std::optional<std::string> readLine();
  // TODO: add constructors
  ~InputHandler();
};
