#ifndef IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_H_
#define IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_H_

// Recommended implementation (typically the best one on the benchmark):
#include "impl/kalinov/array/list_backed_keyed_dynamic_array.h"
template <class T>
class KeyedDynamicArray : public kalinov::ListBackedKeyedDynamicArray<T> {};

#endif  // IMPL_CONCRETE_ARRAY_KEYED_DYNAMIC_ARRAY_H_
