#pragma once

#include <optional>
#include <string>
namespace InputHandler {
std::string ReadFile(const std::string &filename);
std::optional<std::string> ReadLine();
}
