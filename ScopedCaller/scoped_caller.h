#pragma once

#include <functional>
#include <iostream>

class ScopedCaller
{
public:
    template<typename T>
    ScopedCaller(T&& f);
    ScopedCaller(const ScopedCaller &other) = delete;
    ScopedCaller(ScopedCaller &&other);
    ~ScopedCaller();

    ScopedCaller& operator = (const ScopedCaller &other) = delete;
    ScopedCaller& operator = (ScopedCaller &&other);
    template<typename T>
    void reset(T&& f);
    void reset();
    std::function<void()> release();

private:
    std::function<void()> m_func;
};

template<typename T>
ScopedCaller::ScopedCaller(T&& f): m_func(std::forward<T>(f)) {}

ScopedCaller::ScopedCaller(ScopedCaller &&other): m_func(std::move(other.m_func)) {}

ScopedCaller::~ScopedCaller()
{
    auto temp = std::move(m_func);

    if(temp)
    {
        temp();
    }
}

ScopedCaller& ScopedCaller::operator = (ScopedCaller &&other)
{
    m_func = std::move(other.m_func);
    return *this;
}

template<typename T>
void ScopedCaller::reset(T&& f)
{
    auto temp = std::move(m_func);
    m_func = std::forward<T>(f);

    if(temp)
    {
        temp();
    }
}

void ScopedCaller::reset()
{
    auto temp = std::move(m_func);

    if(temp)
    {
        temp();
    }
}

std::function<void ()> ScopedCaller::release()
{
    auto temp = std::move(m_func);

    if(temp)
    {
        temp();
    }
    return temp;
}
