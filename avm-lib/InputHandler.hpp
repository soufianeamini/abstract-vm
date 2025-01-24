#pragma once

#include <optional>
#include <string>
#include <termios.h>
#include <vector>
class InputHandler {
private:
  std::vector<std::string> history{};
  termios old{};
  termios new1{};

public:
  static std::string readFile(const std::string &filename);
  std::optional<std::string> readLine();
  InputHandler();
  InputHandler &operator=(const InputHandler &other);
  InputHandler(const InputHandler &other);
  ~InputHandler();
};
