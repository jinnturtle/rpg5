#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>
#include <memory>
#include <vector>

#include "Tile.hpp"

class Floor_map final {
public:
    Floor_map();
    virtual ~Floor_map(){};

    Tile* get_tile(int x, int y);
    void generate_test_level();

private:
    std::vector<Tile*> tiles;
    std::vector<Tile> tile_dict;
    int w,h;

    friend class Viewport;
};

#endif //define LEVEL_HPP
