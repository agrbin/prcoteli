// DynamicArray is an Array that is mutable, insertable and removable.

#ifndef CONCEPTS_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_
#define CONCEPTS_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_

#include "boost/concept_check.hpp"
#include "concepts/abstract/array/array.hpp"

namespace concepts {

template <class T>
struct IsDynamicArray : IsMutableArray<T>,
                        IsInsertableArray<T>,
                        IsRemovableArray<T> {};

}  // namespace concepts

#endif  // CONCEPTS_CONCRETE_ARRAY_DYNAMIC_ARRAY_HPP_
