#include "Pawn.hpp"

Pawn::Pawn(int x, int y)
: x{x}
, y{y}
, map{nullptr}
{}

void Pawn::move(Direction dir)
{
    int tgt_x = this->x;
    int tgt_y = this->y;

    // set target coordinates (where we want to move to)
    switch(dir) {
        case NORTH: --tgt_y; break;
        case EAST:  ++tgt_x; break;
        case SOUTH: ++tgt_y; break;
        case WEST:  --tgt_x; break;
        default: break;
    }

    // see if the target coordinates are passable, and move there if so
    if(this->map->get_tile(tgt_x, tgt_y)->get_type() != WALL) {
        this->x = tgt_x;
        this->y = tgt_y;
    }
}

void Pawn::assign_map(Level* map) {this->map = map;}
