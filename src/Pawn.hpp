#ifndef PAWN_HPP
#define PAWN_HPP

#include "world.hpp"
#include "Level.hpp"

class Pawn {
public:
    Pawn(int x, int y);
    virtual ~Pawn(){};

    void move(Direction dir);
    void assign_map(Level* map);
private:
    int x, y;
    Level* map;

    friend class Viewport;
};

#endif //define PAWN_HPP
