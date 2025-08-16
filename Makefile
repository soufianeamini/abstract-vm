SRCS = main.cpp $(wildcard avm-*/*.cpp)

HEADER = $(wildcard avm-*/*.h) $(wildcard avm-*/*.hpp)

OBJS	=	$(SRCS:.cpp=.o)

DEPS = ./external-libs/include

CFLAGS	=	-Wall -Wextra -Werror -std=c++17 -g -I$(DEPS)

STATIC_LIBS = ./external-libs/lib/libfmt.a ./external-libs/lib/libgtest.a

NAME	=	avm

CC	=	clang++

all: $(NAME)

VENV = .venv

PYTEST = .venv/bin/pytest

$(NAME): $(DEPS) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_LIBS) -o $@

%.o:	%.cpp $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS): scripts/install_dependencies.py
	@echo "Installing dependencies..."
	mkdir -p external-libs
	./scripts/install_dependencies.py

test: all $(VENV) $(PYTEST)
	.venv/bin/pytest avm-tests/ || echo "Make sure that 'test_mode' is set to 'false' for integration tests"

$(VENV):
	uv venv

$(PYTEST):
	uv pip install pytest

run: all
	./avm

clean:
	$(RM) $(OBJS)
	$(RM) -r external-libs

fclean: clean
	$(RM) $(NAME)
	$(RM) -r deps
	$(RM) -r $(VENV)

pretty:
	clang++ -Xclang -ast-print -fsyntax-only $(SRCS)

re: fclean all

.PHONY: all clean fclean re
