#ifndef __C_ANIMALS_H_INCLUDED__
#define __C_ANIMALS_H_INCLUDED__

#include "U_randomGenerator.hpp"
#include "C_environment.hpp"

#include <string>
#include <vector>
#include <iostream>

class Environment;

class Animals
{
public :
    Animals ( int newId = 99,
              std::vector<unsigned int> newlifeCycle = {1,1,1},
              std::vector<int> newprobabilities = {0,0,0,0,0,0},
              std::vector<int> newDetectionRadius = {2,2,2},
              std::vector<int> newActionRadius = {1,1,1}
            )
    {
        id = newId;
        lifeCycle = newlifeCycle;
        moveProbability = newprobabilities[0];
        eatProbability = newprobabilities[1];
        growthProbability = newprobabilities[2];
        spawnProbability = newprobabilities[3];
        deadProbability = newprobabilities[4];
        reproductionProbability = newprobabilities[5];

        actionRadius = newActionRadius;
        detectionRadius = newDetectionRadius;

        length = runRNG ( 0,10 );
        sex = runRNG ( 0,1 );
        growthState = runRNG ( 0,2 );

    };
    ~Animals ( void ) {};

    int run ( Environment * environment );

    int getID();

    int setLocation ( std::vector<int> newLocation );
    std::vector <int> getLocation();

    bool isDead();

    int getSex();

    int setSpawnAbility ( bool newSpawnAbility );
    
    int spawn();

protected :

    int id = 0;

    std::vector <int> location{0,0,0};
    std::vector<int> actionRadius{0,0,0};
    std::vector<int>  detectionRadius{0,0,0};
    
    int sex = 0; // 0 = male 1 = female

    int length = 0;
    int growthState = 0;

    int satietyIndex = 100; // MAX 100 MIN 0

    int moveProbability = 0;
    int eatProbability = 0;
    int growthProbability = 0;
    int spawnProbability = 0;
    int deadProbability = 0 ;
    int reproductionProbability = 0;

    unsigned int timeLifeCycle = 0;
    std::vector<unsigned int> lifeCycle{0,0,0};

    bool hidden = false;
    bool death = false;
    bool spawnAbility = false;

    // Detection step
    int detection ( Environment * environment );

    // Action step
    virtual int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs ) = 0;

    int move ( Environment * environment );
    int moveTowards ( Environment * environment, int X, int Y );
    int eat ();
    int setHiddenState ( bool state );
    int reproduction ( std::unordered_multimap<int, Animals *> * VisibleAnimals );
    int attack ( Environment * environment );
    int spawn ( Environment * environment );

    int growth ( Environment * environment );
    int dead();

};

class Leucorrhinia: public Animals
{
public :
    Leucorrhinia ( int id = 0,
                   std::vector<unsigned int> lifeCycle = {1,24,1},
                   std::vector<int> probabilities = {100,0,100,100,0,100},
                   std::vector<int> detectionRadius = {1,1,2},
                   std::vector<int> actionRadius = {1,1,1} ) :Animals ( id, lifeCycle, probabilities, detectionRadius, actionRadius ) {}
protected :
    int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Hyla: public Animals
{
public :
    Hyla ( int id = 1 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Phengaris: public Animals
{
public :
    Phengaris ( int id = 2 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Zootoca: public Animals
{
public :
    Zootoca ( int id = 3 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Vipera: public Animals
{
public :
    Vipera ( int id = 4 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

#endif // __C_ANIMALS_H_INCLUDED__




