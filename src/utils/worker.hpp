#ifndef RIKKI_PATCHER_UTILS_WORKER_HPP
#define RIKKI_PATCHER_UTILS_WORKER_HPP
#include "precompiled.hpp"

class Worker {
public:
    bool is_running() const;
    void enqueue(const std::function<void()>& fn);

    void start();
    void stop();
private:
    void worker_thread();

public:
    explicit Worker(size_t threads);
    ~Worker();
private:
    std::atomic<bool> m_isRunning;
    const size_t m_threads;
    std::vector<std::thread> m_workers;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};


#endif //RIKKI_PATCHER_UTILS_WORKER_HPP
