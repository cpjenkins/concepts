// file:   benchmark.h
// author: cpjenkins
// date:   26 Sep 2020
// 
// benchmarking faculties
#pragma once

#include <ctime>

namespace concepts {

// return current wall clock time [seconds]
static inline double tick() {
    struct timespec tv;
    clock_gettime(CLOCK_MONOTONIC, &tv);
    return tv.tv_sec + (double) tv.tv_nsec / 1e9;
}

// return elapsed wallclock time [seconds]
static inline double tock(double start) {
    return tick() - start;
}

}


