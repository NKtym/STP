#include <cmath>
#include <iostream>
#include "thread_pool.hpp"

double estimate_pi(size_t iterations) {
  size_t in_circle = 0;
  for (size_t i = 0; i < iterations; i++) {
    double x = (double)rand() / RAND_MAX;
    double y = (double)rand() / RAND_MAX;
    if (x * x + y * y <= 1.0)
      in_circle++;
  }
  return 4.0 * in_circle / iterations;
}

int main() {
  size_t num_threads;
  std::cout << "Введите количество потоков: ";
  std::cin >> num_threads;
  thread_pool pool(num_threads);
  std::vector<std::future<double>> res;
  size_t iterations = 100000;
  size_t iteration_thread = iterations / num_threads;
  for (size_t i = 0; i < num_threads; i++) {
    res.push_back(pool.enqueue(estimate_pi, iteration_thread));
  }
  double pi = 0;
  for (auto& f : res)
    pi += f.get();
  pi /= num_threads;
  std::cout << pi << '\n';
  return 0;
}