#ifndef IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_H_
#define IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_H_

// Recommended implementation (typically the best one on the benchmark):
#include "impl/agrbin/search/linear_discrete_first_valid_search.h"

template <class T>
class DiscreteFirstValidSearch
    : public agrbin::LinearDiscreteFirstValidSearch<T> {};

#endif  // IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_H_
