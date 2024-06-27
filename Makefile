SRCS	=	main.cpp lexer/Lexer.cpp parser/Parser.cpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++23

NAME	=	avm

CC	=	c++

HEADER	= lexer/Lexer.hpp lexer/Token.hpp exceptions/LexerException.hpp vm/Vm.hpp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ 

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
