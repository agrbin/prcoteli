#ifndef IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_
#define IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_

// Recommended implementation (typically the best one on the benchmark):
#include "impl/kalinov/array/block_based_keyed_dynamic_array.hpp"
template <class T>
class DynamicArray : public kalinov::BlockBasedKeyedDynamicArray<T> {};

#endif  // IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_
