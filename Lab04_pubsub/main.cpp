#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include "circular_buf.hpp"

void publisher(Circularbuf& buf, double mean, double stddev) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> d(mean, stddev);
  while (true) {
    int n = std::round(d(gen));
    auto start = std::chrono::high_resolution_clock::now();
    buf.push(n);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> wait_time = end - start;
    std::cout << "[Publisher] Push: " << n << " | Wait: " << wait_time.count()
              << "s\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
  }
}

void subscriber(Circularbuf& buf, double mean, double stddev) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> d(mean, stddev);
  while (true) {
    int n = buf.pop();
    int s = std::round(d(gen));
    std::cout << "[Subscriber] Pop: " << n << " | Buf size: " << buf.size()
              << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(s));
  }
}

int main(int argc, char* argv[]) {
  if (argc != 6) {
    std::cerr << "Ошибка: неверная структура входных данных(<buf_cap> "
                 "<pub_mean> <pub_stddev> <sub_mean> <sub_stddev>)\n";
    return 1;
  }
  size_t buf_cap = std::stoi(argv[1]);
  double pub_mean = std::stod(argv[2]);
  double pub_stddev = std::stod(argv[3]);
  double sub_mean = std::stod(argv[4]);
  double sub_stddev = std::stod(argv[5]);
  Circularbuf buf(buf_cap);
  std::thread pub_thread(publisher, std::ref(buf), pub_mean, pub_stddev);
  std::thread sub_thread(subscriber, std::ref(buf), sub_mean, sub_stddev);
  pub_thread.join();
  sub_thread.join();
  return 0;
}
