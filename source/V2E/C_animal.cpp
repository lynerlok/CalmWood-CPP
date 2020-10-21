/* 
 * Copyright 2020 Axel Polin, univ_apolin@protonmail.com
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
*/
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "U_randomGenerator.hpp"
#include "C_environment.hpp"
#include "C_plant.hpp"
#include "C_animal.hpp"

typedef std::unordered_multimap<int, Animal *>::iterator MMAnimalIterator;

Animal::Animal ( int newId,
                 std::string newName,
                 std::vector<unsigned int> newlifeCycle,
                 std::vector<int> newprobabilities,
                 std::vector<int> newDetectionRadius,
                 std::vector<int> newActionRadius,
                 bool isBorn,
                 int newSpawnNumber
               )
{

        id = newId;
        name = newName;
        lifeCycle = newlifeCycle;

        moveProbability = newprobabilities[0];
        eatProbability = newprobabilities[1];
        growthProbability = newprobabilities[2];
        spawnProbability = newprobabilities[3];
        deadProbability = newprobabilities[4];
        reproductionProbability = newprobabilities[5];
        attackProbability = newprobabilities[6];
        protectionProbability = newprobabilities[7];

        actionRadius = newActionRadius;
        detectionRadius = newDetectionRadius;

        length = runRNG ( 0,10 );
        sex = runRNG ( 0,1 );

        growthState = isBorn ? 0 : runRNG ( 0,2 );

        spawnNumber = newSpawnNumber;

}

Animal::~Animal() {}

int Animal::continueSimulation()
{
        simulationState = true;
        return 0;
}

int Animal::stopSimulation()
{
        simulationState = false;
        return 0;
}

int Animal::growthFinished()
{
        growing = false;
        return 0;
}

int Animal::getID()
{
        return id;
}

std::string Animal::getName()
{
        return name;
}

int Animal::getSex()
{
        return sex;
}

int Animal::run ( Environment * environment )
{
        if ( simulationState )
                detection ( environment );

        return 0;
}

int Animal::getGrowthState()
{
        return growthState;
}

int Animal::setLocation ( std::vector<int> newLocation )
{

        if ( newLocation.size() != 2 )
                return -1;

        location = newLocation;

        return 0;
}

int Animal::setOldLocation ( std::vector<int> newLocation )
{

        if ( newLocation.size() != 2 )
                return -1;

        oldLocation = newLocation;

        return 0;
}

std::vector <int> Animal::getLocation()
{
        return location;
}

std::vector<int> Animal::getOldLocation()
{
        return oldLocation;
}


bool Animal::isDead()
{
        return death;
}

bool Animal::isSpawn ()
{
        return spawnAbility;
}

bool Animal::getHiddenState()
{
        return hidden;
}

bool Animal::isGrowing()
{
        return growing;
}


int Animal::setSpawnAbility ( bool newSpawnAbility ) // RDI + offset
{
        if ( newSpawnAbility ) // Careful this is string in assembly !!! so test sil, sil
                deadProbability = deadProbability - 30 < 0 ? 0 : deadProbability - 30;
        if ( ! newSpawnAbility )
                deadProbability += 30;

        spawnAbility = newSpawnAbility;
        return 0;

}

int Animal::getSpawnProbability()
{
        return spawnProbability;
}

int Animal::getSpawnNumber()
{
        return spawnNumber;
}


int Animal::detection ( Environment * environment )
{
        int currentX = location[0];
        int currentY = location[1];
        int newX = 0;
        int newY = 0;

        int mapLength = environment->getMapLength();
        int detectionRangeSize = 0;

        std::vector<std::unordered_multimap<int, Animal *>> VisibleAnimals;
        std::vector<std::unordered_multimap<int, Plant *>> VisiblePlants;
        std::vector<std::vector<int>> CellSpecs;
        std::vector<std::vector<int>> detectionRange;

        if ( environment->getCell ( currentX, currentY )->getCellContentSpecs() [0] == 0 )
                dead ( environment );

        for ( int i = ( 0 - detectionRadius[growthState] ); i <= detectionRadius[growthState]; ++i ) {
                for ( int j = ( 0 - detectionRadius[growthState] ); j <= detectionRadius[growthState]; ++j ) {
                        newX = currentX+i;
                        newY = currentY+j;

                        if ( ( newX >= 0 && newX < mapLength ) && ( newY >= 0 && newY < mapLength ) )
                                detectionRange.push_back ( {currentX+i,currentY+j} );
                }
        }

        detectionRangeSize = detectionRange.size();

        for ( int cell = 0; cell < detectionRangeSize; ++cell ) {

                VisibleAnimals.push_back ( environment->getCell ( detectionRange[cell][0], detectionRange[cell][1] )->getCellContentAnimals() );
                VisiblePlants.push_back ( environment->getCell ( detectionRange[cell][0], detectionRange[cell][1] )->getCellContentPlants() );
                CellSpecs.push_back ( environment->getCell ( detectionRange[cell][0], detectionRange[cell][1] )->getCellContentSpecs() );
                
        }

        decision ( environment, &VisibleAnimals, &VisiblePlants, &CellSpecs );

        return 0;
}

