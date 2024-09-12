SRCS	=	main.cpp lexer/Lexer.cpp parser/Parser.cpp vm/InputHandler.cpp \
				operand/OperandFactory.cpp exceptions/ParserException.cpp\
				vm/Vm.cpp exceptions/VmException.cpp avm-lib/utils.cpp

HEADER	= lexer/Lexer.hpp lexer/Token.hpp exceptions/ParserException.hpp vm/Vm.hpp vm/InputHandler.hpp \
					operand/IOperand.hpp operand/Operand.hpp operand/OperandFactory.hpp exceptions/VmException.hpp \
					avm-lib/utils.hpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++17 -g

NAME	=	avm

CC	=	clang++

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

pretty:
	clang++ -Xclang -ast-print -fsyntax-only $(SRCS)

re: fclean all

.PHONY: all clean fclean re
