#include "thread_pool.h"
#include <windows.h>
#include <iostream>
#include <unordered_set>

class keyboard_listener
{
public:

    virtual void on_key_press(int key_code)
    {
        std::cout << "key pressed: " << key_code << std::endl;
    }

    virtual void on_key_release(int key_code)
    {
        std::cout << "key released: " << key_code << std::endl;
    }
};

class keyboard_manager
{
public:
    keyboard_manager() = default;

    ~keyboard_manager()
    {
        if (is_active())
        {
            shutdown();
        }
    }

    void run()
    {
        bool loop = true;
        while (loop)
        {
            for (auto key_code : m_key_codes)
            {
                auto key_state = GetAsyncKeyState(key_code);

                if (key_state & 0x8000)
                {
                    if (key_code == VK_ESCAPE)
                    {
                        loop = false;
                    } else
                    {
                        for (auto& key_listener : m_key_listeners)
                        {
                            auto key_event = std::make_tuple(key_listener, key_code);
                            m_thread_pool.submit(
                                    [key_event]
                                    {
                                        auto listener = std::get<0>(key_event);
                                        auto code = std::get<1>(key_event);
                                        listener->on_key_press(code);
                                    });
                        }
                    }
                }
            }
        }
        shutdown();
    }

    bool is_active()
    {
        m_thread_pool.is_active();
    }

    void shutdown()
    {
        m_thread_pool.shutdown();
    }

    void add_keyboard_listener(std::shared_ptr<keyboard_listener>&& keyboard_listener)
    {
        m_key_listeners.push_back(std::move(keyboard_listener));
        std::cout << "LISTENER ADDED" << std::endl;
    }

    void add_keyboard_listener(const std::shared_ptr<keyboard_listener>& keyboard_listener)
    {
        m_key_listeners.push_back(keyboard_listener);
        std::cout << "LISTENER ADDED" << std::endl;
    }
private:
    int m_key_codes[5] = {VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_ESCAPE};
    std::vector<std::shared_ptr<keyboard_listener>> m_key_listeners;
    cppx::thread_pool m_thread_pool;
};

class keyboard_handler : public keyboard_listener
{
public:

    keyboard_handler()
    {
        std::cout << "HANDLER CREATED" << std::endl;
    }

    ~keyboard_handler()
    {
        std::cout << "HANDLER DESTROYED" << std::endl;
    }
};

int main(int argc, char** argv)
{
    keyboard_manager manager;
    std::shared_ptr<keyboard_listener> handler(new keyboard_handler());
    manager.add_keyboard_listener(handler);
    manager.run();
    return 0;
}
