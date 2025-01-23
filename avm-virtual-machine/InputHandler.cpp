#include "InputHandler.hpp"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

// TODO: Transform into class to add history handling later
namespace InputHandler {
std::string readFile(const std::string &filename) {
  std::fstream file(filename);

  if (!file) {
    throw std::runtime_error("invalid file name: " + filename);
  }

  std::stringstream ss;

  ss << file.rdbuf();
  std::string content(ss.str());

  return content;
}

std::optional<std::string> readLine() {
  std::string line;

  if (std::getline(std::cin, line)) {
    return line;
  }

  return std::nullopt;
}
} // namespace InputHandler
