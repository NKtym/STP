#pragma once

template <typename T>
class UniquePtr {
 private:
  T* ptr;

  void release() {
    delete ptr;
    ptr = nullptr;
  }

 public:
  explicit UniquePtr(T* p = nullptr) { ptr = p; }

  ~UniquePtr() { release(); }

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  UniquePtr(UniquePtr&& p) {
    ptr = p.ptr;
    p.ptr = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& p) {
    if (&p != this) {
      release();
      ptr = p.ptr;
      p.ptr = nullptr;
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
    }
  }
};