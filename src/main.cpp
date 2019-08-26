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
#include "Creatures.hpp"

std::string gen_version();
void gameover();
void init_ncurses();
void deinit_ncurses();

int main() {
    init_ncurses();

    Floor_map level;
    level.generate_test_level();

    Human_pawn player(5, 5, PLAYER, 0, "player");
    Goblin_pawn mob(10, 10);
    Goblin_pawn mob2(20, 10);
    
    Data_master dm;
    dm.add_pawn(&player);
    dm.add_pawn(&mob);
    dm.add_pawn(&mob2);
    dm.set_floor_map(&level);

    Viewport viewport(0, 0, 80, 20);
    viewport.attach_dm(&dm);
    Pawn_statsview player_statsview(0, 20, &player);
    Pawn_statsview mob_statsview(0, 21, &mob);
    
    Log_viewer log_view(0, 22, 80, 5);
    log_view.attach_log(&dm);
    
    Ui ui(&viewport, &player_statsview, &log_view);
    
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
            default: break;
        }
        
        dm.make_turn(move_direction);
        if(dm.get_gameover()) {
            gameover();
            break;
        }

        ui.render();

        mvprintw(getmaxy(stdscr) - 1, 0, gen_version().c_str());
        cmd = getch();
        clear();
    }

    deinit_ncurses();
    return 1;
}

std::string gen_version()
{
    std::string name("prototype1");
    unsigned maj {0};
    unsigned med {0};
    unsigned min {5};
    bool wip {false};

    std::string suffix((wip)? "-WIP" : "");
    
    std::stringstream ssbuf;
    ssbuf << "v" << maj << "." << med << "." << min << "-" << name << suffix;
    
    return ssbuf.str();
}

void gameover()
{
    std::stringstream buf;
    
    buf << "Alas our hero has fallen." << std::endl
        << "This draws our story to a close." << std::endl
        << std::endl
        << "But there are more stroies." << std::endl;
        
    mvprintw(0, 0, buf.str().c_str());
    
    // wait for player input
    printw("\n\npress any key...");
    getch();
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
