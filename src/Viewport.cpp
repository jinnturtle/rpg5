#include "Viewport.hpp"

Viewport::Viewport()
: level{nullptr}
{}

void Viewport::attach_level(Level* level) {this->level = level;}
void Viewport::attach_player(Pawn* player) {this->player = player;}

void Viewport::render_level()
{
    for(int y {0}; y < this->level->h; ++y) {
        for(int x {0}; x < this->level->w; ++x) {
            mvaddch(y, x, this->level->data[x + (y * this->level->w)]);
        }
    }
}

void Viewport::render_player()
{
    if(
        this->player->x >= 0 && this->player->x < this->level->w
        && this->player->y >= 0 && this->player->y < this->level->h
    ) {
        mvaddch(this->player->y, this->player->x, '@');
    }
}
