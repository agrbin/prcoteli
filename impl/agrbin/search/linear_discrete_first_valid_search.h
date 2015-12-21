#ifndef IMPL_AGRBIN_SEARCH_LINEAR_DISCRETE_FIRST_VALID_SEARCH_H_
#define IMPL_AGRBIN_SEARCH_LINEAR_DISCRETE_FIRST_VALID_SEARCH_H_

#include <functional>

namespace agrbin {

template <typename T>
class LinearDiscreteFirstValidSearch {
 public:
  typedef T value_type;

  LinearDiscreteFirstValidSearch(std::function<bool(T)> predicate)
      : predicate(predicate) {}

  bool FindFirstValid(value_type lo, value_type hi, value_type *result) const {
    for (value_type i = lo; i < hi; ++i) {
      if (predicate(i)) {
        *result = i;
        return true;
      }
    }
    return false;
  }

 private:
  const std::function<bool(T)> predicate;
};

}  // namespace agrbin

#endif  // IMPL_AGRBIN_SEARCH_LINEAR_DISCRETE_FIRST_VALID_SEARCH_H_
