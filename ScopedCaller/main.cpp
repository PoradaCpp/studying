#include <iostream>

#include "scoped_caller.h"

struct f
{
    void operator () ()
    {
        std::cout << ":::ScopedCaller\n";
        throw 1;
    }
};

int main()
{
    {
        std::cout << "ScopedCaller c-tor...\n";
        f fff;
        ScopedCaller sc(fff);
        std::cout << "ScopedCaller reset():\n";
        try
        {
            sc.reset([](){std::cout << ":::new ScopedCaller\n";});
        }
        catch (int &exc)
        {
            std::cout << "Exception caught! " << exc << " \n";
        }

    }
    std::cout << "Out of scope\n";

    return 0;
}
