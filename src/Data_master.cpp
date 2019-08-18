#include "Data_master.hpp"

#include <climits>
#include <cmath>

void Data_master::move_pawns(Direction player_input)
{
    for(auto& pawn : this->pawns) {
        switch(pawn->controller) {
            case PLAYER: player_take_turn(pawn, player_input); break;
            case AI_BASIC: ai_basic_take_turn(pawn); break;
            default: break;
        }
    }
    
    this->update_pawns();
}

void Data_master::add_pawn(Pawn* pawn)
{
    this->pawns.push_back(pawn);
}

void Data_master::set_floor_map(Floor_map* map)
{
    this->map = map;
}

void Data_master::player_take_turn(Pawn* pawn, Direction player_input)
{
    if(pawn->controller == PLAYER) {
        int tgt_x = pawn->x;
        int tgt_y = pawn->y;
        switch(player_input) {
            case NORTH: --tgt_y; break;
            case EAST: ++tgt_x; break;
            case SOUTH: ++tgt_y; break;
            case WEST: --tgt_x; break;
            default: break;
        }
        
        Pawn* tgt_pawn = this->get_pawn_at(tgt_x, tgt_y);
        if(tgt_pawn) {
            pawn->attack(tgt_pawn);
            return;
        }
        
        pawn->move(player_input);
    }
}

void Data_master::ai_basic_take_turn(Pawn* pawn)
{
    // this AI biscally moves to the closes non-friendly pawn and attacks it
    
    int closest_dist {INT_MAX};
    Pawn* closest_enemy {nullptr};
    for(auto& other_pawn : this->pawns) {
        // skip team-mates
        if(other_pawn->team == pawn->team) {continue;}
        
        int dist_x {abs(other_pawn->x - pawn->x)};
        int dist_y {abs(other_pawn->y - pawn->y)};
        int distance {dist_x + dist_y};
        if(closest_dist > distance) {
            closest_dist = distance;
            closest_enemy = other_pawn;
        }
    }
    //decide movement direction to get closer if were not close enough
    if(closest_dist <= 1) {
        pawn->attack(closest_enemy);
        return;
    }
    
    Direction direction{NONE};
    if(closest_enemy) {
        if(closest_enemy->x > pawn->x) {direction = EAST;}
        else if(closest_enemy->x < pawn->x) {direction = WEST;}
        else if(closest_enemy->y < pawn->y) {direction = NORTH;}
        else if(closest_enemy->y > pawn->y) {direction = SOUTH;}
    }
    pawn->move(direction);
}

Pawn* Data_master::get_pawn_at(int x, int y)
{
    for(auto& pawn: this->pawns) {
        if(pawn->x == x && pawn->y == y) {
            return pawn;
        }
    }
    
    return nullptr;
}

void Data_master::update_pawns()
{
    for(size_t i {0}; i < this->pawns.size(); ++i) {
        // if pawn is dead, delete by overwrting with back and delete back
        if(this->pawns[i]->hp == 0) {
            this->pawns[i] = this->pawns.back();
            this->pawns.pop_back();
        }
    }
}
