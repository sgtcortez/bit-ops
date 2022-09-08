#include "BitOps.hpp"
#include <cstdint>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    // Supress unused arguments. Use this to enable the flag: -Werror(which threats warnings as errors)
    (void(argc));
    (void(argv));

    uint64_t number = 34359738368 + 3131414;
    Qword byte(number);
    cout << byte.to_string() << endl;
    auto restored = byte.restore();

    cout << "Number: " << to_string(number) << " restored: " << to_string(restored) << " are equals: " << (number == restored) << endl;


    return EXIT_SUCCESS;
}