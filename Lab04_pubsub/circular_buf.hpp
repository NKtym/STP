#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>

class Circularbuf {
 public:
  explicit Circularbuf(size_t capacity);
  void push(int value);
  int pop();
  size_t size();

 private:
  size_t capacity;
  std::queue<int> buf;
  std::mutex mtx;
  std::condition_variable cv_push, cv_pop;
};