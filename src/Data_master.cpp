#include "Data_master.hpp"

void Data_master::move_pawns(Direction player_input)
{
    for(auto& pawn : this->pawns) {
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
                continue;
            }
            
            pawn->move(player_input);
        } else {
            pawn->move(NONE);
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
