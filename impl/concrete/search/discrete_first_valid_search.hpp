#ifndef __IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__
#define __IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__

// Recommended implementation (typically the best one on the benchmark):
#include "impl/agrbin/search/linear_discrete_first_valid_search.hpp"

template <class T>
class DiscreteFirstValidSearch : public
                                 agrbin::LinearDiscreteFirstValidSearch<T> {};

#endif  // __IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__
