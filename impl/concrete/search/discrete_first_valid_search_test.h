#ifndef IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_TEST_H_
#define IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_TEST_H_

#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "boost/concept_check.hpp"
#include "concepts/concrete/search/discrete_first_valid_search.h"
#include "testing/tests.h"

namespace testing {

using namespace std;

template <template <class> class DiscreteFirstValidSearchImpl>
class DiscreteFirstValidSearchTests : public Tests {
 public:
  typedef DiscreteFirstValidSearchImpl<long long> Impl;

  DiscreteFirstValidSearchTests() {
    BOOST_CONCEPT_ASSERT((concepts::IsDiscreteFirstValidSearch<Impl>));
    RegisterTests();
  }

 private:
  void RegisterTests() {
    this->AddTest("DiscreteFirstValidSearchTests::Simple",
                  std::bind(&DiscreteFirstValidSearchTests::TestSimple, this));

    this->AddBenchmark(
        "DiscreteFirstValidSearchTests::Simple",
        std::bind(&DiscreteFirstValidSearchTests::BenchmarkSimple, this,
                  placeholders::_1, placeholders::_2));
  }

  bool TestSimple() {
    auto predicate = [](long long x) { return x >= 5; };
    Impl searcher(predicate);
    {
      long long result;
      CHECK(!searcher.FindFirstValid(0, 0, &result));
      CHECK(!searcher.FindFirstValid(0, 4, &result));
    }
    {
      long long result;
      CHECK(searcher.FindFirstValid(0, 10, &result));
      CHECK(result == 5);
    }
    return true;
  }

  pair<bool, double> BenchmarkSimple(int level, string *message) {
    long long n = 1000000;
    for (int i = 0; i < level; ++i) n = n * 2;
    ostringstream oss;
    oss << "(n = " << n << ")";
    *message = oss.str();

    auto t1 = chrono::high_resolution_clock::now();

    {
      Impl searcher([n](long long x) { return x >= n - 1; });
      long long result;
      searcher.FindFirstValid(0, n, &result);
    }

    auto t2 = chrono::high_resolution_clock::now();
    auto runtime = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    return make_pair(runtime.count() < 1.0, runtime.count());
  }
};

}  // namespace testing

#endif  // IMPL_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_TEST_H_
