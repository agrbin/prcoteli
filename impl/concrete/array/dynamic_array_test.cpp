#include "impl/concrete/array/dynamic_array_test.hpp"
#include "testing/tester.hpp"

// A list of DynamicArray implementations:
#include "impl/dummy/array/dynamic_array.hpp"
#include "impl/dummy/array/keyed_dynamic_array.hpp"
#include "impl/kalinov/array/block_based_keyed_dynamic_array.hpp"

namespace testing {

#define TESTER_ADD_IMPLEMENTATION(ClassName) \
  TESTER_ADD(#ClassName, new DynamicArrayTests<ClassName>())

TESTER_BEGIN(DynamicArray)
TESTER_ADD_IMPLEMENTATION(dummy::DynamicArray);
TESTER_ADD_IMPLEMENTATION(dummy::KeyedDynamicArray);
TESTER_ADD_IMPLEMENTATION(kalinov::BlockBasedKeyedDynamicArray);
TESTER_END()

}  // testing

TESTER_MAIN()
