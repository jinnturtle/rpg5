// The purpose of this program is to test the parser of dice notation strings

#include <iostream>
#include <vector>
#include <string>

#include "../../src/Randomizer.cpp"

struct Test_data {int min, max;};

int main()
{
    std::vector<Test_data> test_strings {
        {.min = 10, .max = 20},
        {.min = 0, .max = 100},
        {.min = -100, .max = 100},
        {.min = -200, .max = -100},
        {.min = 100, .max = -100},
        {.min = 0, .max = 0},
    };
    
    Randomizer rand;

    size_t reps {20};

    for(auto& roll_data : test_strings) {
        std::cout << "test: " << roll_data.min << " - " << roll_data.max
        << std::endl;
        for(size_t i {0}; i < reps; ++i) {
            std::cout << "\t" << i << ": "
            << rand.roll_in_range(roll_data.min, roll_data.max) << std::endl;
        }
    }

    return 0;
}
