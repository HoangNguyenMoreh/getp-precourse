#include "vector.h"

namespace getp {

template <typename T>
vector<T>::vector() {
  // TODO : FILL IN HERE
  data_ = nullptr;
  size = 0;
  capacity = 0;
}

template <typename T> vector<T>::~vector() { 
  // TODO : FILL IN HERE
  delete[] data_;
}

template <typename T>
vector<T>::vector(const vector &other) {
  // TODO : FILL IN HERE
  data_ = new T[other.capacity];
  size = other.size;
  capacity = other.capacity;
  std::copy(other.data_, other.data_ + size, data_);
}

template <typename T>
vector<T>::vector(vector &&other) noexcept { 
  // TODO : FILL IN HERE
  data_ = other.data_;
  size = other.size;
  capacity = other.capacity;

  other.data_ = nullptr;
  other.size = 0;
  other.capacity = 0;
}

template <typename T> vector<T> &vector<T>::operator=(const vector &other) {
  // TODO : FILL IN HERE
  if (this != &other)
  {
    delete data_;
    data_ = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    std::copy(other.data_, other.data_ + size, data_);
  }
  return *this;
}

template <typename T> vector<T> &vector<T>::operator=(vector &&other) noexcept {
  // TODO : FILL IN HERE
  if (this != &other)
  {
    delete data_;
    data_ = other.data_;
    size = other.size;
    capacity = other.capacity;

    other.data_ = nullptr;
    other.size = 0;
    other.capacity = 0;
  }
  return *this;
}

template <typename T> T &vector<T>::at(size_t index) {
  // TODO : FILL IN HERE
  return data_[index];
}

template <typename T> T &vector<T>::operator[](size_t index) {
  // TODO : FILL IN HERE
  return data_[index];
}

template <typename T> T &vector<T>::front() {
  // TODO : FILL IN HERE
  return data_[0];
}

template <typename T> T &vector<T>::back() {
  // TODO : FILL IN HERE
  return data_[size - 1];
}

template <typename T> T *vector<T>::data() {
  // TODO : FILL IN HERE
  return data_;
}

template <typename T> size_t vector<T>::getSize() const {
  // TODO : FILL IN HERE
  return size;
}

template <typename T> void vector<T>::push_back(const T &value) {
  // TODO : FILL IN HERE
  if (size == capacity)
  {
    if (capacity == 0)
      reserve(1);
    else
      reserve(capacity << 1);
  }
  data_[size++] = value;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args &&... args) {
  // TODO : FILL IN HERE
  if (size == capacity)
  {
    if (capacity == 0)
      reserve(1);
    else
      reserve(capacity << 1);
  }
  new(&data_[size++]) T(std::forward<Args>(args)...);
}

template <typename T>
template <typename InputIt>
void vector<T>::append_range(InputIt first, InputIt last) {
  // TODO : FILL IN HERE
  for(auto it = first; it != last; ++it)
  {
    this->push_back(*it);
  }
}

template <typename T> void vector<T>::pop_back() {
  // TODO : FILL IN HERE
  if (size > 0) size--;
}

template <typename T> void vector<T>::reserve(size_t newCapacity) {
  // TODO : FILL IN HERE
  if (newCapacity > capacity)
  {
    T* new_data = new T[newCapacity];
    std::copy(data_, data_ + size, new_data);
    delete data_;
    data_ = new_data;
    capacity = newCapacity;
  }
}

template <typename T> T *vector<T>::begin() {
  // TODO : FILL IN HERE
  return data_;
}

template <typename T> const T *vector<T>::cbegin() const {
  // TODO : FILL IN HERE
  return data_;
}

template <typename T> T *vector<T>::end() {
  // TODO : FILL IN HERE
  return data_ + size;
}

template <typename T> const T *vector<T>::cend() const {
  // TODO : FILL IN HERE
  return data_ + size;
}

template <typename T> std::reverse_iterator<T *> vector<T>::rbegin() {
  // TODO : FILL IN HERE
  return std::reverse_iterator<T*>(this->end());
}

template <typename T>
std::reverse_iterator<const T *> vector<T>::crbegin() const {
  // TODO : FILL IN HERE
  return std::reverse_iterator<const T*>(this->cend());
}

template <typename T> std::reverse_iterator<T *> vector<T>::rend() {
  // TODO : FILL IN HERE
  return std::reverse_iterator<T*>(this->begin());
}

template <typename T>
std::reverse_iterator<const T *> vector<T>::crend() const {
  // TODO : FILL IN HERE
  return std::reverse_iterator<const T*>(this->cbegin());
}

// Explicit instantiation for supported types
template class vector<int>;
template void getp::vector<int>::emplace_back<int>(int &&);

} // namespace getp
