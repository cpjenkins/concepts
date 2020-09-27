// file:   branch_mod.cc
// author: cpjenkins
// date:   26 Sep 2020
// 
// compare methods for checking odd/even integers
#include "concepts/benchmark.h"
#include <cstdlib>
#include <random>

namespace cp = concepts;
int main(int argc, const char* argv[]) {
    const int64_t niter = argc > 1 ? std::atoi(argv[1]) : 1000;
    const int64_t seed  = argc > 2 ? std::atoi(argv[2]) : 12345;

    const int64_t N = 64*1024;
    int64_t nums[N];
    int64_t oddities[N];
    std::default_random_engine rng_dev(seed); 
    std::mt19937 mtwist(rng_dev()); 
    std::uniform_int_distribution<int> distro(0);
    for (int64_t nn = 0; nn < N; ++nn) { 
        nums[nn] = distro(mtwist);
    }
    
    fprintf(stderr, "niter: %ld, seed: %ld\n", niter, seed);


    // impl1
    double start_time = cp::tick();
    for (int64_t ii = 0; ii < niter; ++ii) {
        for (int64_t nn = 0; nn < N; ++nn) {
            oddities[nn] = nums[nn] % 2 ? nums[nn]+1 : nums[nn];        
        }
    }
    double ternary_time = cp::tock(start_time);

    int64_t nflip = 0;
    for (int64_t nn = 0; nn < N; ++nn) {
        if (oddities[nn] != nums[nn]) nflip++;
    }

    fprintf(stderr, "num flipped: %ld\n", nflip);

    // impl2
    start_time = cp::tick();
    for (int64_t ii = 0; ii < niter; ++ii) {
        for (int64_t nn = 0; nn < N; ++nn) {
            oddities[nn] = nums[nn] + nums[nn] % 2;       
        }
    }
    double modulo_time = cp::tock(start_time);

    nflip = 0;
    for (int64_t nn = 0; nn < N; ++nn) {
        if (oddities[nn] != nums[nn]) nflip++;
    }
    fprintf(stderr, "num flipped: %ld\n", nflip);
    

    (void) oddities;
    fprintf(stderr, "ternary: %.6f sec\n", ternary_time);
    fprintf(stderr, "modulo:  %.6f sec\n", modulo_time);

    return 0;
}


