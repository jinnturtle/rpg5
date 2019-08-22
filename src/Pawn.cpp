#include "Pawn.hpp"

#include <sstream>

Pawn::Pawn(int x, int y,
           Pawn_controller contr, int team,
           const std::string& name,
           int hp, int str)
: stats{.str = str}
, name{name}
, controller{contr}
, team{team}
, x{x}
, y{y}
, hp{hp}
, hp_max{this->hp}
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
    
    int dmg = this->calc_dmg();
    
    std::stringstream msg;
    msg << "The " << this->name << " attacks " << enemy->name
        << " dealing " << dmg << " damage.";
    
    enemy->take_damage(dmg);
    
    return msg.str();
}

bool Pawn::check_dead() {return(this->hp <= 0);}

int Pawn::calc_dmg()
{
    return this->stats.str / 5;
}
