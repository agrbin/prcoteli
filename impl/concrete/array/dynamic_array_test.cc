#include "impl/concrete/array/dynamic_array_test.h"
#include "testing/tester.h"

// A list of DynamicArray implementations:
#include "impl/kalinov/array/vector_backed_dynamic_array.h"
#include "impl/kalinov/array/list_backed_keyed_dynamic_array.h"

namespace testing {

#define TESTER_ADD_IMPLEMENTATION(ClassName) \
  TESTER_ADD(#ClassName, new DynamicArrayTests<ClassName>())

TESTER_BEGIN(DynamicArray)
TESTER_ADD_IMPLEMENTATION(kalinov::VectorBackedDynamicArray);
TESTER_ADD_IMPLEMENTATION(kalinov::ListBackedKeyedDynamicArray);
TESTER_END()

}  // namespace testing

TESTER_MAIN()
