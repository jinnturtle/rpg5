CXX = g++ -Wall -Wextra -std=c++17 -ggdb
LD = g++
NAME = game
SRC_DIR = src
SRC = $(SRC_DIR)/main.cpp
INCLUDE = -I src
LIBS = -lncurses
OBJ_DIR = obj
SRC =      main.cpp \
	   Floor_map.cpp \
	   Pawn.cpp \
	   Viewport.cpp \
	   Tile.cpp \
	   Data_master.cpp \
	   Pawn_statsview.cpp \
	   Log_viewer.cpp \
	   Creatures.cpp \
	   Ui.cpp \
	   dice_roll.cpp
_OBJ := $(SRC:%.cpp=%.o)
OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))
MAKEFILE = makefile

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

all: $(MAKEFILE) $(OBJ_DIR) $(DEPDIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPDIR)/%.d | $(DEPDIR)
	@echo "CXX $@"
	@$(CXX) $(DEPFLAGS) -o $@ $< $(INCLUDE) -c

$(NAME): $(OBJ) $(MAKEFILE)
	@echo "LD $@"
	@$(LD) -o $@ $(OBJ) $(LIBS)

# cleaning
.PHONY: clean
clean:
	@rm -rfv $(OBJ_DIR)
	@rm -fv $(NAME)

# dependency files
$(DEPDIR):
	mkdir -p $@
	
DEPFILES := $(_OBJ:%.o=$(DEPDIR)/%.d)
$(DEPFILES):

include $(wildcard $(DEPFILES))
