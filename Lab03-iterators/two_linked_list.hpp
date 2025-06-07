#pragma once
#include <cstddef>
#include <iterator>
#include <stdexcept>

template <typename T>
class LinkedList {
 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(const T& input_data) {
      data = input_data;
      prev = nullptr;
      next = nullptr;
    }
  };
  Node* head;
  Node* tail;
  std::size_t cnt;

 public:
  LinkedList() : head(nullptr), tail(nullptr), cnt(0) {}
  template <typename It>
  LinkedList(It begin, It end) : head(nullptr), tail(nullptr), cnt(0) {
    for (auto it = begin; it != end; it++)
      push_back(*it);
  }
  LinkedList(const LinkedList& in_ll) : head(nullptr), tail(nullptr), cnt(0) {
    for (Node* i = in_ll.head; i != nullptr; i = i->next)
      push_back(i->data);
  }
  LinkedList(LinkedList&& in_ll)
      : head(in_ll.head), tail(in_ll.tail), cnt(in_ll.cnt) {
    in_ll.head = in_ll.tail = nullptr;
    in_ll.cnt = 0;
  }
  LinkedList& operator=(const LinkedList& in_ll) {
    if (this != &in_ll) {
      clear();
      for (Node* curr = in_ll.head; curr != nullptr; curr = curr->next)
        push_back(curr->data);
    }
    return *this;
  }
  LinkedList& operator=(LinkedList&& in_ll) noexcept {
    if (this != &in_ll) {
      clear();
      head = in_ll.head;
      tail = in_ll.tail;
      cnt = in_ll.cnt;
      in_ll.head = in_ll.tail = nullptr;
      in_ll.cnt = 0;
    }
    return *this;
  }
  ~LinkedList() { clear(); }
  T& front() {
    if (empty())
      throw std::out_of_range("Список пуст");
    return head->data;
  }
  const T& front() const {
    if (empty())
      throw std::out_of_range("Список пуст");
    return head->data;
  }
  T& back() {
    if (empty())
      throw std::out_of_range("Список пуст");
    return tail->data;
  }
  const T& back() const {
    if (empty())
      throw std::out_of_range("Список пуст");
    return tail->data;
  }
  void push_front(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    if (head)
      head->prev = newNode;
    head = newNode;
    if (!tail)
      tail = newNode;
    cnt++;
  }
  void push_back(const T& value) {
    Node* newNode = new Node(value);
    newNode->prev = tail;
    if (tail)
      tail->next = newNode;
    tail = newNode;
    if (!head)
      head = newNode;
    cnt++;
  }
  bool empty() const { return cnt == 0; }
  std::size_t size() const { return cnt; }
  void clear() {
    while (cnt) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
      cnt--;
    }
  }
  class iterator {
    friend class LinkedList;

   private:
    Node* current;
    Node* tail;

   public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::bidirectional_iterator_tag;
    iterator(Node* ptr, Node* tail_ptr) : current(ptr), tail(tail_ptr) {}
    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }
    iterator& operator++() {
      current = current->next;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      current = current->next;
      return tmp;
    }
    iterator& operator--() {
      if (current == nullptr) {
        current = tail;
      } else {
        current = current->prev;
      }
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      current = current->prev;
      return tmp;
    }
    bool operator==(const iterator& in_ll) const {
      return current == in_ll.current;
    }
    bool operator!=(const iterator& in_ll) const {
      return current != in_ll.current;
    }
  };

  class const_iterator {
    friend class LinkedList;

   private:
    const Node* current;

   public:
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = const T*;
    using reference = const T&;
    using iterator_category = std::bidirectional_iterator_tag;
    const_iterator(const Node* ptr = nullptr) : current(ptr) {}
    const_iterator(const iterator& it) : current(it.current) {}
    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }
    const_iterator& operator++() {
      current = current->next;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      current = current->next;
      return tmp;
    }
    const_iterator& operator--() {
      current = current->prev;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      current = current->prev;
      return tmp;
    }
    bool operator==(const const_iterator& in_ll) const {
      return current == in_ll.current;
    }
    bool operator!=(const const_iterator& in_ll) const {
      return current != in_ll.current;
    }
  };
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  iterator begin() { return iterator(head, tail); }
  iterator end() { return iterator(nullptr, tail); }
  const_iterator begin() const { return const_iterator(head); }
  const_iterator end() const { return const_iterator(nullptr); }
  const_iterator cbegin() const { return const_iterator(head); }
  const_iterator cend() const { return const_iterator(nullptr); }
  reverse_iterator rbegin() { return reverse_iterator(tail); }
  reverse_iterator rend() { return reverse_iterator(nullptr); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(tail); }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(nullptr);
  }
  const_reverse_iterator crbegin() const {
    return const_reverse_iterator(tail);
  }
  const_reverse_iterator crend() const {
    return const_reverse_iterator(nullptr);
  }
};

// https://pvs-studio.ru/ru/blog/terms/6683/