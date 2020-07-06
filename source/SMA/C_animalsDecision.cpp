#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "U_randomGenerator.hpp"
#include "C_animal.hpp"
#include "C_plant.hpp"
#include "C_animal.hpp"
#include "C_environment.hpp"

int Leucorrhinia::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimal, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();

    std::vector<std::vector<int>>::iterator cell = CellSpecs->begin();

    int viability = 0;// CellSpecs->at ( 0 );
    int wetLand = 0; //CellSpecs->at ( 3 );
    int X = 0; //CellSpecs->at ( 4 );
    int Y = 0; //CellSpecs->at ( 5 );

    float temperature = environment->getEnvironmentParameters() [0];
    float hygrometry = environment->getEnvironmentParameters() [1];
    float antropizationRate = environment->getEnvironmentParameters() [2];

    int actionProbability = runRNG ( 0, 100 );
    int chooseProbability = runRNG( 0, 100 ); // À voir 

    satietyIndex -= 10;

    if ( temperature < 15.0 || temperature > 30.0 ) {
        dead ( environment );
        return 0;
    }

    if ( antropizationRate > 0.8 ) {
        dead ( environment );
        return 0;
    }

    if ( hygrometry < 0.2 || hygrometry > 0.95 ) {
        dead ( environment );
        return 0;
    }

    if ( month < 5 && month >= 9 && sex == 1 ) {
        hidden = true;
        deadProbability = deadProbability - 30 < 0 ? 0 : deadProbability - 30;
    }

    if ( actionProbability < deadProbability ) {
        dead ( environment );
        return 0;
    }

    if ( actionProbability < growthProbability )
        growth ( environment );

    if ( actionProbability < eatProbability )
        eat();


    for( int cell = 0 ; cell < CellSpecs->size(); ++cell) {
        if( ( * CellSpecs )[cell][0] == 0) {
            VisibleAnimal->remove(cell);
            VisiblePlants->erase(cell);
            CellSpecs->erase(cell);
        }

    }

    if ( growthState == 1 ) {
        if ( actionProbability < moveProbability && wetLand == 1 ) {
            moveTowards ( environment, X, Y );
        }
    }

    if ( growthState == 2 ) {

        if ( sex == 0 ) {

            if ( actionProbability < protectionProbability && viability == 1 && month >= 4 && month < 7 && ! protectTerritory ) {
                moveTowards ( environment,X,Y );
                protectTerritory = true;
                territoryCoordinates = {X,Y};
                oldDetectionRadius = detectionRadius[2];
                detectionRadius[2] = 1;
            }

            if ( actionProbability < reproductionProbability && protectTerritory )
                reproduction ( VisibleAnimals,0 );

            if ( actionProbability < attackProbability && protectTerritory )
                attack ( environment, VisibleAnimals, X, Y, 0 );

            if ( month < 4 && month >= 7 )
                protectTerritory = false;
        }

        if ( sex == 1 ) {

            if ( spawnAbility && wetLand == 1 ) {
                moveTowards ( environment, X, Y );
            }
        }

        if ( ( actionProbability < moveProbability && month >= 5 && month < 9 && growthState > 0 && ! protectTerritory && ! spawnAbility ) )
            move ( environment );
    }

    return 0;
}

int Hyla::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimal, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
    return 0;
}


int Phengaris::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimal, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
    return 0;
}

int Zootoca::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimal, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
    return 0;
}

int Vipera::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimal, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
    return 0;
}
