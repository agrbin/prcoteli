#ifndef IMPL_DUMMY_ARRAY_KEYED_DYNAMIC_ARRAY_HPP_
#define IMPL_DUMMY_ARRAY_KEYED_DYNAMIC_ARRAY_HPP_

#include <iterator>
#include <list>

namespace dummy {

using namespace std;

template <typename T>
class KeyedDynamicArray {
 public:
  typedef typename list<T>::iterator key_type;
  typedef T value_type;

  KeyedDynamicArray() {}

  KeyedDynamicArray(int n) {
    for (int i = 0; i < n; ++i) a.emplace_back();
  }

  template <typename A>
  KeyedDynamicArray(A const& array) {
    for (int i = 0; i < array.size(); ++i) a.push_back(array[i]);
  }

  int size() const { return a.size(); }

  value_type const& operator[](int index) const {
    auto it = a.begin();
    advance(it, index);
    return *it;
  }

  value_type& operator[](int index) {
    auto it = a.begin();
    advance(it, index);
    return *it;
  }

  key_type Insert(int index, value_type value) {
    auto it = a.begin();
    advance(it, index);
    a.insert(it, value);
    return --it;
  }

  key_type InsertAfterKey(key_type key, value_type value) {
    auto it = key;
    a.insert(++it, value);
    return --it;
  }

  key_type InsertBeforeKey(key_type key, value_type value) {
    auto it = key;
    a.insert(it, value);
    return --it;
  }

  void Remove(int index) {
    auto it = a.begin();
    advance(it, index);
    a.erase(it);
  }

  void RemoveKey(key_type key) { a.erase(key); }

  value_type const& Get(key_type key) const { return *key; }
  value_type& Get(key_type key) { return *key; }

  int GetIndex(key_type key) const {
    int index = 0;
    for (; key != a.begin(); --key) {
      index += 1;
    }
    return index;
  }

 private:
  list<value_type> a;
};

}  // namespace dummy

#endif  // IMPL_DUMMY_ARRAY_KEYED_DYNAMIC_ARRAY_HPP_
