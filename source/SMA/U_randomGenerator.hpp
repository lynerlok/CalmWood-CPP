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

inline int runRNG ( int lower, int upper )
{

        // Seed with a real random value, if available
        pcg_extras::seed_seq_from<std::random_device> seed_source;

        // Make a random number engine
        pcg32 rng ( seed_source );

        // Choose a random mean between lower and upper
        std::uniform_int_distribution<int> uniform_dist ( lower, upper );
        int number = uniform_dist ( rng );

        return number;
}

template<typename T>

inline int runShuffle ( std::vector<T> * vectorToSfuffle )
{
        // Seed with a real random value, if available
        pcg_extras::seed_seq_from<std::random_device> seed_source;

        // Make a random number engine
        pcg32 rng ( seed_source );

        pcg_extras::shuffle ( begin ( ( *vectorToSfuffle ) ), end ( ( *vectorToSfuffle ) ), rng );

        return 0;
}

inline std::vector<float> getDirection ( int lower, int upper )
{

        std::vector<float> vector;

        for ( int i = 0; i < 3; ++i )
                vector.push_back ( ldexp ( runRNG ( lower,upper ), -32 ) );

        return vector ;
}

#endif // __RANDOMUTILS_H_INCLUDED__ 
