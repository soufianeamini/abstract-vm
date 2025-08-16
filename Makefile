SRCS = main.cpp $(wildcard avm-*/*.cpp)

HEADER = $(wildcard avm-*/*.h) $(wildcard avm-*/*.hpp)

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
	ward -p avm-tests/ || echo "Make sure that 'test_mode' is set to 'false' for integration tests"

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
