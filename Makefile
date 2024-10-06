SRCS	=	main.cpp lexer/Lexer.cpp parser/Parser.cpp vm/InputHandler.cpp \
				operand/OperandFactory.cpp exceptions/ParserException.cpp\
				vm/Vm.cpp exceptions/VmException.cpp avm-lib/utils.cpp

HEADER	= parser/Instruction.hpp parser/Parser.hpp lexer/Lexer.hpp lexer/Token.hpp exceptions/ParserException.hpp vm/Vm.hpp vm/InputHandler.hpp \
					operand/IOperand.hpp operand/Operand.hpp operand/OperandFactory.hpp exceptions/VmException.hpp \
					avm-lib/utils.hpp avm-arithmetic/checked_arithmetic.hpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++17 -g -I$(DEPS)

DEPS = external-libs/include

STATIC_LIBS = external-libs/lib/libfmt.a

NAME	=	avm

CC	=	clang++

all: $(NAME)

$(NAME): $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIBS) -o $@ 

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS):
	echo "Installing dependencies... This can take a few minutes"
	mkdir -p external-libs
	./scripts/install_dependencies.py

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

pretty:
	clang++ -Xclang -ast-print -fsyntax-only $(SRCS)

re: fclean all

.PHONY: all clean fclean re
