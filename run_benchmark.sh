g++ impl/concrete/$1_test.cc -I. -o test -O2 -std=c++11 -lm && ./test --benchmark_only "${@:2}" && rm test
