#include "Tile.hpp"

Tile::Tile(Tile_type type)
: type{type}
{}

Tile_type Tile::get_type() {return this->type;}
