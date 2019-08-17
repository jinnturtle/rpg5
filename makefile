CXX = g++ -Wall -Wextra -std=c++17 -ggdb
LD = g++
NAME = game
SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp
INCLUDE = -I src
LIBS = -lncurses
OBJ_DIR = obj
_OBJ = main.o \
	   Level.o \
	   Pawn.o \
	   Viewport.o
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))
MAKEFILE = makefile

all: $(MAKEFILE) $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "CXX $@"
	@$(CXX) $(INCLUDE) -c -o $@ $<

$(NAME): $(OBJ) $(MAKEFILE)
	@echo "LD $@"
	@$(LD) -o $@ $(OBJ) $(LIBS)

.PHONY: clean
clean:
	@rm -rfv $(OBJ_DIR)
	@rm -fv $(NAME)
