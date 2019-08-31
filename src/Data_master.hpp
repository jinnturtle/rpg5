#ifndef DATAMASTER_HPP
#define DATAMASTER_HPP

#include <vector>

#include "Pawn.hpp"
#include "Floor_map.hpp"
#include "Randomizer.hpp"

typedef std::vector<std::string> Message_log;

// tabletop RPGs have a game master (aka. dungeon master), this is
// the data master (your digital DM)
class Data_master final {
public:
    Data_master();
    
    void make_turn(Direction player_input);
    void add_pawn(Pawn* pawn);
    void set_floor_map(Floor_map* map);
    bool get_gameover();
    
private:
    std::vector<Pawn*> pawns;
    Message_log log; // TODO use a deque?
    Floor_map* map;
    int turn; // the current game turn
    Randomizer rand;

    void move_pawns(Direction player_input);
    void update_pawns();
    void player_take_turn(Pawn* pawn, Direction player_input);
    void ai_basic_take_turn(Pawn* pawn);
    Pawn* get_pawn_at(int x, int y);
    void move_pawn(Pawn* pawn, Direction direction);
    void move_pawn(Pawn* pawn, int x, int y);
    void pawn_attack(Pawn* attacker, Pawn* target);
    void add_message(const std::string& msg);
    
    friend class Viewport;
    friend class Log_viewer;
};

#endif //#ifndef DATAMASTER_HPP
