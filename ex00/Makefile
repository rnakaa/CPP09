CXX = c++

CXXFLAGS = -std=c++98 -Wall -Wextra -Werror 
NAME = btc

SRCS = main.cpp\
	BitcoinExchange.cpp



HEADERS = BitcoinExchange.hpp

OBJS = $(SRCS:%.cpp=%.o)

$(NAME):$(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o : %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:all
all:$(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS) 

.PHONY: fclean
fclean: clean
	rm -f $(NAME) 

.PHONY:re
re:		fclean all

.PHONY:run
run: all $(NAME) 
	./$(NAME)
