#include "thread_pool.hpp"

thread_pool::thread_pool(size_t num_threads) {
  for (size_t i = 0; i < num_threads; i++) {
    std::thread t([this] {
      while (true) {
        std::function<void()> task;
        std::unique_lock<std::mutex> lock(this->mtx);
        this->condition.wait(
            lock, [this] { return this->stop || !this->tasks.empty(); });
        if (this->stop && this->tasks.empty())
          return;
        task = std::move(this->tasks.front());
        this->tasks.pop();
        lock.unlock();
        task();
      }
    });
    threads.push_back(std::move(t));
  }
}

thread_pool::~thread_pool() {
  std::unique_lock<std::mutex> lock(mtx);
  stop = true;
  lock.unlock();
  condition.notify_all();
  for (std::thread& thread : threads)
    thread.join();
}