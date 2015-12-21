#ifndef IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_H_
#define IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_H_

// Recommended implementation (typically the best one on the benchmark):
#include "impl/kalinov/array/vector_backed_dynamic_array.h"
template <class T>
class DynamicArray : public kalinov::VectorBackedDynamicArray<T> {};

#endif  // IMPL_CONCRETE_ARRAY_DYNAMIC_ARRAY_H_
