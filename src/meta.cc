// file:   meta.cc
// author: cpjenkins
// date:   27 Sep 2020
// 
// that's so meta...

#include <cstdio>
#include <cstdlib>
#include <type_traits>

template <bool B, class T=void>
struct enable_if { };

// if B is true, evaluates to a struct w/ typedef 'type'
// therefore if B is false, the compiler must choose the empty
// struct - causing the desired substitution failure
template <class T>
struct enable_if<true, T> { typedef T type; };

template <bool B, class T=void>
using enable_if_t = typename enable_if<B, T>::type;

// example
template <typename T, 
          typename = enable_if_t<std::is_arithmetic<T>::value>>
T sum(T a, T b) { return a + b; }

// check if power of 2
template <class T=void>
using enable_if_integral = enable_if<std::is_integral<T>::value, int>;

template <class T=void>
using enable_if_integral_t = enable_if_t<std::is_integral<T>::value, int>;


template <typename T, enable_if_integral_t<T> = 0>
static constexpr bool is_power_of_2(T n) {
    return n && !(n & (n-1));
}

int main() {
    fprintf(stderr, "easy as 1, 2, %d\n", sum(1, 2));
    fprintf(
        stderr, "the number 0 %s a power of 2\n", 
        is_power_of_2(0) ? "is" : "is NOT"
    );
    fprintf(
        stderr, "the number 1 %s a power of 2\n", 
        is_power_of_2(1) ? "is" : "is NOT"
    );
    fprintf(
        stderr, "the number 3 %s a power of 2\n", 
        is_power_of_2(3) ? "is" : "is NOT"
    );
    fprintf(
        stderr, "the number 8 %s a power of 2\n", 
        is_power_of_2(8) ? "is" : "is NOT"
    );
    fprintf(
        stderr, "the number 9 %s a power of 2\n", 
        is_power_of_2(9) ? "is" : "is NOT"
    );
    fprintf(
        stderr, "the number -32 %s a power of 2\n", 
        is_power_of_2(-64L) ? "is" : "is NOT"
    );
    return 0;
}

