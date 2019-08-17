#ifndef PAWN_HPP
#define PAWN_HPP

#include "world.hpp"

class Pawn {
public:
    Pawn(int x, int y);
    virtual ~Pawn(){};

    void move(Direction dir);
private:
    int x, y;

    friend class Viewport;
};

#endif //define PAWN_HPP
