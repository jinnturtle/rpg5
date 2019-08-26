#include "Creatures.hpp"

Human_pawn::Human_pawn(int x, int y,
                       Pawn_controller contr, int team,
                       const std::string& name)
: Pawn{x, y, contr, team, name, 10, 10}
{}

Goblin_pawn::Goblin_pawn(int x, int y,
                       Pawn_controller contr, int team,
                       const std::string& name)
: Pawn{x, y, contr, team, name, 3, 6}
{}
