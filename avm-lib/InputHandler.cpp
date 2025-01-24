#include "InputHandler.hpp"
#include <cstdio>
#include <cstdlib>
#include <fmt/base.h>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <termios.h>
#include <unistd.h>

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
  const static auto enableRawMode = [this]() {
    tcgetattr(STDIN_FILENO, &old);
    new1.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new1);
  };

  const static auto disableRawMode = [this]() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
  };
  std::string line{};

  // TODO: Use something that allows you to capture arrow keys
  // if (std::getline(std::cin, line)) {
  //   if (!line.empty()) {
  //     history.push_back(line);
  //   }
  //   return line;
  // }

  enableRawMode();

  char c{};
  char old{};

  while (1) {
    read(STDIN_FILENO, &c, 1);
    if (c != old && c != 127) {
      // fmt::print("char: {}, code: {}", c, static_cast<int>(c));
      // std::flush(std::cout);
    }
    if (c != old && c == 127) {
      fmt::print("\b \b");
    }
    if (c == 'q') {
      break;
    }
    old = c;
  }
  disableRawMode();

  return std::nullopt;
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
