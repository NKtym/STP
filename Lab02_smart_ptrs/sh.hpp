#pragma once
#include <cstddef>
#include <iostream>

template <typename T>
class SharedPtr {
 private:
  T* ptr;
  size_t* cnt;
  void release() {
    if (cnt) {
      (*cnt)--;
      if (*cnt == 0) {
        delete ptr;
        delete cnt;
      }
    }
  }

 public:
  explicit SharedPtr(T* p) {
    ptr = p;
    cnt = new size_t(1);
  }

  ~SharedPtr() { release(); }

  SharedPtr(const SharedPtr& p) {
    ptr = p.ptr;
    cnt = p.cnt;
    if (cnt) {
      (*cnt)++;
    }
  }

  SharedPtr& operator=(const SharedPtr& p) {
    if (&p != this) {
      release();
      ptr = p.ptr;
      cnt = p.cnt;
      (*cnt)++;
    }
    return *this;
  }

  SharedPtr(SharedPtr&& p) {
    ptr = p.ptr;
    cnt = p.cnt;
    p.ptr = nullptr;
    p.cnt = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& p) {
    if (this != &p) {
      release();
      ptr = p.ptr;
      cnt = p.cnt;
      p.ptr = nullptr;
      p.cnt = nullptr;
    }
    return *this;
  }

  T& operator*() const { return *ptr; }

  T* operator->() const { return ptr; }

  T* get() const { return ptr; }

  void reset(T* p = nullptr) {
    if (p != ptr) {
      release();
      ptr = p;
      cnt = new size_t(1);
    }
  }

  std::size_t use_count() const {
    if (cnt)
      return *cnt;
    else
      return 0;
  }
};