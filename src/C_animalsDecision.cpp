#include "headers/C_animals.hpp"

int Leucorrhinia::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();
    int viability = CellSpecs->at ( 0 );
    int wetLand = CellSpecs->at ( 3 );
    int X = CellSpecs->at ( 4 );
    int Y = CellSpecs->at ( 5 );

    // {viability,containTrees,containAnthropization,containWetland,X,Y};

    int actionProbability = runRNG ( 0,100 );

    if ( ( actionProbability < moveProbability && ( month >= 5 && month < 9 && growthState > 0 ) ) || viability == 0 )
        move ( environment );

    if ( month < 5 && month >= 9 )
    {
        hidden = true;
        deadProbability = 0;
    }

    if ( actionProbability < deadProbability )
        dead ( environment );

    if ( actionProbability < growthProbability )
        growth ( environment );

    if ( actionProbability < eatProbability )
        eat();

    if ( growthState == 1 )
    {
        if ( actionProbability < moveProbability && wetLand == 1 )
        {
            moveTowards ( environment, X, Y );
        }
    }

    if ( growthState == 2 )
    {
        if ( sex == 0 )
        {
            if ( actionProbability < reproductionProbability )
                reproduction ( VisibleAnimals,0 );
            
            if ( actionProbability < attackProbability )
                attack(environment);
                
        }

    }


    // Adult
    // attack();

    return 0;
}

int Hyla::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}


int Phengaris::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}

int Zootoca::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}

int Vipera::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}
