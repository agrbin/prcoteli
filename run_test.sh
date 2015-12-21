g++ impl/concrete/$1_test.cc -I. -o test -O2 -std=c++11 -lm && ./test --test_only "${@:2}" && rm test
