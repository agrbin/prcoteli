#ifndef __IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_HPP__
#define __IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_HPP__

// Recommended implementation (typically the best one on the benchmark):
#include "impl/dummy/array/keyed_dynamic_array.hpp"
template <class T>
class KeyedDynamicArray : public dummy::KeyedDynamicArray<T> {};

#endif  // __IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_HPP__
