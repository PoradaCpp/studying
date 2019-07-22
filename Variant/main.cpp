#include <iostream>
#include <algorithm>
#include <type_traits>
#include <string>

#include "variant.hpp"


int main()
{
    Variant<int, double, char> v;

    v = 1;
    std::cout << v.get<int>() << '\n';

    v = 3.14;
    std::cout << v.get<double>() << '\n';

    v = 'v';
    std::cout << v.get<char>() << '\n';

    try
    {
        std::cout << v.get<double>() << '\n';
    }
    catch (const std::runtime_error &error)
    {
        std::cout << error.what() << '\n';
    }

    try
    {
        v = "vv";
    }
    catch (const std::runtime_error &error)
    {
        std::cout << error.what() << '\n';
    }

    Variant<int, std::string&> v1;

    std::string s("abc");
    v1 = s;
    std::cout << v1.get<std::string&>() << '\n';

    return 0;
}
