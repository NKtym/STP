#include "circular_buf.hpp"

Circularbuf::Circularbuf(size_t capacity) : capacity(capacity) {}

void Circularbuf::push(int value) {
  std::unique_lock<std::mutex> lock(mtx);
  cv_push.wait(lock, [this] { return buf.size() < capacity; });
  buf.push(value);
  cv_pop.notify_one();
}

int Circularbuf::pop() {
  std::unique_lock<std::mutex> lock(mtx);
  cv_pop.wait(lock, [this] { return !buf.empty(); });
  int value = buf.front();
  buf.pop();
  cv_push.notify_one();
  return value;
}

size_t Circularbuf::size() {
  std::lock_guard<std::mutex> lock(mtx);
  return buf.size();
}