#pragma once
#include <exception>
#include "../avm-lexer/Token.hpp"

// TODO: inherit from std::runtime_error or std::logic_error (the former is better)
class ParserException : public std::exception {
public:
  enum class Type {
    SyntaxError,
    UnknownInstruction,
		Overflow,
		Underflow,
  };

  ParserException();
  ParserException(Type type, Token errorToken);
  ParserException(const ParserException &o);
  ParserException &operator=(const ParserException &o);
  ~ParserException();
  const char *what() const noexcept override;
  std::string getLineInfo() const;

private:
  Type type;
  Token errorToken;
};

std::string format_as(const ParserException::Type& t);
