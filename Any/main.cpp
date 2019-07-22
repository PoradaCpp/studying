#include <iostream>

#include "any.hpp"

using namespace std;

int main()
{
    Any a;
    std::cout << std::boolalpha;
    a = 1;
    std::cout << a.type().name() << ": " << a.any_cast<int>() << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << a.any_cast<double>() << '\n';
    a = true;
    std::cout << a.type().name() << ": " << a.any_cast<bool>() << '\n';

    try
    {
        a.any_cast<int>();
    }
    catch (const std::runtime_error &error)
    {
        std::cout << error.what() << '\n';
    }


    return 0;
}
