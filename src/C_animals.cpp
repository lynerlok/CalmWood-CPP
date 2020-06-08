#include "headers/C_animals.hpp"

typedef std::unordered_multimap<int, Animals *>::iterator MMAnimalIterator;

int Animals::getID()
{
    return id;
}

int Animals::run ( Environment * environment )
{
    // std::cout << "ID : " << getID() << std::endl;

    detection ( environment );

    return 0;
}

int Animals::setLocation ( std::vector<int> newLocation )
{
    if ( newLocation.size() != 3 )
        return -1;

    location = newLocation;

    return 0;
}

std::vector <int> Animals::getLocation()
{
    return location;
}

bool Animals::isDead()
{
    return death;
}

int Animals::getSex()
{
    return sex;
}

int Animals::setSpawnAbility ( bool newSpawnAbility )
{
    spawnAbility = newSpawnAbility;
    return 0;

}

int Animals::detection ( Environment * environment )
{
    int currentX = location[0];
    int currentY = location[1];
    int newX = 0;
    int newY = 0;

    int mapLength = environment->getMapLength();
    int detectionRangeSize = 0;

    std::unordered_multimap<int, Animals *> VisibleAnimals;
    std::unordered_map<int,int> VisiblePlants;
    std::vector<int> CellSpecs;
    std::vector<std::vector<int>> detectionRange;

    for ( int i = ( 0 - detectionRadius[growthState] ); i <= detectionRadius[growthState]; ++i )
    {
        for ( int j = ( 0 - detectionRadius[growthState] ); j <= detectionRadius[growthState]; ++j )
        {
            newX = currentX+i;
            newY = currentY+j;

            if ( ( newX >= 0 && newX < mapLength ) && ( newY >= 0 && newY < mapLength ) )
                detectionRange.push_back ( {currentX+i,currentY+j} );
        }
    }

    detectionRangeSize = detectionRange.size();

    runShuffle ( &detectionRange );

    for ( int i = 0; i < detectionRangeSize; ++i )
    {

        VisibleAnimals = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentAnimals();
        VisiblePlants = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentPlants();
        CellSpecs = environment->getCell ( detectionRange[i][0], detectionRange[i][1] )->getCellContentSpecs();

        decision ( environment, &VisibleAnimals, &VisiblePlants, &CellSpecs );
    }

    return 0;
}

int Animals::move ( Environment * environment )
{
    std::vector<int> locationOffset ( 2 );
    std::vector<int> savedLocation = {location[0],location[1]};

    const unsigned int mapLength = environment->getMapLength();

    environment->getCell ( location[0],location[1] )->removeAnimal ( id, this );

    locationOffset = { runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ), runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ) };

    for ( int coord=0; coord < 2; ++coord )
    {
        location[coord] = location[coord]+locationOffset[coord] < 0 ? 0 : location[coord]+locationOffset[coord];
        location[coord] = location[coord]+locationOffset[coord] >= mapLength ? mapLength-1 : location[coord]+locationOffset[coord];
    }

    satietyIndex -= ( abs ( savedLocation[0]-location[0] ) + abs ( savedLocation[1]-location[1] ) );

    if ( satietyIndex <= 0 )
    {
        int TestEatProbability = runRNG ( 0,100 );

        if ( TestEatProbability < eatProbability )
        {
            dead();
            return 0;
        }

        eat();
    }

    environment->getCell ( location[0],location[1] )->addAnimal ( id, this );

    detection ( environment );

    return 0;
}

int Animals::moveTowards ( Environment * environment, int X, int Y )
{

    int mapLength = environment->getMapLength();
    std::vector<int> newLocation = {X,Y};
    std::vector<int> savedLocation = {location[0],location[1]};

    environment->getCell ( location[0],location[1] )->removeAnimal ( id, this );

    for ( int coord=0; coord < 2; ++coord )
    {
        location[coord] = newLocation[coord] < 0 ? 0 : newLocation[coord];
        location[coord] = newLocation[coord] >= mapLength ? mapLength-1 : newLocation[coord];
    }

    satietyIndex -= ( abs ( savedLocation[0]-location[0] ) + abs ( savedLocation[1]-location[1] ) );

    if ( satietyIndex <= 0 )
    {
        int TestEatProbability = runRNG ( 0,100 );

        if ( TestEatProbability < eatProbability )
        {
            dead();
            return 0;
        }

        eat();
    }

    environment->getCell ( location[0], location[1] )->addAnimal ( id, this );

    detection ( environment );

    return 0;
}

int Animals::eat ()
{

    int eatAmount = runRNG ( 1,25 );
    satietyIndex = satietyIndex + eatAmount > 100 ? 100 : satietyIndex + eatAmount;

    return 0;
}

int Animals::setHiddenState ( bool state )
{
    hidden = state;
    return 0;
}

int Animals::growth ( Environment * environment )
{

    unsigned int elapsedTime = environment->getMonth() - environment->getOriginMonth();

    timeLifeCycle += elapsedTime;

    if ( timeLifeCycle >= lifeCycle[growthState] )
    {
        if ( satietyIndex < 80 )
        {
            dead();
            return 0;
        }

        growthState = growthState+1 >= 3 ? 2 : growthState+1; // HERE REMOVE THAT WHEN DEAD WILL BE IMPLEMENTED
        timeLifeCycle = 0;

    }

    if ( growthState == 3 )
        dead();

    return 0;
}

int Animals::reproduction ( std::unordered_multimap<int, Animals *> * VisibleAnimals )
{
    std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimals->equal_range ( 0 );
    for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it )
    {
        if ( it->second->getSex() == 1 )
        {
            if ( reproductionProbability <= runRNG ( 0,100 ) )
            {
                it->second->setSpawnAbility ( true );
            }
        }
    }
    
    return 0;
}

int Animals::spawn ( Environment* environment )
{
    std::cout << "Spawning" << std::endl;
    spawnAbility = false;
    
    return 0;
}


int Animals::dead()
{
    std::cout << "Unfortunaly i'm dead : " << id << std::endl;

    death = true;
    return 0;
}
