#include "Pawn.hpp"

#include <sstream>

Pawn::Pawn(const std::string& name, int x, int y,
           Pawn_controller contr, int team,
           int hp, int hp_max, int dmg)
: stats{.per = 5, .str = 1}
, name{name}
, controller{contr}
, team{team}
, x{x}
, y{y}
, hp{hp}
, hp_max{hp_max}
, dmg{dmg}
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

void Pawn::take_damage(int dmg) {this->hp -= dmg;}

std::string Pawn::attack(Pawn* enemy) {
    if(this->check_dead()) {return "";}
    
    std::stringstream msg;
    msg << "The " << this->name << " attacks " << enemy->name
        << " dealing " << this->dmg << " damage.";
    
    enemy->take_damage(this->dmg);
    
    return msg.str();
}

bool Pawn::check_dead() {return(this->hp <= 0);}
