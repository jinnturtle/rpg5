#include "Viewport.hpp"

Viewport::Viewport(int x, int y, int w, int h)
: x{x}
, y{y}
, w{w}
, h{h}
, map_x{0}
, map_y{0}
, dm{nullptr}
{}

void Viewport::attach_dm(Data_master* dm) {this->dm = dm;}

void Viewport::render_level()
{
    for(int y {this->map_y}; y < this->dm->map->h; ++y) {
        for(int x {this->map_x}; x < this->dm->map->w; ++x) {
            Tile_type tile_type = this->dm->map->get_tile(x, y)->get_type();

            // determine graphics
            char tile_gfx;
            switch(tile_type) {
                case FLOOR: tile_gfx = '.'; break;
                case WALL: tile_gfx = '#'; break;
            }

            this->addch_at(x, y, tile_gfx);
        }
    }
}

void Viewport::render_pawns()
{
    for(auto& pawn : this->dm->pawns) {
        char pawn_gfx = '?';
        
        if(pawn->controller == PLAYER) {
            pawn_gfx = '@';
        }
        
        if(
            pawn->x >= 0 && pawn->x < this->dm->map->w
            && pawn->y >= 0 && pawn->y < this->dm->map->h
        ) {
            this->addch_at(pawn->x, pawn->y, pawn_gfx);
        }
    }
}

void Viewport::addch_at(int x, int y, char glyph)
{
    int onscreen_x = x + this->x;
    int onscreen_y = y + this->y;
    
    if(onscreen_x < this->x + this->w && onscreen_y < this->y + this->h) {
        mvaddch(onscreen_y, onscreen_x, glyph);
    }
}

void Viewport::render()
{
    this->render_level();
    this->render_pawns();
}
