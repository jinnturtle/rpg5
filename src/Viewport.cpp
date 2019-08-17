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
            Tile_type tile_type = this->level->get_tile(x, y)->get_type();

            char tile_gfx;
            switch(tile_type) {
                case FLOOR: tile_gfx = '.'; break;
                case WALL: tile_gfx = '#'; break;
            }

            mvaddch(y, x, tile_gfx);
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
