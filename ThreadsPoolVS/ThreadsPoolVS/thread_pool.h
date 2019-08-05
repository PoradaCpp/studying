#pragma once

#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <future>
#include <mutex>
#include <iostream>

class ThreadPool
{
public:
    ThreadPool(size_t nNumOfThreads = std::thread::hardware_concurrency());
    ~ThreadPool();

    template <typename F, typename R = std::result_of_t<F&()>>
    std::future<R> addTask(F&& func);

private:
    std::queue <std::packaged_task <void()>> m_Tasks;
    std::vector <std::thread> m_Threads;
    std::mutex m_Mutex;
    std::condition_variable m_CondVar;
    size_t m_nNumOfActThreads = 0;
    bool m_fCarryOnWork = true;

private:
    void loopFunc(size_t nThreadId);
};

template <typename F, typename R>
std::future<R> ThreadPool::addTask(F&& func)
{
    std::packaged_task<R()> task(std::forward<F>(func));
    auto retValue = task.get_future();
    {
        std::lock_guard<std::mutex> lock(m_Mutex);
        m_Tasks.emplace(std::move(task));
        std::cout << "New task was added\n";
    }
    m_CondVar.notify_one();
    return retValue;
}
