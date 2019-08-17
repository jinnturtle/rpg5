#include "Pawn.hpp"

Pawn::Pawn(int x, int y)
: x{x}
, y{y}
{}

void Pawn::move(Direction dir)
{
    switch(dir) {
        case NORTH: --this->y; break;
        case EAST:  ++this->x; break;
        case SOUTH: ++this->y; break;
        case WEST:  --this->x; break;
        default: break;
    }
}
