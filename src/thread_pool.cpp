/**
 * File thread_pool.cpp
 * Author: John Patek
 * Email: johnpatek2@gmail.com
 */

#include <iostream>

#include "thread-pool/thread_pool.h"

cpp::thread_pool::thread_pool(const size_type pool_size)
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
                    });
        }
    }
}

cpp::thread_pool::~thread_pool()
{
    if (is_active())
    {
        shutdown();
    }
}

bool cpp::thread_pool::is_active() const
{
    return m_active;
}

void cpp::thread_pool::execute(std::function<void()> function)
{
    m_task_queue.put(function);
}

void cpp::thread_pool::shutdown()
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