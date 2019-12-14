#include "Creatures.hpp"

Human_pawn::Human_pawn(int x, int y,
                       Randomizer* rand,
                       Pawn_controller contr,
                       int team,
                       const std::string& name)
: Pawn{x, y, contr, team, name, 10, 10, rand}
{}

Goblin_pawn::Goblin_pawn(int x, int y,
                         Randomizer* rand,
                         Pawn_controller contr,
                         int team,
                         const std::string& name)
: Pawn{x, y, contr, team, name, 3, 6, rand}
{}
