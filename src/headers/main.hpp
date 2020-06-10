#ifndef __MAIN_H_INCLUDED__
#define __MAIN_H_INCLUDED__

namespace constants
{

constexpr unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and less for prod.
constexpr unsigned int MAXDAILYRUN = 1; // Number of run in a day
constexpr unsigned int MAXDAYMONTH = 4; // Number of day in a month
constexpr unsigned int MAXTIME = 2; // Number of month in the sim
constexpr unsigned int ADDDAYTIME = 24 / MAXDAILYRUN;
constexpr uint16_t MAXNUMBERAGENT = 10;
constexpr uint16_t PLANTDENSITY = 1;

}

#endif // __MAIN_H_INCLUDED__
