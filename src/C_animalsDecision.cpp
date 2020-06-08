#include "headers/C_animals.hpp"


int Leucorrhinia::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();
    int viability = CellSpecs->at ( 0 );
    
    // {viability,containTrees,containAnthropization,containWetland};
    
    switch(growthState) {
        case 0 :
            break;
        case 1 : 
            break;
        case 2 :
            break;
    }
    
    if ( CellSpecs->at ( 0 ) == 0 )
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
