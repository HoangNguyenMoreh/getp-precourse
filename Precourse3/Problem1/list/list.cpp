#include "list.h"

// Explicit instantiation
template class getp::list<int>;
template class getp::list<float>;
template class getp::list<double>;

namespace getp {

// Node implementation
template <class T>
list<T>::Node::Node() {
  next = nullptr;
  prev = nullptr;
}

template <class T>
list<T>::Node::Node(const T &value) {
  // TODO : FILL IN HERE
  data = value;
  next = nullptr;
  prev = nullptr;
}

// iterator implementation
template <class T> list<T>::iterator::iterator(Node *node) {
  // TODO : FILL IN HERE
  current = node;
}

template <class T> list<T>::iterator::iterator(const iterator &other) {
  current = other.current;
}

template <class T> T &list<T>::iterator::operator*() const {
  // TODO : FILL IN HERE
  assert(current != nullptr);
  return current->data;
}

template <class T> typename list<T>::iterator &list<T>::iterator::operator++() {
  // TODO : FILL IN HERE
  assert(current != nullptr);
  current = current->next;
  return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator++(int) {
  // TODO : FILL IN HERE
  list<T>::iterator tmp = list<T>::iterator(current);
  ++(*this);
  return tmp;
}

template <class T> typename list<T>::iterator &list<T>::iterator::operator--() {
  assert(current != nullptr);
  current = current->prev;
  return *this;
}

template <class T>
bool list<T>::iterator::operator!=(const iterator &other) const {
  // TODO : FILL IN HERE
  return this->current != other.current;
}

// constant iterator implementation
template <class T> list<T>::const_iterator::const_iterator(const Node *node) {
  // TODO : FILL IN HERE
  current = node;
}

template <class T> list<T>::const_iterator::const_iterator(const const_iterator &other) {
  current = other.current;
}

template <class T> const T &list<T>::const_iterator::operator*() const {
  // TODO : FILL IN HERE
  assert(current != nullptr);
  return current->data;
}

template <class T> typename list<T>::const_iterator &list<T>::const_iterator::operator++() {
  // TODO : FILL IN HERE
  assert(current != nullptr);
  current = current->next;
  return *this;
}

template <class T>
typename list<T>::const_iterator list<T>::const_iterator::operator++(int) {
  // TODO : FILL IN HERE
  list<T>::const_iterator tmp = list<T>::const_iterator(current);
  ++(*this);
  return tmp;
}

template <class T> typename list<T>::const_iterator &list<T>::const_iterator::operator--() {
  // TODO : FILL IN HERE
  assert(current != nullptr);
  current = current->prev;
  return *this;
}

template <class T>
bool list<T>::const_iterator::operator!=(const const_iterator &other) const {
  // TODO : FILL IN HERE
  return this->current != other.current;
}

// reverse iterator implementation
template <class T>
template <class _It>
list<T>::reverse_iterator<_It>::reverse_iterator(_It iter) : iter(iter) {}

template <class T>
template <class _It>
auto &list<T>::reverse_iterator<_It>::operator*() const{
  _It tmp = iter;
  --tmp;
  return *tmp;
}

template <class T>
template <class _It>
typename list<T>::reverse_iterator<_It> &list<T>::reverse_iterator<_It>::operator++() {
    --iter;
    return *this;
}

template <class T>
template <class _It>
typename list<T>::reverse_iterator<_It> list<T>::reverse_iterator<_It>::operator++(int) {
    reverse_iterator<_It> temp = *this;
    --iter;
    return temp;
}

template <class T>
template <class _It>
bool list<T>::reverse_iterator<_It>::operator!=(const reverse_iterator& other) const {
    return iter != other.iter;
}

// Rest of the list class implementation
template <class T> list<T>::list(){
  // TODO : FILL IN HERE
  impl.next = &impl;
  impl.prev = &impl;
  size_ = 0;
}

template <class T>
list<T>::list(const list &other) {
  // TODO : FILL IN HERE
  impl.next = impl.prev = &impl;
  size_ = 0;
  list<T>::Node *current = other.impl.next;
  while (current != &other.impl)
  {
    this->push_back(current->data);
    current = current->next;
  }
}

template <class T>
list<T>::list(std::initializer_list<T> initList) {
  // TODO : FILL IN HERE
  impl.next = impl.prev = &impl;
  size_ = 0;
  for(T item: initList)
    this->push_back(item);
}

template <class T> list<T>::~list() { 
  // TODO : FILL IN HERE
  clear();
}

template <class T> list<T> &list<T>::operator=(const list &other) {
  // TODO : FILL IN HERE
  if (this != &other)
  {
    clear();
    list<T>::Node *current = other.impl.next;
    while (current != &other.impl)
    {
      this->push_back(current->data);
      current = current->next;
    }
  }
  return *this;
}

template <class T> void list<T>::push_back(const T &value) {
  // TODO : FILL IN HERE
  list<T>::Node *new_node = new list<T>::Node(value);
  if (impl.next == &impl) 
  {
    impl.next = impl.prev = new_node;
  }
  else 
  {
    impl.prev->next = new_node;
    new_node->prev = impl.prev;
    impl.prev = new_node;
    new_node->next = &impl;
  }
  size_++;
}

template <class T> void list<T>::push_front(const T &value) {
  // TODO : FILL IN HERE
  list<T>::Node *new_node = new list<T>::Node(value);
  if (impl.next == &impl)
  {
    impl.next = impl.prev = new_node;
  }
  else
  {
    impl.next->prev = new_node;
    new_node->next = impl.next;
    impl.next = new_node;
    new_node->prev = &impl;
  }
  size_++;
}

template <class T> void list<T>::pop_back() {
  // TODO : FILL IN HERE
  if (impl.prev == &impl) return;

  list<T>::Node *old_node = impl.prev;
  if (impl.next == impl.prev)
  {
    impl.next = impl.prev = &impl;
  }
  else
  {
    impl.prev = old_node->prev;
    old_node->prev->next = &impl;
  }

  delete old_node;
  size_--;
}

template <class T> void list<T>::pop_front() {
  // TODO : FILL IN HERE
  if (impl.next == &impl) return;

  list<T>::Node *old_node = impl.next;
  if (impl.next == impl.prev)
  {
    impl.next = impl.prev = &impl;
  }
  else
  {
    impl.next = old_node->next;
    old_node->next->prev = &impl;
  }

  delete old_node;
  size_--;
}

template <class T> void list<T>::emplace_back(T &&value) {
  // TODO : FILL IN HERE
  push_back(std::move(value));
}

template <class T> void list<T>::emplace_front(T &&value) {
  // TODO : FILL IN HERE
  push_front(std::move(value));
}

template <class T> std::size_t list<T>::size() const {
  // TODO : FILL IN HERE
  return size_;
}

template <class T> void list<T>::print() const {
  // TODO : FILL IN HERE
  list<T>::Node *current = impl.next;
  while (current != &impl)
  {
    std::cout<<current->data<<" ";
    current = current->next;
  }
  std::cout<<std::endl;
  
}

template <class T> void list<T>::clear() {
  // TODO : FILL IN HERE
  list<T>::Node *current = impl.next;
  while (current != &impl)
  {
    list<T>::Node *next_ = current->next;
    delete current;
    current = next_;
  }
  impl.next = impl.prev = &impl;
  size_ = 0;
}

template <class T> typename list<T>::iterator list<T>::begin() {
  // TODO : FILL IN HERE
  return list<T>::iterator(impl.next);
}

template <class T> typename list<T>::iterator list<T>::end() {
  // TODO : FILL IN HERE
  return list<T>::iterator(&impl);
}

template <class T> typename list<T>::const_iterator list<T>::cbegin() const {
  // TODO : FILL IN HERE
  return list<T>::const_iterator(impl.next);
}

template <class T> typename list<T>::const_iterator list<T>::cend() const {
  // TODO : FILL IN HERE
  return list<T>::const_iterator(&impl);
}

template <class T> typename list<T>::reverse_iterator<typename list<T>::iterator> list<T>::rbegin() {
  // TODO : FILL IN HERE
  return list<T>::reverse_iterator<list<T>::iterator>(end());
}

template <class T> typename list<T>::reverse_iterator<typename list<T>::iterator> list<T>::rend() {
  // TODO : FILL IN HERE
  return list<T>::reverse_iterator<list<T>::iterator>(begin());
}

template <class T> typename list<T>::reverse_iterator<typename list<T>::const_iterator> list<T>::crbegin() const {
  // TODO : FILL IN HERE
  return list<T>::reverse_iterator<list<T>::const_iterator>(cend());
}

template <class T> typename list<T>::reverse_iterator<typename list<T>::const_iterator> list<T>::crend() const {
  // TODO : FILL IN HERE
  return list<T>::reverse_iterator<list<T>::const_iterator>(cbegin());
}

} // namespace getp
