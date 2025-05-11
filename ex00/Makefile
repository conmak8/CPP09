NAME		=	btc
CXX			=	c++
FLAGS		=	-Wall -Wextra -Werror
STANDARD	=	--std=c++17
SRCS		=	main.cpp BitcoinExchange.cpp
HEADERS		=	BitcoinExchange.hpp
OBJS		=	$(SRCS:.cpp=.o)

%.o:%.cpp $(HEADERS)
	$(CXX) $(FLAGS) $(STANDARD) -o $@ -c $<

$(NAME):$(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
