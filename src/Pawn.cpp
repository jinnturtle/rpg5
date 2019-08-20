#include "Pawn.hpp"

Pawn::Pawn(const std::string& name, int x, int y,
           Pawn_controller contr, int team,
           int hp, int hp_max, int dmg)
: name{name}
, controller{contr}
, team{team}
, x{x}
, y{y}
, hp{hp}
, hp_max{hp_max}
, dmg{dmg}
, stats{.per = 5, .str = 1}
{}

void Pawn::move(Direction dir)
{
    // set target coordinates (where we want to move to)
    switch(dir) {
        case NORTH: --this->y; break;
        case EAST:  ++this->x; break;
        case SOUTH: ++this->y; break;
        case WEST:  --this->x; break;
        default: break;
    }
}

void Pawn::attack(Pawn* enemy) {enemy->take_damage(this->dmg);}

void Pawn::take_damage(int dmg) {this->hp -= dmg;}
