#ifndef TILE_HPP
#define TILE_HPP

enum Tile_type {
    FLOOR = 0,
    WALL
};

class Tile {
public:
    Tile(Tile_type type);
    virtual ~Tile(){};

    Tile_type get_type();
private:
    Tile_type type;
};

#endif //define TILE_HPP
