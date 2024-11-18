SRCS	=	avm-lib/utils.cpp avm-exceptions/ParserException.cpp avm-exceptions/VmException.cpp avm-lexer/Lexer.cpp main.cpp avm-operand/OperandFactory.cpp avm-parser/Parser.cpp avm-virtual-machine/InputHandler.cpp avm-virtual-machine/Vm.cpp avm-lexer/Token.cpp avm-tests/tests.cpp avm-fmt/Formatter.cpp

HEADER = avm-arithmetic/checked_arithmetic.hpp  avm-exceptions/ParserException.hpp  avm-lexer/Token.hpp avm-operand/Operand.hpp avm-virtual-machine/InputHandler.hpp avm-lib/safe-math.h avm-exceptions/VmException.hpp avm-operand/IOperand.hpp avm-parser/Instruction.hpp avm-virtual-machine/Vm.hpp avm-lib/utils.hpp avm-lexer/Lexer.hpp  avm-operand/OperandFactory.hpp avm-parser/Parser.hpp avm-fmt/Formatter.hpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++17 -g -I$(DEPS)

DEPS = ./external-libs/include

STATIC_LIBS = ./external-libs/lib/libfmt.a ./external-libs/lib/libgtest.a

NAME	=	avm

CC	=	clang++

all: $(NAME)

$(NAME): $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIBS) -o $@

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS): scripts/install_dependencies.py
	@echo "Installing dependencies..."
	mkdir -p external-libs
	./scripts/install_dependencies.py

test: all
	. .venv/bin/activate
	ward -p avm-tests/ || echo "Make sure that DEBUG is not set for integration tests"

run: all
	./avm

clean:
	$(RM) $(OBJS)
	$(RM) -r external-libs

fclean: clean
	$(RM) $(NAME)
	$(RM) -r deps

pretty:
	clang++ -Xclang -ast-print -fsyntax-only $(SRCS)

re: fclean all

.PHONY: all clean fclean re
