#pragma once

#include <cassert>
#include <initializer_list>
#include <iostream>

namespace getp {

template <class T> class list {
private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node();
    Node(const T &value);
  };

  Node impl;
  std::size_t size_;

public:
  class iterator {
  private:
    Node *current;

  public:
    iterator(Node *node);
    iterator(const iterator &other);

    T &operator*() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    bool operator!=(const iterator &other) const;
  };

  // Begin: Another types of iterator
  class const_iterator {
  private:
    const Node *current;

  public:
    const_iterator(const Node *node);
    const_iterator(const const_iterator &other);

    const T &operator*() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    bool operator!=(const const_iterator &other) const;
  };

  template <class _It>
  class reverse_iterator  {
  private:
    _It iter;

  public:
    reverse_iterator (_It iter);
    auto &operator*() const;
    reverse_iterator &operator++();
    reverse_iterator operator++(int);
    bool operator!=(const reverse_iterator &other) const;
  };
  // End

  list();
  list(const list &other);
  list(std::initializer_list<T> initList);
  ~list();

  list &operator=(const list &other);

  void push_back(const T &value);
  void push_front(const T &value);
  void pop_back();
  void pop_front();
  void emplace_back(T &&value);
  void emplace_front(T &&value);

  std::size_t size() const;

  void print() const;
  void clear();

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  reverse_iterator<iterator> rbegin();
  reverse_iterator<iterator> rend();
  reverse_iterator<const_iterator> crbegin() const;
  reverse_iterator<const_iterator> crend() const;
};

} // namespace getp
