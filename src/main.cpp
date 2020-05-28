#include <iostream>

#include "headers/U_randomGenerator.hpp"
#include "headers/U_loadLevel.hpp"
#include "headers/C_animals.hpp"
#include "headers/C_plants.hpp"
#include "headers/C_environment.hpp"
#include "headers/C_plants.hpp"
#include <unistd.h>

using namespace std;

int addNewAgent ( Animals animal );

int MASrun ( Environment * environment, vector<Animals*> * animals )
{

    const unsigned int SLEEPTIME = 0.5 * 1000000; // µsecs ! Use 1 multiplicator for test and minus for prod.
    const unsigned int MAXRUN = 10;

    bool runError = false;
    int agent = 0;
    vector<int> probabilities;

    int agentNumber = ( *animals ).size();

    /* DEV PART */
    for ( int run=1; run != ( MAXRUN + 1 ); ++run )
    {
        // agent = runRNG(0,agentNumber);
        for ( int agent = 0; agent < agentNumber; ++agent )
        {
            ( * ( *animals ) [agent] ).run ( environment );
        }
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

    std::vector<float> location = {0,0,0};

    const unsigned int mapLength = environment.getMapLength();

    uint16_t MaxNumberAgent = 10;
    uint8_t NumberSpecies = 5;

    uint16_t PlantDensity = 1;

    auto initAnimals = [&] ( Environment * environment, vector<Animals*> * animals, Animals * animal )
    {
        for ( int i = 0; i < 3; ++i )
        {
            location[i] = runRNG ( 0,mapLength-1 );
        }
   
        ( *animal ).setLocation ( location );
        (*environment).getCell(location[0],location[1])->addAnimal((*animal).getID(), animal);

        ( *animals ).push_back ( animal );

    };

    for ( int agent=0; agent < MaxNumberAgent*NumberSpecies; agent+=NumberSpecies ) // ***May be optimized !***
    {

        initAnimals ( &environment,&animals, new Leucorrhinia() );
        initAnimals ( &environment,&animals,new Hyla() );
        initAnimals ( &environment,&animals,new Phengaris() );
        initAnimals ( &environment,&animals,new Zootoca() );
    }

    for ( int agent=0; agent < PlantDensity; agent+=1 )
    {
        plants.push_back ( new Gentiania() );
    }

    environment.setEnvironmentParameters ( 25,0.5,0.7 );

    int LevelNumber = 1;

    MASrun ( &environment,&animals );

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

