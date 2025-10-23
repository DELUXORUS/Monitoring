#ifndef THREADGUARD_H
#define THREADGUARD_H

#include <thread>


class ThreadGuard
{
public:
    template <typename Callable, typename ...Args>
    explicit ThreadGuard(Callable&& func, Args&& ...args)
                        : t_(std::forward<Callable>(func),
                             std::forward<Args>(args)...) {}
    explicit ThreadGuard(std::thread t) noexcept
                        : t_(std::move(t)) {}
    explicit ThreadGuard(ThreadGuard&& other) noexcept
                        : t_(std::move(other.t_)) {}
    ~ThreadGuard();

    ThreadGuard(const ThreadGuard& t) = delete;
    ThreadGuard& operator=(const ThreadGuard& t) = delete;
private:
    std::thread t_;
};

#endif // THREADGUARD_H