int Animal::move ( Environment * environment )
{
        const unsigned int mapLength = environment->getMapLength();
        std::vector<int> locationOffset ( 2 );
        std::vector<int> newLocation ( 2 );

        oldLocation = location;

        locationOffset = { runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ), runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ) };

        for ( int coord=0; coord < 2; ++coord ) {
                newLocation[coord] = location[coord]+locationOffset[coord] < 0 ? 0 : location[coord]+locationOffset[coord];
                newLocation[coord] = location[coord]+locationOffset[coord] >= mapLength ? mapLength-1 : location[coord]+locationOffset[coord];
        }

        location = newLocation;

        environment->getCell ( oldLocation[0], oldLocation[1] )->removeAnimal ( id, this );
        environment->getCell ( location[0], location[1] )->addAnimal ( id, this );

        return 0;
}

int Animal::moveTowards ( Environment * environment, int X, int Y )
{

        const unsigned int mapLength = environment->getMapLength();
        std::vector<int> newLocation = {X,Y};

        oldLocation = location;

        for ( int coord=0; coord < 2; ++coord ) {
                newLocation[coord] = newLocation[coord] < 0 ? 0 : newLocation[coord];
                newLocation[coord] = newLocation[coord] >= mapLength ? mapLength-1 : newLocation[coord];
        }

        location = newLocation;

        environment->getCell ( oldLocation[0], oldLocation[1] )->removeAnimal ( id, this );
        environment->getCell ( location[0], location[1] )->addAnimal ( id, this );

        return 0;
}

int Animal::flee ( Environment * environment )
{
        move ( environment );
        return 0;
}

int Animal::eat ()
{

        int eatAmount = runRNG ( 1,25 );
        satietyIndex = satietyIndex + eatAmount > 100 ? 100 : satietyIndex + eatAmount;

        return 0;
}

int Animal::predation( Animal * target ){
    return 0;
}

int Animal::setHiddenState ( bool state )
{
        hidden = state;
        return 0;
}

int Animal::growth ( Environment * environment )
{

        unsigned int elapsedTime = environment->getMonth() - environment->getOriginMonth();

        timeLifeCycle += elapsedTime;

        if ( timeLifeCycle >= lifeCycle[growthState] ) {
                if ( satietyIndex < 80 || growthState+1 >= 3 ) {
                        dead ( environment );
                        return 0;
                }

                growthState += 1;
                growing = true;
                timeLifeCycle = 0;

        }

        return 0;
}

int Animal::reproduction ( std::unordered_multimap<int, Animal *> * VisibleAnimals, int specie )
{
        std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimals->equal_range ( 0 );

        int trigger = 0;

        for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it ) {
                if ( it->second->getSex() == 1 && ! it->second->getHiddenState() ) {
                        trigger = runRNG ( 0,100 );
                        if ( trigger < reproductionProbability ) {
                                it->second->setSpawnAbility ( true );
                                protectTerritory = false;
                                detectionRadius[2] = oldDetectionRadius;
                                return 0;
                        }
                }
        }

        return 0;
}

int Animal::attack ( Environment * environment, std::unordered_multimap<int, Animal *> * VisibleAnimals, int intruderX, int intruderY, int specie )
{
        std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimals->equal_range ( 0 );
        int X, Y = location[0],location[1];

        int trigger = 0;

        for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it ) {
                if ( it->second->getSex() == 0 ) {
                        trigger = runRNG ( 0, 1 );
                        if ( trigger == 0 )
                                it->second->flee ( environment );
                        if ( trigger == 1 )
                                move ( environment );
                }
        }

        return 0;
}

int Animal::dead ( Environment * environment )
{
        environment->getCell ( location[0], location[1] )->removeAnimal ( id, this );
        death = true;

        return 0;
}

