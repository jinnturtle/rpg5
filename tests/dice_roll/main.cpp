// The purpose of this program is to test the parser of dice notation strings

#include <iostream>
#include <vector>
#include <string>

#include "../../src/dice_roll.cpp"

int main()
{
    std::vector<std::string> test_strings {
        "3d6",
        "1d60",
        "0d4 + 7",
        "1d0 + 77",
        "0d0 + 12",
        "0d0 - 12",
        "1d2 * 5",
        "1d10 / 5",
    };

    size_t reps {20};

    for(auto& roll_data : test_strings) {
        std::cout << "test: " << roll_data << std::endl;
        for(size_t i {0}; i < reps; ++i) {
            std::cout << "\t" << i << ": " << roll_dice(roll_data) << std::endl;
        }
    }

    return 0;
}
