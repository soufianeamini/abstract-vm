cmake_minimum_required(VERSION 4.2)

project(
	abstract-vm
	VERSION 1.0.0
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(avm)
add_library(avm-arithmetic INTERFACE)
add_library(avm-exceptions)
add_library(avm-fmt)
add_library(avm-lexer)
add_library(avm-lib)
add_library(avm-operand)
add_library(avm-parser)
add_library(avm-virtual-machine)

target_link_libraries(avm avm-parser avm-fmt avm-lexer avm-lib avm-virtual-machine)
target_link_libraries(avm-virtual-machine avm-exceptions)
target_link_libraries(avm-parser avm-operand)

target_sources(avm PUBLIC main.cpp)
target_sources(
	avm-arithmetic 
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-arithmetic/
	FILES avm-arithmetic/checked_arithmetic.hpp
)
target_sources(
	avm-exceptions
	PRIVATE avm-exceptions/ParserException.cpp avm-exceptions/VmException.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-exceptions/
	FILES avm-exceptions/ParserException.hpp avm-exceptions/VmException.hpp
)
target_sources(
	avm-fmt
	PRIVATE avm-fmt/Formatter.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-fmt/
	FILES avm-fmt/Formatter.hpp
)
target_sources(
	avm-lexer
	PRIVATE avm-lexer/Lexer.cpp avm-lexer/Token.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-lexer/
	FILES avm-lexer/Lexer.hpp avm-lexer/Token.hpp
)
target_sources(
	avm-lib
	PRIVATE avm-lib/InputHandler.cpp avm-lib/utils.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-lib/
	FILES avm-lib/InputHandler.hpp avm-lib/utils.hpp avm-lib/safe-math.h
)
target_sources(
	avm-operand
	PRIVATE avm-operand/OperandFactory.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-operand/
	FILES avm-operand/IOperand.hpp avm-operand/Operand.hpp avm-operand/OperandFactory.hpp
)
target_sources(
	avm-parser
	PRIVATE avm-parser/Parser.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-parser/
	FILES avm-parser/Instruction.hpp avm-parser/Parser.hpp avm-parser/VmValue.hpp
)
target_sources(
	avm-virtual-machine
	PRIVATE avm-virtual-machine/Vm.cpp
	PUBLIC
	FILE_SET HEADERS
	BASE_DIRS avm-virtual-machine/
	FILES avm-virtual-machine/Vm.hpp
)

# dependencies
## fmt
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        407c905e45ad75fc29bf0f9bb7c5c2fd3475976f) # 12.1.0
FetchContent_MakeAvailable(fmt)

target_link_libraries(avm-operand fmt::fmt)
target_link_libraries(avm-lib fmt::fmt)
target_link_libraries(avm-lexer fmt::fmt)
target_link_libraries(avm-exceptions fmt::fmt)
target_link_libraries(avm-fmt fmt::fmt)

## gtest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip # 1.17.0
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(avm gtest_main)
