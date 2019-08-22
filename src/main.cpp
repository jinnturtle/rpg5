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
void gameover();
void init_ncurses();
void deinit_ncurses();
void message_screen(Data_master* dm); // TODO this is temporary just for debugging

int main() {
    init_ncurses();

    Floor_map level;
    level.generate_test_level();

    Pawn player("player", 5, 5, PLAYER, 0);
    Pawn mob("mob", 10, 10, AI_BASIC, 1);
    
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
            case 'm': message_screen(&dm); break;
            
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
        if(dm.get_gameover()) {
            gameover();
            break;
        }

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
    std::string name("prototype1");
    unsigned maj {0};
    unsigned med {0};
    unsigned min {2};
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

void message_screen(Data_master* dm)
{
    std::vector<std::string*> messages = dm->get_messages(5);
    
    move(0, 0);
    for(auto& message : messages) {
        printw("%s\n", message->c_str());
    }
    
    getch();
}
