#pragma once

#include <queue>
#include <vector>
#include <thread>
#include <condition_variable>
#include <future>
#include <mutex>
#include <iostream>
#include <atomic>

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
	std::mutex m_ConsoleMutex;
    std::condition_variable m_CondVar;
    std::atomic_uint m_nNumOfActThreads;
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
    }
	m_CondVar.notify_one();
	{
		std::lock_guard<std::mutex> console_lock(m_ConsoleMutex);
		std::cout << "New task was added\n";
	}
    return retValue;
}
