#include "impl/concrete/search/discrete_first_valid_search_test.h"
#include "testing/tester.h"

// A list of DiscreteFirstValidSearch implementations:
#include "impl/agrbin/search/linear_discrete_first_valid_search.h"

namespace testing {

#define TESTER_ADD_IMPLEMENTATION(ClassName) \
  TESTER_ADD(#ClassName, new DiscreteFirstValidSearchTests<ClassName>())

TESTER_BEGIN(DiscreteFirstValidSearch)
TESTER_ADD_IMPLEMENTATION(agrbin::LinearDiscreteFirstValidSearch);
TESTER_END()

}  // testing

TESTER_MAIN()
