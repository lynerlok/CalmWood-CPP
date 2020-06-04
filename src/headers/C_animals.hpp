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
    Animals ( int newId = 0 )
    {
        id = newId;
    };
    ~Animals ( void ) {};

    int run ( Environment * environment );

    int getID();

    int setName ( std::string newName );
    std::string getName();

    int setParameters ( int newLength,
                        int newActionRadius,
                        int newDetectionRadius,
                        int newGrowthState,
                        int sex );

    int setProbabilities ( int newMoveProbability,
                           int newEatProbability,
                           int newGrowthProbability,
                           int newDeadProbability );

    std::vector<int> getProbabilities();

    int setLocation ( std::vector<float> newLocation );
    std::vector <float> getLocation();

    int triggerAgent ( Environment * environment, int alterationType, int associatedProbability );

    bool isDead();

protected :

    int id = 0;

    std::vector <float> location{0,0,0};

    std::string name;
    std::string form;

    int sex = 0; // 0 = male 1 = female

    int length = 1;
    int actionRadius = 1;
    int detectionRadius = 2;
    int growthState = 0;

    int satietyIndex = 100; // MAX 100 MIN 0

    int moveProbability = 60;
    int eatProbability = 0; // 70;
    int growthProbability = 0; // 30;
    int deadProbability = 0;

    bool hidden = false;
    bool death = false;

    // Detection step
    int detection ( Environment * environment );

    // Action step
    virtual int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs ) = 0;
//     virtual int reproduction ( Environment * environment ) = 0;
//     virtual int attack ( Environment * environment ) = 0;

    int move ( Environment * environment );
    int moveTowards ( Environment * environment, int X, int Y );
    int eat ( Environment * environment );
    int setHiddenState ( bool state );
    int spawn ( Environment * environment );

    int growth();
    int dead();

};

class Leucorrhinia: public Animals
{
public :
    Leucorrhinia ( int id = 0 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Hyla: public Animals
{
public :
    Hyla ( int id = 1 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Phengaris: public Animals
{
public :
    Phengaris ( int id = 2 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Zootoca: public Animals
{
public :
    Zootoca ( int id = 3 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

class Vipera: public Animals
{
public :
    Vipera ( int id = 4 ) :Animals ( id ) {}
protected :
    int decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs );
//     int reproduction ( Environment * environment );
//     int attack ( Environment * environment );
};

#endif // __C_ANIMALS_H_INCLUDED__




