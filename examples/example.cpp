#include <thread-pool/thread_pool.h>
#include <iostream>

std::mutex mutex;

void print_status(
    const int task_number, 
    const std::string& status)
{
    std::unique_lock<std::mutex> lock(mutex);
    std::cerr <<  task_number << " " << status << std::endl;
}

void work(const int task_number)
{
    int x;
    print_status(task_number, "started");
    for(int i = 0; i < 1000; i++)
    {
        x = i * i;
    }
    print_status(task_number, "done");
}

int main(int argc, char** argv)
{
    cpp::thread_pool tpool;
    for(int i = 0; i < 100; i++)
    {
        tpool.submit(work,i);
    }
    return 0;
}