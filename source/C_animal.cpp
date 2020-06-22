#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "U_randomGenerator.hpp"
#include "C_environment.hpp"
#include "C_animal.hpp"

typedef std::unordered_multimap<int, Animal *>::iterator MMAnimalIterator;

Animal::Animal ( int newId,
                 std::string newName,
                 std::vector<unsigned int> newlifeCycle,
                 std::vector<int> newprobabilities,
                 std::vector<int> newDetectionRadius,
                 std::vector<int> newActionRadius,
                 bool isBorn )
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

        actionRadius = newActionRadius;
        detectionRadius = newDetectionRadius;

        length = runRNG ( 0,10 );
        sex = runRNG ( 0,1 );

        growthState = isBorn ? 0 : runRNG ( 0,2 );

}

Animal::~Animal() {}

int Animal::getID()
{
        return id;
}

std::string Animal::getName()
{
    return name;
}

int Animal::run ( Environment * environment )
{
        detection ( environment );

        return 0;
}

int Animal::setLocation ( std::vector<int> newLocation )
{
        if ( newLocation.size() != 3 )
                return -1;

        location = newLocation;

        return 0;
}

std::vector <int> Animal::getLocation()
{
        return location;
}

bool Animal::isDead()
{
        return death;
}

bool Animal::isSpawn ()
{
        return spawnAbility;
}

int Animal::getSex()
{
        return sex;
}

bool Animal::getHiddenState()
{
        return hidden;
}

int Animal::setSpawnAbility ( bool newSpawnAbility ) // RDI + offset
{
        if ( newSpawnAbility ) // Carteful this is string in assembly !!! so test sil, sil
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


int Animal::detection ( Environment * environment )
{
        int currentX = location[0];
        int currentY = location[1];
        int newX = 0;
        int newY = 0;

        int mapLength = environment->getMapLength();
        int detectionRangeSize = 0;

        std::unordered_multimap<int, Animal *> VisibleAnimals;
        std::unordered_map<int,int> VisiblePlants;
        std::vector<int> CellSpecs;
        std::vector<std::vector<int>> detectionRange;

        for ( int i = ( 0 - detectionRadius[growthState] ); i <= detectionRadius[growthState]; ++i ) {
                for ( int j = ( 0 - detectionRadius[growthState] ); j <= detectionRadius[growthState]; ++j ) {
                        newX = currentX+i;
                        newY = currentY+j;

                        if ( ( newX >= 0 && newX < mapLength ) && ( newY >= 0 && newY < mapLength ) )
                                detectionRange.push_back ( {currentX+i,currentY+j} );
                }
        }

        detectionRangeSize = detectionRange.size();

        runShuffle ( &detectionRange );

        for ( int i = 0; i < detectionRangeSize; ++i ) {

                VisibleAnimals = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentAnimals();
                VisiblePlants = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentPlants();
                CellSpecs = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentSpecs();

                decision ( environment, &VisibleAnimals, &VisiblePlants, &CellSpecs );
        }

        return 0;
}

int Animal::move ( Environment * environment )
{
        const unsigned int mapLength = environment->getMapLength();
        std::vector<int> locationOffset ( 2 );
        std::vector<int> savedLocation = {location[0],location[1]};
        std::vector<int> newLocation ( 2 );

        locationOffset = { runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ), runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ) };

        for ( int coord=0; coord < 2; ++coord ) {
                newLocation[coord] = location[coord]+locationOffset[coord] < 0 ? 0 : location[coord]+locationOffset[coord];
                newLocation[coord] = location[coord]+locationOffset[coord] >= mapLength ? mapLength-1 : location[coord]+locationOffset[coord];
        }

        satietyIndex -= ( abs ( savedLocation[0]-newLocation[0] ) + abs ( savedLocation[1]-newLocation[1] ) );

        if ( satietyIndex <= 0 ) {
                satietyIndex = 0;
                int TestEatProbability = runRNG ( 0,100 );

                if ( TestEatProbability < eatProbability ) {
                        dead ( environment );
                        return 0;
                }

                eat();
        }

        location[0], location[1] = newLocation[0], newLocation[1];

        environment->getCell ( savedLocation[0],savedLocation[1] )->removeAnimal ( id, this );
        environment->getCell ( location[0], location[1] )->addAnimal ( id, this );

        detection ( environment );

        return 0;
}

int Animal::moveTowards ( Environment * environment, int X, int Y )
{

        const unsigned int mapLength = environment->getMapLength();
        std::vector<int> newLocation = {X,Y};
        std::vector<int> savedLocation = {location[0],location[1]};

        for ( int coord=0; coord < 2; ++coord ) {
                newLocation[coord] = newLocation[coord] < 0 ? 0 : newLocation[coord];
                newLocation[coord] = newLocation[coord] >= mapLength ? mapLength-1 : newLocation[coord];
        }


        satietyIndex -= ( abs ( savedLocation[0]-newLocation[0] ) + abs ( savedLocation[1]-newLocation[1] ) );

        if ( satietyIndex <= 0 ) {
                int TestEatProbability = runRNG ( 0,100 );

                if ( TestEatProbability < eatProbability ) {
                        dead ( environment );
                        return 0;
                }

                eat();
        }

        location[0], location[1] = newLocation[0], newLocation[1];

        environment->getCell ( savedLocation[0], savedLocation[1] )->removeAnimal ( id, this );
        environment->getCell ( location[0], location[1] )->addAnimal ( id, this );

        detection ( environment );

        return 0;
}

int Animal::eat ()
{

        int eatAmount = runRNG ( 1,25 );
        satietyIndex = satietyIndex + eatAmount > 100 ? 100 : satietyIndex + eatAmount;

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
                timeLifeCycle = 0;

        }

        return 0;
}

int Animal::reproduction ( std::unordered_multimap<int, Animal *> * VisibleAnimal, int specie )
{
        std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimal->equal_range ( 0 );

        int trigger = 0;

        for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it ) {
                if ( it->second->getSex() == 1 && ! it->second->getHiddenState() ) {
                        trigger = runRNG ( 0,100 );
                        if ( trigger < reproductionProbability ) {
                                it->second->setSpawnAbility ( true );
                        }
                }
        }

        return 0;
}

int Animal::attack ( Environment * environment, std::unordered_multimap<int, Animal *> * VisibleAnimal, int intruderX, int intruderY, int specie )
{
        std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimal->equal_range ( 0 );
        int X, Y = location[0],location[1];

        int trigger = 0;

        for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it ) {
                if ( it->second->getSex() == 0 ) {
                        trigger = runRNG ( 0,100 );

                        if ( trigger < deadProbability ) {
                                dead ( environment );
                                return 0;
                        } else if ( trigger > deadProbability ) {
                                it->second->killed ( environment );
                        }
                }
        }

        return 0;
}

int Animal::killed ( Environment * environment )
{
        environment->getCell ( location[0], location[1] )->removeAnimal ( id, this );
        death = true;
        return 0;
}

int Animal::dead ( Environment * environment )
{
        environment->getCell ( location[0], location[1] )->removeAnimal ( id, this );
        death = true;
        return 0;
}
