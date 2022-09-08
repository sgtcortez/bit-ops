#include "BitOps.hpp"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    // Supress unused arguments. Use this to enable the flag: -Werror(which threats warnings as errors)
    (void(argc));
    (void(argv));

    uint32_t number = 300;
    Dword byte(number);
    cout << byte.to_string() << endl;
    auto restored = byte.restore();

    cout << "Number: " << to_string(number) << " restored: " << to_string(restored) << " are equals: " << (number == restored) << endl;


    return EXIT_SUCCESS;
}