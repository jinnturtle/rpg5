#include "Level.hpp"

#include <stdexcept>

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
