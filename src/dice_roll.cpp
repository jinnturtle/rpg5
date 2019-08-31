#include "dice_roll.hpp"

#include <array>

Randomizer::Randomizer()
: rng{std::mt19937(this->dev())}
{}

int Randomizer::roll_dice(const std::string& dice_str)
{    
    auto d = this->parse_dice_string(dice_str);
    
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, d.sides);
    
    // roll the dice
    int sum {0};
    if(d.sides != 0) {
        for(size_t i {0}; i < d.ammount; ++i) {
            sum += dist(this->rng);
        }
    }
    
    int result {sum};
    
    // if a modifier was applied - finding the argument and modirying the
    // result accordingly
    if(d.modifier) {
        switch(d.modifier) {
            case '+': result += d.mod_argument; break;
            case '-': result -= d.mod_argument; break;
            case '*': result *= d.mod_argument; break;
            case '/': result /= d.mod_argument; break;
            default: break;
        }
    }
    
    return result;
}

Randomizer::Dicethrow_data Randomizer::parse_dice_string(const std::string& dice_str)
{
    Dicethrow_data d{
        .ammount = 0,
        .sides = 0,
        .modifier = 0,
        .mod_argument = 0
    };
    
    // the ammount of dice to throuw is the number before the 'd' separator
    constexpr char dsep {'d'};
    size_t dsep_pos = dice_str.find(dsep);
    std::string ammount_str {dice_str.substr(0, dsep_pos)};
    d.ammount = static_cast<unsigned>(std::stoi(ammount_str));
    
    // the number of sides the dice have is the number between the 'd' separator
    // and the modifier
    constexpr std::array<char,4> mods {'+', '-', '*', '/'};
    size_t mod_pos = dice_str.find_first_of(&mods[0], dsep_pos + 1);
    std::string sides_str {
        dice_str.substr(dsep_pos + 1, mod_pos - dsep_pos - 1)};
    d.sides = static_cast<unsigned>(std::stoi(sides_str));
    
    // modifier is the mathematical sign after the sides number
    if(mod_pos != std::string::npos) {d.modifier = dice_str[mod_pos];}
    
    // the modifier is followed by modifier argument int (to modify stuff by)
    if(d.modifier) {
        d.mod_argument = std::stoi(dice_str.substr(mod_pos + 1));
    }

    return d;
}
