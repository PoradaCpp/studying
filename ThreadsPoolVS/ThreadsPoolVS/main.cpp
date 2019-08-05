#include <iostream>
#include <functional>
#include <string>
#include <cmath>

#include "thread_pool.h"

double func1(size_t nNum1, size_t nNum2);
std::string func2(std::string str1, size_t nNum);
size_t func3(size_t nNum1, size_t nNum2);

int main()
{
    const size_t EXPERIMENTS = 30;
    ThreadPool pool;
    std::vector<std::future<void>> futureVc;

    std::vector<double> dVc1(0);
    std::vector<std::string> sVc2;
    std::vector<size_t> nVc3(0);

    for (size_t i = 0; i < EXPERIMENTS; ++i)
    {
        futureVc.emplace_back(pool.addTask([&dVc1, i]
        {
            dVc1.push_back(func1(i, i));
        }));

        futureVc.emplace_back(pool.addTask([&sVc2, i]
        {
            sVc2.push_back(func2(std::to_string(i), i));
        }));

        futureVc.emplace_back(pool.addTask([&nVc3, i]
        {
            nVc3.push_back(func3(i, i));
        }));
    }

    for (auto &future : futureVc)
    {
        future.wait();
    }

    for(double dNum : dVc1)
    {
        std::cout << dNum << ' ';
    }
    std::cout << '\n';

    for(std::string str : sVc2)
    {
        std::cout << str << ' ';
    }
    std::cout << '\n';

    for(size_t nNum : nVc3)
    {
        std::cout << nNum << ' ';
    }
    std::cout << '\n';

    return 0;
}

double func1(size_t nNum1, size_t nNum2)
{
    return log(nNum1) + log(nNum2);
}

std::string func2(std::string str1, size_t nNum)
{
    return str1 + " + " + std::to_string(nNum) + "\n";
}

size_t func3(size_t nNum1, size_t nNum2)
{
    return nNum1 + nNum2;
}
