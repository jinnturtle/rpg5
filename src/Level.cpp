#include "Level.hpp"

#include <stdexcept>

Level::Level(int w, const std::string& data)
: w{w}
{
    //init tile dict
    this->tile_dict.push_back(Tile(FLOOR));
    this->tile_dict.push_back(Tile(WALL));

    //bad dimensions
    if(data.size() % w != 0) {
        throw std::logic_error("Level data dimensions misalligned");
    }
    this->h = data.size() / w;

    //TODO allocate tiles space in one go
    for(auto ch : data) {
        switch(ch) {
            case '.': this->tiles.push_back(&this->tile_dict[0]); break;
            case '#': this->tiles.push_back(&this->tile_dict[1]); break;
            default: throw std::runtime_error("unrecognised symbol in level data");
        }
    }
}

Tile* Level::get_tile(int x, int y)
{
    if(
        x >= 0 && x < this->w
        && y >= 0 && y < this->h
    ) {
        return this->tiles[x + (y * this->w)];
    } else {
        //TODO log warning that a tile out of bounds was requested
        return nullptr;
    }
}
