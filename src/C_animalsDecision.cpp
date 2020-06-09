#include "headers/C_animals.hpp"

int Leucorrhinia::decision ( Environment * environment, std::unordered_multimap<int, Animals *> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();
    int viability = CellSpecs->at ( 0 );
    int wetLand = CellSpecs->at ( 3 );
    int X = CellSpecs->at ( 4 );
    int Y = CellSpecs->at ( 5 );

    int actionProbability = runRNG ( 0,100 );

    if ( month < 5 && month >= 9 && sex == 1 )
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

            if ( viability == 1 && month >= 4 && month < 7 )
            {
                protectTerritory = true;
                territoryCoordinates = {location[0],location[1]};
                detectionRadius[2] = 1;
            }

            if ( actionProbability < reproductionProbability && protectTerritory )
                reproduction ( VisibleAnimals,0 );

            if ( actionProbability < attackProbability && protectTerritory )
                attack ( environment, VisibleAnimals, X, Y, 0 );

            if ( month < 4 && month >= 7 )
                protectTerritory = false;
        }

        if ( ( actionProbability < moveProbability && month >= 5 && month < 9 && growthState > 0 && ! protectTerritory ) || viability == 0 )
            move ( environment );
    }

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
