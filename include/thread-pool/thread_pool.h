/**
 * File thread_pool.h
 * Author: John Patek
 * Email: johnpatek2@gmail.com
 */

#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include "thread-pool/blocking_queue.h"

namespace cpp
{

    class thread_pool
    {
    public:
        using size_type = typename blocking_queue<std::function<void() >>::size_type;

        thread_pool(const size_type pool_size = std::thread::hardware_concurrency());

        ~thread_pool();

        size_type size() const;

        bool is_active() const;

        void execute(std::function<void()> function);
        
        template<class F, class... Args> auto submit(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>
        {
            using return_type = typename std::result_of < F(Args...)>::type;

            auto task = std::make_shared < std::packaged_task < return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

            std::future<return_type> result = task->get_future();
            m_task_queue.put([task]()
            {
                (*task)();
            });

            return result;
        }

        void shutdown();

    private:
        std::vector<std::thread> m_threads;
        cpp::blocking_queue<std::function<void() >> m_task_queue;
        bool m_active;
    };
}
#endif /* THREAD_POOL_H */