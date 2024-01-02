#pragma once

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <queue>
#include <vector>

namespace getp {

template <class T>
class priority_queue {
private:
  std::vector<T> data;
  std::greater<T> compare;

public:
  priority_queue();
  ~priority_queue();
  void push( const T& value );
  const T& top() const;
  void pop();
};

template <class T>
priority_queue<T>::priority_queue() {}

template <class T>
priority_queue<T>::~priority_queue() {}

template <class T>
void priority_queue<T>::push(const T &value) {
  data.push_back(value);

  size_t index = data.size() - 1;
  while (index > 0) {
    size_t parent = (index - 1) / 2;
    if (!compare(data[index], data[parent]))
        break;
    std::swap(data[index], data[parent]);
    index = parent;
  }
}

template <class T>
const T& priority_queue<T>::top() const {
  return data.front();
}

template <class T>
void priority_queue<T>::pop() {
  if (!data.empty()) {
    std::swap(data.front(), data.back());
    data.pop_back();
    
    size_t size = data.size();
    size_t index = 0;
    while (true) {
        size_t leftChild = 2 * index + 1;
        size_t rightChild = 2 * index + 2;
        size_t smallest = index;

        if (leftChild < size && compare(data[leftChild], data[smallest]))
            smallest = leftChild;

        if (rightChild < size && compare(data[rightChild], data[smallest]))
            smallest = rightChild;

        if (smallest == index)
            break;

        std::swap(data[index], data[smallest]);
        index = smallest;
    }
  }
}

} // namespace getp
