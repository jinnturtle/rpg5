#ifndef PAWN_STATSVIEW_HPP
#define PAWN_STATSVIEW_HPP

#include "Pawn.hpp"

class Pawn_statsview final {
public:
    Pawn_statsview(int x = 0, int y = 0, Pawn* pawn = nullptr);
    
    void render();
private:
    int x, y;
    Pawn* pawn;
};

#endif //define PAWN_STATSVIEW_HPP
