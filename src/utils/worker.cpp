#include "worker.hpp"

bool Worker::is_running() const {
    return m_isRunning;
}

void Worker::enqueue(const std::function<void()>& fn) {
    std::unique_lock<std::mutex> lock(m_mtx);

    if (!m_isRunning) {
        return;
    }

    m_tasks.emplace(std::move(fn));
    lock.unlock();

    m_cv.notify_one();
}

void Worker::start() {
    std::unique_lock<std::mutex> lock(m_mtx);

    if (m_isRunning) {
        return;
    }

    m_isRunning = true;

    for (size_t i = 0; i < m_threads; i++) {
        m_workers.emplace_back(&Worker::worker_thread, this);
    }
}

void Worker::stop() {
    std::unique_lock<std::mutex> lock(m_mtx);

    if (!m_isRunning) {
        return;
    }

    m_isRunning = false;

    for (auto& it : m_workers) {
        it.detach();
    }

    lock.unlock();
    m_cv.notify_all();

    for (auto& it : m_workers) {
        while (it.joinable()) { }
    }

    m_workers.clear();
    m_tasks = std::queue<std::function<void()>>();
}

void Worker::worker_thread() {
    while (true) {
        std::unique_lock<std::mutex> lock(m_mtx);

        m_cv.wait(lock, [this] {
            return !m_isRunning || !m_tasks.empty();
        });

        if (!m_isRunning) {
            return;
        }

        auto task = std::move(m_tasks.front());
        m_tasks.pop();
        lock.unlock();

        task();
    }
}

Worker::Worker(size_t threads) :
        m_isRunning(false),
        m_threads(threads) { }

Worker::~Worker() {
    if (m_isRunning) {
        this->stop();
    }
}
