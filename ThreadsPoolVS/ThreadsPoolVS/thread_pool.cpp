#include "thread_pool.h"

#include <iostream>

ThreadPool::ThreadPool(size_t nNumOfThreads /* = std::thread::hardware_concurrency()*/)
{
	m_nNumOfActThreads.store(0);
    size_t nCores = std::thread::hardware_concurrency();

    if(!nNumOfThreads || (nNumOfThreads > nCores && nCores))
    {
        nNumOfThreads = nCores ? nCores : 1;
    }

    m_Threads.reserve(nNumOfThreads);

    for (size_t i = 0; i < nNumOfThreads; ++i)
    {
        m_Threads.emplace_back([this, nThreadId = i]
        {
            loopFunc(nThreadId);
        });
    }
}

ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(m_Mutex);
    m_fCarryOnWork = false;
    lock.unlock();
    m_CondVar.notify_all();

    for (std::thread &thread : m_Threads)
    {
        thread.join();
    }
}

void ThreadPool::loopFunc(size_t nThreadId)
{
    std::unique_lock<std::mutex> lock(m_Mutex, std::defer_lock);
    std::packaged_task<void()> task;

    while(true)
    {
		lock.lock();
        m_CondVar.wait(lock, [this]
        {
            return !m_Tasks.empty() || !m_fCarryOnWork;
        });

        if(!m_fCarryOnWork)
        {
            break;
        }

        task = std::move(m_Tasks.front());
        m_Tasks.pop();

        lock.unlock();
		{
			std::lock_guard<std::mutex> console_lock(m_ConsoleMutex);
			std::cout << "The thread #" << nThreadId << " get next task. Quantity of the active threads = "
					  << ++m_nNumOfActThreads << "\n";
		}
        task();
        
		{
			std::lock_guard<std::mutex> console_lock(m_ConsoleMutex);
			std::cout << "The thread #" << nThreadId << " finished its task. Quantity of the active threads = "
					  << --m_nNumOfActThreads << "\n";
		}
        if(!m_nNumOfActThreads && m_Tasks.empty())
        {
			std::lock_guard<std::mutex> console_lock(m_ConsoleMutex);
            std::cout << "\nAll tasks are finished!\n\n";
        }
    }
	std::lock_guard<std::mutex> console_lock(m_ConsoleMutex);
    std::cout << "The thread #" << nThreadId << " finished its work.\n";
}
