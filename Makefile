NAME = containers

SRCS =  main.cpp

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

OBJ 		= 	$(SRCS:.cpp=.o)

$(NAME): $(OBJ)
	@clang++ -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

