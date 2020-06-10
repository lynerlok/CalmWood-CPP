#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "headers/U_randomGenerator.hpp"
#include "headers/U_loadLevel.hpp"
#include "headers/C_animal.hpp"
#include "headers/C_plant.hpp"
#include "headers/C_environment.hpp"
#include "headers/main.hpp"

using namespace std;
using namespace constants;

int MASinitialize ( Environment * environment,
                    vector<Animal*> * animals,
                    vector<Plant*> * plants )
{

    std::vector<int> location = {0,0,0};

    const unsigned int mapLength = environment->getMapLength();

    auto initAnimals = [&] ( Environment * environment, vector<Animal*> * animals )
    {
        vector<Animal *> newAnimals = { new Leucorrhinia(), new Hyla(), new Phengaris(), new Zootoca(), new Vipera() };

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

    auto initPlants = [&] ( Environment * environment, vector<Plant*> * plants )
    {
        vector<Plant *> newPlants = { new Gentiania(), new Juncus(), new Glyceria(), new Carex(), new Iris() };

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

    for ( int agent=0; agent < MAXNUMBERAGENT; ++agent )
    {
        initAnimals ( environment, animals );
    }

    for ( int agent=0; agent < PLANTDENSITY; ++agent )
    {
        initPlants ( environment, plants );
    }

    runShuffle ( animals );
    runShuffle ( plants );

    environment->setEnvironmentParameters ( 25,0.5,0.7 );

    return 0;
}

int MASrun ( Environment * environment, vector<Animal*> * animals, vector<Plant*> * plants, int * deadCount, int * spawnCount )
{

    vector<Animal*>::iterator agent;

    unsigned int timeOfDay = ( * environment ).getTimeOfDay();
    unsigned int monthOfYear = ( * environment ).getMonth();

    Animal * newAnimal;
    vector<int> spawnLocation{0,0,0};

    auto spawn = [&] ( Animal * animal )
    {
        spawnLocation = animal->getLocation();

        switch ( animal->getID() )
        {
        case 0 :
            newAnimal = new Leucorrhinia ( 0, {1,24,1}, {0,0,0,100,1,20}, {1,1,2}, {1,1,1}, true );
            break;
        case 1 :
            newAnimal = new Hyla();
            break;
        case 2 :
            newAnimal = new Phengaris();
            break;
        case 3 :
            newAnimal = new Zootoca();
            break;
        case 4 :
            newAnimal = new Vipera();
            break;
        }

        newAnimal->setLocation ( spawnLocation );
        ( *environment ).getCell ( spawnLocation[0],spawnLocation[1] )->addAnimal ( newAnimal->getID(), newAnimal );

        ( *animals ).push_back ( newAnimal );

        animal->setSpawnAbility ( false );

        runShuffle ( animals );
    };

    /* DEV PART */


    for ( int simulationTime=0; simulationTime < MAXTIME; ++simulationTime )
    {

        for ( int MonthlyRun=0; MonthlyRun < MAXDAYMONTH; ++MonthlyRun )
        {

            for ( int DailyRun=0; DailyRun < MAXDAILYRUN; ++DailyRun )
            {
                for ( agent = ( *animals ).begin() ; agent != ( *animals ).end(); ++agent )
                {
                    ( *agent )->run ( environment );

                    if ( ( *agent )->isDead() )
                    {
                        *deadCount += 1;
                        delete ( *agent );
                        agent = ( *animals ).erase ( agent );
                        --agent;

                    }
                    else if ( ( *agent )->isSpawn() && runRNG ( 0,100 ) < ( *agent )->getSpawnProbability() )
                    {
                        *spawnCount += 1;
                        spawn ( ( *agent ) );
                    }

                }

                timeOfDay = ( timeOfDay + ADDDAYTIME ) % 24;
                ( * environment ).setTimeOfDay ( timeOfDay );

            }
        }

        monthOfYear = ( monthOfYear + 1 ) % 12;
        ( * environment ).setMonth ( monthOfYear );

    }

    /* END DEV PART */

    /* PROD PART */

//     while (runError == false){
//         usleep(SLEEPTIME);
//     }

    /* END PROD PART */

    return 0;
}

int MAScollector ( Environment * environment,
                   vector<Animal*> * animals,
                   vector<Plant*> * plants,
                   int * deadCount,
                   int * spawnCout )
{

    cout << "Some statistics on the simulation" << endl;

    cout << "Number of death ( animals ) : " << *deadCount << endl;
    cout << "Number of birth ( animals ) : " << *spawnCout << endl;
    
    cout << "Number of Leucorrhinia at simulation start : " << MAXNUMBERAGENT << endl;
    
    int LeucorrhiniaCount = 0;
    
    for ( int animal = 0; animal < animals->size(); ++animal )
        if ( (*animals)[animal]->getID() == 0 )
            LeucorrhiniaCount++;
        
    cout << "Number of Leucorrhinia at the end : " << LeucorrhiniaCount << endl;
    
    cout << "Temperature at the end of the simulation : " << environment->getEnvironmentParameters()[0] << endl;
    
    cout << "Hygrometry at the end of the simulation : " << environment->getEnvironmentParameters()[1] << endl;
    
    cout << "Antrhopization at the end of the simulation : " << environment->getEnvironmentParameters()[2] << endl;
    
    return 0;
}

int main ( int argc, char **argv )
{

    Environment environment;
    vector<Animal*> animals;
    vector<Plant*> plants;

    int deadCount = 0;
    int spawnCount = 0;

    MASinitialize ( &environment, &animals, &plants );

    MASrun ( &environment, &animals, &plants, &deadCount, &spawnCount );

    MAScollector ( &environment, &animals, &plants, &deadCount, &spawnCount );

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
