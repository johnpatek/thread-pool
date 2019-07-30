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

#include "blocking_queue.h"
namespace thread_pool
{

template<class F,class... Args> class callable_task
{
public:
    using return_type = typename std::result_of < F(Args...)>::type;
    
};

class runnable_task
{

};

class thread_pool
{

};

}
#endif /* THREAD_POOL_H */

