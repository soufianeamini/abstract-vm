#include "InputHandler.hpp"
#include <cctype>
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

static constexpr auto ctrlKey(char key) { return (key & 0x1f); }

static auto readKey() {
  char c{'\0'};
  read(STDIN_FILENO, &c, 1);
  return std::make_optional(c);
}

static constexpr auto enableRawMode(termios *old, termios *new1) {
  tcgetattr(STDIN_FILENO, old);
  new1->c_lflag &= ~(ICRNL | IXON);
  new1->c_lflag &= ~(OPOST);
  new1->c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  new1->c_cc[VMIN] = 0;
  new1->c_cc[VTIME] = 1; // in tenths of a second e.g 1 => 100ms of timeout

  tcsetattr(STDIN_FILENO, TCSAFLUSH, new1);
}

static constexpr auto disableRawMode(termios *old) {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, old);
}

auto InputHandler::readLine() -> decltype(readLine()) {
  // This function should only return at the last statement
  std::string line{};
  enableRawMode(&old, &new1);

  while (1) {
    auto r{readKey()};

    if (!r.has_value()) {
      // TODO: remove printing
      fmt::println(stderr, "error: read()");
      break;
    }
    auto c = *r;

    if (!std::iscntrl(c)) {
      fmt::println("c: {}\r", c);
    } else {
      fmt::println("c: {}, code: {}\r", c, static_cast<int>(c));
    }
    if (c == ctrlKey('c')) {
      break;
    }
  }

  disableRawMode(&old);
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
