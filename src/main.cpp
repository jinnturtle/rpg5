//std lib
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

//3rd party libs
#include <ncurses.h>

//homebrew
#include "Data_master.hpp"
#include "Ui.hpp"

std::string gen_version();
void init_ncurses();
void deinit_ncurses();

int main() {
    init_ncurses();

    Floor_map level;
    level.generate_test_level();

    Pawn player("player", 5, 5, PLAYER, 0);
    player.assign_map(&level);
    Pawn mob("mob", 10, 10, AI_BASIC, 1);
    mob.assign_map(&level);
    
    Data_master dm;
    dm.add_pawn(&player);
    dm.add_pawn(&mob);
    dm.set_floor_map(&level);

    Viewport viewport(0, 0, 80, 20);
    viewport.attach_dm(&dm);
    Pawn_statsview player_statsview(0, 20, &player);
    Pawn_statsview mob_statsview(0, 21, &mob);
    
    Ui ui(&viewport, &player_statsview);
    
    // game loop
    int cmd {0};
    while(cmd != 'q') {
        // process movement input
        Direction move_direction {NONE};
        switch(cmd) {
            case 'h': move_direction = WEST; break;
            case 'j': move_direction = SOUTH; break;
            case 'k': move_direction = NORTH; break;
            case 'l': move_direction = EAST; break;
            
//             case 'w': --viewport.y; break;
//             case 'a': --viewport.x; break;
//             case 's': ++viewport.y; break;
//             case 'd': ++viewport.x; break;
//             case 'S': --viewport.h; break;
//             case 'A': --viewport.w; break;
//             case 'W': ++viewport.h; break;
//             case 'D': ++viewport.w; break;
            default: break;
        }
        
        dm.move_pawns(move_direction);

        ui.render();
        mob_statsview.render();

        mvprintw(getmaxy(stdscr) - 1, 0, gen_version().c_str());
        cmd = getch();
        clear();
    }

    deinit_ncurses();
    return 1;
}

std::string gen_version()
{
    unsigned maj {0};
    unsigned min {1};
    unsigned fix {0};
    std::string name("prototype");
    
    std::stringstream ssbuf;
    ssbuf << "v" << maj << "." << min << "." << fix << "-" << name;
    
    return ssbuf.str();
}

void init_ncurses()
{
	initscr();//start ncurses mode
	//initialisation functions
	raw();//pass all keyboard input to the program, avoiding terminal interupts
	noecho();//do not echo chars to terminal
	keypad(stdscr, true);//enable arrow keys, F1, F2 ,etc... for stdscr
	curs_set(0);//hide the cursor
}

void deinit_ncurses()
{
    endwin();
}
