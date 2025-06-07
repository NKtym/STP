#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class thread_pool {
 private:
  std::vector<std::thread> threads;
  std::queue<std::function<void()>> tasks;
  std::mutex mtx;
  std::condition_variable condition;
  bool stop = false;

 public:
  thread_pool(size_t num_threads);
  ~thread_pool();
  template <typename Func, typename... Args>
  auto enqueue(Func&& f, Args&&... args) -> std::future<decltype(f(args...))>;
};

template <typename Func, typename... Args>
auto thread_pool::enqueue(Func&& f, Args&&... args)
    -> std::future<decltype(f(args...))> {
  auto task = std::make_shared<std::packaged_task<decltype(f(args...))()>>(
      std::bind(std::forward<Func>(f), std::forward<Args>(args)...));
  std::future<decltype(f(args...))> res = task->get_future();
  std::unique_lock<std::mutex> lock(mtx);
  if (stop)
    throw std::runtime_error("thread_pool остановлен");
  tasks.emplace([task]() { (*task)(); });
  lock.unlock();
  condition.notify_one();
  return res;
}
