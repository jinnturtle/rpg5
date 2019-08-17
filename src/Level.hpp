#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <string>

class Level {
public:
    Level(int w, const std::string& data);
    virtual ~Level(){};

private:
    std::string data;
    int w,h;

    friend class Viewport;
};

#endif //define LEVEL_HPP
