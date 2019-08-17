#include "Pawn_statsview.hpp"

// c++ std lib
#include <sstream>

// 3rd party libs
#include <ncurses.h>

Pawn_statsview::Pawn_statsview(int x, int y, Pawn* pawn)
: x{x}
, y{y}
, pawn{pawn}
{}

void Pawn_statsview::render()
{
    int pos_x = this->x;
    int pos_y = this->y;
    
    std::stringstream linebuff;
    
    linebuff << this->pawn->name << "} HP: " << this->pawn->hp << "/" << this->pawn->hp_max;
    mvprintw(pos_y, pos_x, linebuff.str().c_str());
}
