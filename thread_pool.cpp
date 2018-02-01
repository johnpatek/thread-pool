#include <iostream>

#include "thread_pool.h"

cppx::thread_pool::thread_pool(const size_type pool_size)
{
    if (pool_size > 0)
    {
        m_active = true;
        m_threads.reserve(pool_size);
        while (m_threads.size() < pool_size)
        {
            m_threads.emplace_back(
                    [this]
                    {
                        std::function<void() > task;
                        while (m_active)
                        {
                            while (!m_task_queue.empty())
                            {
                                task = m_task_queue.take();
                                        task();
                            }
                            std::this_thread::yield();
                        }
                        std::cout << "shutting down!" << std::endl;
                    });
        }
    }
}

cppx::thread_pool::~thread_pool()
{
    if (is_active())
    {
        shutdown();
    }
}

bool cppx::thread_pool::is_active() const
{
    return m_active;
}

void cppx::thread_pool::shutdown()
{
    m_active = false;
    for (auto& thread : m_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}