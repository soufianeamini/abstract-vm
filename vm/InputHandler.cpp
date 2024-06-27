#include <fstream>
#include <sstream>
namespace InputHandler {
std::string ReadFile(const std::string &filename) {
  std::fstream file(filename);
  std::stringstream ss;

  ss << file.rdbuf();
  std::string content(ss.str());

  return content;
}
} // namespace InputHandler
