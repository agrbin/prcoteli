#ifndef IMPL_DUMMY_ARRAY_DYNAMIC_ARRAY_HPP_
#define IMPL_DUMMY_ARRAY_DYNAMIC_ARRAY_HPP_

#include <vector>

namespace dummy {

using namespace std;

template <typename T>
class DynamicArray {
 public:
  typedef T value_type;

  DynamicArray() {}

  DynamicArray(int n) : a(n) {}

  template <typename A>
  DynamicArray(A const& array) {
    for (int i = 0; i < array.size(); ++i) a.push_back(array[i]);
  }

  int size() const { return a.size(); }

  value_type const& operator[](int index) const { return a[index]; }

  value_type& operator[](int index) { return a[index]; }

  void Insert(int index, value_type value) {
    a.insert(a.begin() + index, value);
  }

  void Remove(int index) { a.erase(a.begin() + index); }

 private:
  vector<value_type> a;
};

}  // namespace dummy

#endif  // IMPL_DUMMY_ARRAY_DYNAMIC_ARRAY_HPP_
