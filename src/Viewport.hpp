#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

//3rd party libs
#include <ncurses.h>

//homebrew
#include "Level.hpp"
#include "Pawn.hpp"

class Viewport final {
public:
    Viewport();

    void attach_level(Level* level);
    void attach_player(Pawn* player);
    void render_level();
    void render_player();
private:
    Level* level; //attached level
    Pawn* player; //attached player (temp solution)
};

#endif //define VIEWPORT_HPP
