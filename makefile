CXX = g++ -Wall -Wextra -std=c++17 -ggdb
NAME = game
SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp
LIBS = -lncurses

all: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(LIBS) -o $@ $^
