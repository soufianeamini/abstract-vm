#include "InputHandler.hpp"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>

std::string InputHandler::readFile(const std::string &filename) {
  std::fstream file{filename};

  if (!file) {
    throw std::runtime_error("invalid file name: " + filename);
  }

  std::stringstream ss{};

  ss << file.rdbuf();
  std::string content(ss.str());

  return content;
}

std::optional<std::string> InputHandler::readLine() {
  std::string line{};

	// TODO: Use something that allows you to capture arrow keys
  if (std::getline(std::cin, line)) {
    if (!line.empty()) {
      history.push_back(line);
    }
    return line;
  }

  return std::nullopt;
}
