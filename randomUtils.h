#ifndef __RANDOMUTILS_H_INCLUDED__
#define __RANDOMUTILS_H_INCLUDED__

// If using more complex RNG, uncomment
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <map>
//#include <cmath>

#include <random>


#include "pcg_random.hpp"

int runRNG(int lower, int upper){
    
    // Seed with a real random value, if available
    pcg_extras::seed_seq_from<std::random_device> seed_source;

    // Make a random number engine
    pcg32 rng(seed_source);

    // Choose a random mean between lower and upper
    std::uniform_int_distribution<int> uniform_dist(lower, upper);
    int number = uniform_dist(rng);
    std::cout << "[DEBUG] Generated number : " << number << std::endl;
    
    return number;
}
#endif // __RANDOMUTILS_H_INCLUDED__ 
