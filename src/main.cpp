//std lib
#include <vector>
#include <string>
#include <stdexcept>

//3rd party libs
#include <ncurses.h>

//homebrew
#include "Level.hpp"
#include "Pawn.hpp"
#include "Viewport.hpp"

void init_ncurses();
void deinit_ncurses();

int main() {
    init_ncurses();

    Level level {
        .w = 60,
        .data = {
            "............................................................"
            "............................................................"
            "............................................................"
            "............................................................"
            "............................................................"
            "..................#########................................."
            "..................#.......#................................."
            "..................#.......#................................."
            "..................#.......#................................."
            "..................#........................................."
            "..................#.......#................................."
            "..................#.......#................................."
            "..................#.......#................................."
            "..................#########................................."
            "............................................................"
            "............................................................"
            "............................................................"
            "............................................................"
            "............................................................"
            "............................................................"}
    };

    Pawn player {.x = 5, .y = 5};
    player.assign_map(&level);

    Viewport viewport;
    viewport.attach_level(&level);
    viewport.attach_player(&player);

    // game loop
    int cmd {0};
    while(cmd != 'q') {
        // process movement input
        switch(cmd) {
            case 'h': player.move(WEST); break;
            case 'j': player.move(SOUTH); break;
            case 'k': player.move(NORTH); break;
            case 'l': player.move(EAST); break;
            default: break;
        }

        viewport.render_level();
        viewport.render_player();

        cmd = getch();
    }

    deinit_ncurses();
    return 1;
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
