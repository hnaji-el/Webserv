
NAME = webserv

SRCS = main.cpp \
	   Parser.cpp Lexer.cpp Token.cpp ServerData.cpp

HEADERS = Parser.hpp Lexer.hpp Token.hpp Exceptions.hpp ServerData.hpp

COMPILER = c++

FLAGS = -std=c++98 -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(COMPILER) $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
