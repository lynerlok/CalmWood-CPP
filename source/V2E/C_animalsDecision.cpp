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

int Leucorrhinia::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
        int month = environment->getMonth();

        int X = 0;
        int Y = 0;
        int randomTry = 0;

        float temperature = environment->getEnvironmentParameters() [0];
        float hygrometry = environment->getEnvironmentParameters() [1];
        float antropizationRate = environment->getEnvironmentParameters() [2];

        int actionProbability = runRNG ( 0, 100 );
        int choiceProbability = 0;

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

        if ( actionProbability < deadProbability ) {
                dead ( environment );
                return 0;
        }

        if ( month < 5 && month >= 9 && sex == 1 ) {
                hidden = true;
                deadProbability = deadProbability - 30 < 0 ? 0 : deadProbability - 30;
        }

        if ( actionProbability < growthProbability )
                growth ( environment );

        if ( actionProbability < eatProbability )
                eat();

        if ( growthState == 1 ) {

                if ( actionProbability < moveProbability ) {

                        choiceProbability = runRNG ( 0, CellSpecs->size()-1 );

                        while ( ( CellSpecs->at ( choiceProbability ) [3] == 0 || CellSpecs->at ( choiceProbability ) [0] == 0 ) && randomTry < 10 ) {
                                choiceProbability = runRNG ( 0, CellSpecs->size()-1 );
                                ++randomTry;
                        }

                        if ( randomTry == 4 ) {
                                dead ( environment );
                                return 0;
                        }

                        X, Y = CellSpecs->at ( choiceProbability ) [5], CellSpecs->at ( choiceProbability ) [6];

                        moveTowards ( environment, X, Y );

                }
        }

        if ( growthState == 2 ) {

                if ( sex == 0 ) {

                        if ( actionProbability < protectionProbability && month >= 4 && month < 7 && ! protectTerritory ) {

                                choiceProbability = runRNG ( 0, CellSpecs->size()-1 );

                                while ( CellSpecs->at ( choiceProbability ) [0] == 0 && randomTry < 4 ) {
                                        choiceProbability = runRNG ( 0, CellSpecs->size()-1 );
                                        ++randomTry;
                                }

                                if ( randomTry == 4 ) {
                                        dead ( environment );
                                        return 0;
                                }

                                X, Y = CellSpecs->at ( choiceProbability ) [5], CellSpecs->at ( choiceProbability ) [6];

                                moveTowards ( environment,X,Y );
                                protectTerritory = true;
                                territoryCoordinates = {X,Y};
                                oldDetectionRadius = detectionRadius[2];
                                detectionRadius[2] = 1;

                        }

                        if ( actionProbability < reproductionProbability && protectTerritory ) {

                                choiceProbability = runRNG ( 0, VisibleAnimals->size()-1 );

                                reproduction ( &VisibleAnimals->at ( choiceProbability ), 0 );
                        }

                        if ( actionProbability < attackProbability && protectTerritory ) {

                                choiceProbability = runRNG ( 0, VisibleAnimals->size()-1 );

                                attack ( environment, &VisibleAnimals->at ( choiceProbability ), X, Y, 0 );
                        }

                        if ( month < 4 && month >= 7 )
                                protectTerritory = false;
                }

                if ( sex == 1 ) {

                        if ( spawnAbility ) {

                                choiceProbability = runRNG ( 0, CellSpecs->size()-1 );

                                while ( ( CellSpecs->at ( choiceProbability ) [3] == 0 || CellSpecs->at ( choiceProbability ) [0] == 0 ) && randomTry < 10 ) {
                                        choiceProbability = runRNG ( 0, CellSpecs->size()-1 );
                                        ++randomTry;
                                }

                                if ( randomTry == 4 ) {
                                        dead ( environment );
                                        return 0;
                                }
                                
                                X, Y = CellSpecs->at ( choiceProbability ) [5], CellSpecs->at ( choiceProbability ) [6];
                                moveTowards ( environment, X, Y );
                        }
                }

                if ( ( actionProbability < moveProbability && month >= 5 && month < 9 && growthState > 0 && ! protectTerritory && ! spawnAbility ) )
                        move ( environment );
        }

        return 0;
}

int Hyla::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
        return 0;
}


int Phengaris::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
        return 0;
}

int Zootoca::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
        return 0;
}

int Vipera::decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs )
{
        return 0;
}

