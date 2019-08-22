#ifndef CREATURES_HPP
#define CREATURES_HPP

#include "Pawn.hpp"

class Human_pawn : public Pawn {
public:
    Human_pawn(int x, int y,
               Pawn_controller contr = AI_BASIC, int team = 1,
               const std::string& name = "human");
    virtual ~Human_pawn(){}
};

class Goblin_pawn : public Pawn {
public:
    Goblin_pawn(int x, int y,
               Pawn_controller contr = AI_BASIC, int team = 1,
               const std::string& name = "goblin");
    virtual ~Goblin_pawn(){}
};

#endif //ifndef CREATURES_HPP
