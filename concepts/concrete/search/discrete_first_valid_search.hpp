// DiscreteFirstValidSearch is a concept with these properties:
// * The class defines the "value_type" which refers to a type of the searched
// element. This type must be integral.
// * A constructor with the std::function predicate that receives "value_type"
// and returns bool.
//
// * A const method bool FindFirstValid(value_type lo, value_type hi,
// value_type *result) is defined that performs the search. The main goal of
// this method is to find an element in range [lo, hi) that satisfies the
// predicate given in the constructor.
// The method assumes that if predicate(x) is true, then predicate(y) is also
// true for all y > x.
// If method returns true then
// - Result is a valid element: predicate(*result) == true,
// - Result is the first valid element: predicate(y) == false for y < *result.
//
// If method returns false then
// - All elements are invalid: predicate(y) == false, for y >= lo && y < hi.

#ifndef __CONCEPTS_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__
#define __CONCEPTS_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__

#include "boost/concept_check.hpp"

namespace concepts {

template <class T>
struct IsDiscreteFirstValidSearch {
  typedef typename T::value_type value_type;

  BOOST_CONCEPT_USAGE(IsDiscreteFirstValidSearch) {
    auto predicate = [](value_type x) { return x < 5; };
    T searcher(predicate);
    value_type lo;
    value_type hi;
    value_type result;
    bool success = searcher.FindFirstValid(lo, hi, &result);
  }
};

}  // namespace concepts

#endif  // __CONCEPTS_CONCRETE_SEARCH_DISCRETE_FIRST_VALID_SEARCH_HPP__
