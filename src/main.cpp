#include <iostream>

#include "headers/U_randomGenerator.hpp"
#include "headers/U_loadLevel.hpp"
#include "headers/C_animals.hpp"
#include "headers/C_plants.hpp"
#include "headers/C_environment.hpp"
#include "headers/C_plants.hpp"
#include <unistd.h>

using namespace std;

int MASrun ( Environment * environment, vector<Animals*> * animals, vector<Plants*> * plants )
{

    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and less for prod.
    const unsigned int MAXDAILYRUN = 1; // Number of run in a day
    const unsigned int MAXDAYMONTH = environment->DAYSMONTH; // Number of day in a month
    const unsigned int MAXTIME = 2; // Number of month in the sim

    int addDayTime = 24 / MAXDAILYRUN;

    bool runError = false;
    int agent = 0;

    unsigned int timeOfDay = ( * environment ).getTimeOfDay();
    unsigned int monthOfYear = ( * environment ).getMonth();

    int agentNumber = ( *animals ).size();

    /* DEV PART */

    for ( int simulationTime=0; simulationTime < MAXTIME; ++simulationTime )
    {

        for ( int MonthlyRun=0; MonthlyRun < MAXDAYMONTH; ++MonthlyRun )
        {

            for ( int DailyRun=0; DailyRun < MAXDAILYRUN; ++DailyRun )
            {
                for ( int agent = 0; agent < agentNumber; ++agent )
                {
                    ( * ( *animals ) [agent] ).run ( environment );

                }

                timeOfDay = ( timeOfDay + addDayTime ) % 24;
                ( * environment ).setTimeOfDay ( timeOfDay );

            }
        }

        monthOfYear = ( monthOfYear + 1 ) % 12;
        ( * environment ).setMonth ( monthOfYear );

    }

    /* PROD PART */

//     while (runError == false){
//         usleep(SLEEPTIME);
//     }

    /* END PROD PART */

    return 0;
}

int MASinitialize()
{

    Environment environment;
    vector<Animals*> animals;
    vector<Plants*> plants;

    std::vector<int> location = {0,0,0};

    const unsigned int mapLength = environment.getMapLength();

    uint16_t MaxNumberAgent = 10;
    uint8_t NumberSpecies = 5;

    uint16_t PlantDensity = 1;

    auto initAnimals = [&] ( Environment * environment, vector<Animals*> * animals )
    {
        vector<Animals *> newAnimals = { new Leucorrhinia(), new Hyla(), new Phengaris(), new Zootoca(), new Vipera() };

        for ( int animal = 0; animal < newAnimals.size(); ++animal )
        {

            for ( int i = 0; i < 3; ++i )
            {
                location[i] = runRNG ( 0,mapLength-1 );
            }

            ( *newAnimals[animal] ).setLocation ( location );
            ( *environment ).getCell ( location[0],location[1] )->addAnimal ( ( *newAnimals[animal] ).getID(), newAnimals[animal] );

            ( *animals ).push_back ( newAnimals[animal] );

        }

    };

    auto initPlants = [&] ( Environment * environment, vector<Plants*> * plants )
    {
        vector<Plants *> newPlants = { new Gentiania(), new Juncus(), new Glyceria(), new Carex(), new Iris() };

        for ( int plant = 0; plant < newPlants.size(); ++plant )
        {

            for ( int i = 0; i < 3; ++i )
            {
                location[i] = runRNG ( 0,mapLength-1 );
            }

            ( *newPlants[plant] ).setLocation ( location );
            ( *environment ).getCell ( location[0],location[1] )->addPlant ( ( *newPlants[plant] ).getID(), newPlants[plant] );

            ( *plants ).push_back ( newPlants[plant] );
        }

    };

    for ( int agent=0; agent < MaxNumberAgent; ++agent )
    {
        initAnimals ( &environment, &animals );
    }

    for ( int agent=0; agent < PlantDensity; ++agent )
    {
        initPlants ( &environment, &plants );
    }

    runShuffle ( &animals );
    runShuffle ( &plants );

    environment.setEnvironmentParameters ( 25,0.5,0.7 );

    MASrun ( &environment, &animals, &plants );

    for ( int i=0; i<animals.size(); ++i )
    {
        delete ( animals[i] );
    }

    animals.clear();

    for ( int i=0; i<plants.size(); ++i )
    {
        delete ( plants[i] );
    }

    plants.clear();


    return 0;
}

int MAScollector()
{

    return 0;
}

int main ( int argc, char **argv )
{

    cout << MASinitialize() << endl;

    return 0;
}

/* END DEV PART */

//MASrun();

// MAScollector();

