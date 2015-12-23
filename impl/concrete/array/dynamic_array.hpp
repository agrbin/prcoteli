#ifndef __IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP__
#define __IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP__

// Recommended implementation (typically the best one on the benchmark):
#include "impl/dummy/array/dynamic_array.hpp"
template <class T>
class DynamicArray : public dummy::DynamicArray<T> {};

#endif  // __IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP__
