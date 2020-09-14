/* 
 * Copyright 2020 Axel Polin, univ_apolin@protonmail.com
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
*/
#ifndef __RANDOMUTILS_H_INCLUDED__
#define __RANDOMUTILS_H_INCLUDED__

// If using more complex RNG, uncomment
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <map>
#include <cmath>
#include <ctime>
#include <cstdlib>

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

    srand (static_cast <unsigned> (time(0)));
    
    for ( int i = 0; i < 3; ++i )
        vector.push_back ( lower + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX/(upper-lower))) );

    return vector ;
}

#endif // __RANDOMUTILS_H_INCLUDED__ 
