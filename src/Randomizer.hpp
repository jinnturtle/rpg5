#ifndef RANDOMIZER_HPP
#define RANDOMIZER_HPP

#include <string>
#include <random>

class Randomizer final {
public:
    Randomizer();

    int roll_dice(const std::string& dice_str);
    int roll_in_range(int min, int max);

private:
    struct Dicethrow_data {
        unsigned ammount;
        unsigned sides;
        char modifier;
        unsigned mod_argument;
    };

    std::random_device dev;
    std::mt19937 rng;

    Dicethrow_data parse_dice_string(const std::string& dice_str);
};

#endif //ifndef RANDOMIZER_HPP
