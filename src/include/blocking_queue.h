/**
 * File blocking_queue.h
 * Author: John Patek
 * Email: johnpatek2@gmail.com
 */

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>
#include <deque>

namespace cpp
{

    template<class T, class Container = std::deque<T>>class blocking_queue
    {
    public:
        using container = typename std::queue<T, Container>::container_type;
        using value_type = typename std::queue<T, Container>::value_type;
        using size_type = typename std::queue<T, Container>::size_type;
        using reference = typename std::queue<T, Container>::reference;
        using const_reference = typename std::queue<T, Container>::const_reference;

        blocking_queue() = default;
        blocking_queue(const blocking_queue& orig) = default;
        blocking_queue(blocking_queue&& value) = default;

        bool empty() const
        {
            return m_queue.empty();
        }

        size_type size()
        {
            return m_queue.size();
        }

        void put(const value_type& value)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.push(value);
            m_condition_variable.notify_one();
        }

        void put(value_type&& value)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.push(value);
            m_condition_variable.notify_one();
        }

        template<class... Args > void put(Args&&... args)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_queue.emplace(args...);
            m_condition_variable.notify_one();
        }

        value_type take()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            while (m_queue.empty())
            {
                m_condition_variable.wait(lock);
            }
            auto result = std::move(m_queue.front());
            m_queue.pop();
            return result;
        }
    private:
        std::condition_variable m_condition_variable;
        std::mutex m_mutex;
        std::queue<T, Container> m_queue;
    };
}
#endif /* BLOCKING_QUEUE_H */

