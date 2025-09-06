#include "InputHandler.hpp"
#include <fmt/base.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>

std::string InputHandler::readFile(const std::string &filename) {
  std::fstream file{filename};

  if (!file) {
    throw std::runtime_error("invalid file name: " + filename);
  }

  std::stringstream ss{};

  ss << file.rdbuf();
  std::string content(ss.str() + "\n");

  return content;
}

auto InputHandler::readLine() -> decltype(readLine()) {
  // This function should only return at the last statement
  std::string line{};
  // TODO: error handling
  std::getline(std::cin, line);
  return std::make_optional(line);
}

InputHandler::InputHandler() {}
InputHandler::InputHandler(const InputHandler &o)
    : history{o.history}, old{o.old}, new1{o.new1} {}
InputHandler &InputHandler::operator=(const InputHandler &o) {
  if (&o == this) {
    return *this;
  }

  this->history = o.history;
  this->old = o.old;
  this->new1 = o.new1;

  return *this;
}
InputHandler::~InputHandler() {}
