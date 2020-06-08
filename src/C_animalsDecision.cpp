#include "headers/C_animals.hpp"


int Leucorrhinia::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();
    int viability = CellSpecs->at ( 0 );
    
    // {viability,containTrees,containAnthropization,containWetland};
    
    int actionProbability = runRNG(0,100);
    
    if ( moveProbability <= actionProbability )
        move(environment);
    
    switch(growthState) {
        case 0 : // Egg
//             eat(environment);
//             growth(environment);
            break;
        case 1 : // Larvae
//             detectionRadius = 1;
//             actionRadius = 1;
//             move(environment);
//             eat(environment);
//             growth(environment);
            break;
        case 2 : // Adult
//             detectionRadius = 3;
//             actionRadius = 2;
//             move(environment);
//             eat(environment);
//             growth(environment);
//             reproduction();
//             attack();
//             if ( sex = 1 && reproduction )
//                 spawn;
            break;
    }
    
    if ( viability == 0 )
        move ( environment );

    if ( month < 5 && month >= 9 )
    {
        setHiddenState ( true );
        deadProbability = 0.2;
    }



    return 0;
}

int Hyla::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}


int Phengaris::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}

int Zootoca::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}

int Vipera::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{
    return 0;
}
