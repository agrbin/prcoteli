#include "impl/concrete/array/keyed_dynamic_array_test.hpp"
#include "testing/tester.hpp"

// A list of KeyedDynamicArray implementations:
#include "impl/dummy/array/keyed_dynamic_array.hpp"
#include "impl/kalinov/array/block_based_keyed_dynamic_array.hpp"

namespace testing {

#define TESTER_ADD_IMPLEMENTATION(ClassName) \
  TESTER_ADD(#ClassName, new KeyedDynamicArrayTests<ClassName>())

TESTER_BEGIN(KeyedDynamicArray)
TESTER_ADD_IMPLEMENTATION(dummy::KeyedDynamicArray);
TESTER_ADD_IMPLEMENTATION(kalinov::BlockBasedKeyedDynamicArray);
TESTER_END()

}  // namespace testing

TESTER_MAIN()
