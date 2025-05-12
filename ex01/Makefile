NAME			=	RPN
CXX				=	c++
FLAGS			=	-Wall -Wextra -Werror
STANDARD		=	--std=c++17
SRCS			=	main.cpp RPN.cpp
HEADERS			=	RPN.hpp
OBJS			=	$(SRCS:.cpp=.o)

# Rule to create object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(FLAGS) $(STANDARD) -c $< -o $@

# Linking the object files into the final executable
$(NAME): $(OBJS)
	$(CXX) $(OBJS) $(FLAGS) $(STANDARD) -o $(NAME)

# Default target
all: $(NAME)

# Clean object files
clean:
	rm -rf $(OBJS)

# Clean object files and executable
fclean: clean
	rm -rf $(NAME)

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
