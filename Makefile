SRCS	=	avm-lib/utils.cpp exceptions/ParserException.cpp exceptions/VmException.cpp lexer/Lexer.cpp main.cpp operand/OperandFactory.cpp parser/Parser.cpp vm/InputHandler.cpp vm/Vm.cpp lexer/Token.cpp

HEADER = avm-arithmetic/checked_arithmetic.hpp  exceptions/ParserException.hpp  lexer/Token.hpp operand/Operand.hpp vm/InputHandler.hpp avm-lib/safe-math.h exceptions/VmException.hpp operand/IOperand.hpp parser/Instruction.hpp vm/Vm.hpp avm-lib/utils.hpp lexer/Lexer.hpp  operand/OperandFactory.hpp parser/Parser.hpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++17 -g -I$(DEPS)

DEPS = ./external-libs/include

STATIC_LIBS = ./external-libs/lib/libfmt.a

NAME	=	avm

CC	=	clang++

all: $(NAME)

$(NAME): $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIBS) -o $@

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS):
	@echo "Installing dependencies..."
	mkdir -p external-libs
	./scripts/install_dependencies.py

test: all
	cargo test --lib

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
