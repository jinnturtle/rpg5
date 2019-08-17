#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <memory>
#include <vector>

#include "Tile.hpp"

class Level {
public:
    Level(int w, const std::string& data);
    virtual ~Level(){};

    Tile* get_tile(int x, int y);

private:
    std::vector<Tile*> tiles;
    std::vector<Tile> tile_dict;
    int w,h;

    friend class Viewport;
};

#endif //define LEVEL_HPP
