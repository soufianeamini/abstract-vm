#pragma once

#include <optional>
#include <string>
namespace InputHandler {
std::string readFile(const std::string &filename);
std::optional<std::string> readLine();
}
