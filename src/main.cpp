//std lib
#include <vector>
#include <string>
#include <stdexcept>

//3rd party libs
#include <ncurses.h>

void init_ncurses();
void deinit_ncurses();

class Level {
public:
    Level(int w, const std::string& data);
    virtual ~Level(){};

private:
    std::string data;
    int w,h;

    friend class Viewport;
};

Level::Level(int w, const std::string& data)
: data(data)
, w{w}
{
    //bad dimensions
    if(data.size() % w != 0) {
        throw std::logic_error("Level data dimensions misalligned");
    }
    this->h = this->data.size() / w;
}

enum Direction {
    NORTH = 0,
    EAST,
    SOUTH,
    WEST
};

class Pawn {
public:
    Pawn(int x, int y);
    virtual ~Pawn(){};

    void move(Direction dir);
private:
    int x, y;

    friend class Viewport;
};

Pawn::Pawn(int x, int y)
: x{x}
, y{y}
{}

void Pawn::move(Direction dir)
{
    switch(dir) {
        case NORTH: --this->y; break;
        case EAST:  ++this->x; break;
        case SOUTH: ++this->y; break;
        case WEST:  --this->x; break;
        default: break;
    }
}

class Viewport final {
public:
    Viewport();

    void attach_level(Level* level);
    void attach_player(Pawn* player);
    void render_level();
    void render_player();
private:
    Level* level; //attached level
    Pawn* player; //attached player (temp solution)
};

Viewport::Viewport()
: level{nullptr}
{}

void Viewport::attach_level(Level* level) {this->level = level;}
void Viewport::attach_player(Pawn* player) {this->player = player;}
void Viewport::render_level()
{
    for(int y {0}; y < this->level->h; ++y) {
        for(int x {0}; x < this->level->w; ++x) {
            mvaddch(y, x, this->level->data[x + (y * this->level->w)]);
        }
    }
}

void Viewport::render_player()
{
    if(
        this->player->x >= 0 && this->player->x < this->level->w
        && this->player->y >= 0 && this->player->y < this->level->h
    ) {
        mvaddch(this->player->y, this->player->x, '@');
    }
}

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
