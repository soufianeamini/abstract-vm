SRCS	=	main.cpp lexer/Lexer.cpp

OBJS	=	$(SRCS:.cpp=.o)

CFLAGS	=	-Wall -Wextra -Werror -std=c++23

NAME	=	avm

CC	=	c++

HEADER	= abstract-vm.hpp

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
