#include "headers/C_animals.hpp"

typedef std::unordered_multimap<int, Animals *>::iterator MMAnimalIterator;

Animals::Animals ( int newId,
                   std::vector<unsigned int> newlifeCycle,
                   std::vector<int> newprobabilities,
                   std::vector<int> newDetectionRadius,
                   std::vector<int> newActionRadius,
                   bool isBorn )
{

    id = newId;
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

    if ( ! isBorn )
        growthState = runRNG ( 0,2 );
    else if ( isBorn )
        growthState = 0;

}

Animals::~Animals(){}

int Animals::getID()
{
    return id;
}

int Animals::run ( Environment * environment )
{
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

bool Animals::isSpawn ()
{
    return spawnAbility;
}

int Animals::getSex()
{
    return sex;
}

bool Animals::getHiddenState()
{
    return hidden;
}

int Animals::setSpawnAbility ( bool newSpawnAbility )
{
    spawnAbility = newSpawnAbility;
    return 0;

}

int Animals::getSpawnProbability()
{
    return spawnProbability;
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
    const unsigned int mapLength = environment->getMapLength();
    std::vector<int> locationOffset ( 2 );
    std::vector<int> savedLocation = {location[0],location[1]};
    std::vector<int> newLocation ( 2 );

    locationOffset = { runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ), runRNG ( 0-actionRadius[growthState], actionRadius[growthState] ) };

    for ( int coord=0; coord < 2; ++coord )
    {
        newLocation[coord] = location[coord]+locationOffset[coord] < 0 ? 0 : location[coord]+locationOffset[coord];
        newLocation[coord] = location[coord]+locationOffset[coord] >= mapLength ? mapLength-1 : location[coord]+locationOffset[coord];
    }

    satietyIndex -= ( abs ( savedLocation[0]-newLocation[0] ) + abs ( savedLocation[1]-newLocation[1] ) );

    if ( satietyIndex <= 0 )
    {
        satietyIndex = 0;
        int TestEatProbability = runRNG ( 0,100 );

        if ( TestEatProbability < eatProbability )
        {
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

int Animals::moveTowards ( Environment * environment, int X, int Y )
{

    const unsigned int mapLength = environment->getMapLength();
    std::vector<int> newLocation = {X,Y};
    std::vector<int> savedLocation = {location[0],location[1]};

    for ( int coord=0; coord < 2; ++coord )
    {
        newLocation[coord] = newLocation[coord] < 0 ? 0 : newLocation[coord];
        newLocation[coord] = newLocation[coord] >= mapLength ? mapLength-1 : newLocation[coord];
    }


    satietyIndex -= ( abs ( savedLocation[0]-newLocation[0] ) + abs ( savedLocation[1]-newLocation[1] ) );

    if ( satietyIndex <= 0 )
    {
        int TestEatProbability = runRNG ( 0,100 );

        if ( TestEatProbability < eatProbability )
        {
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
        if ( satietyIndex < 80 || growthState+1 >= 3 )
        {
            dead ( environment );
            return 0;
        }

        growthState += 1;
        timeLifeCycle = 0;

    }

    return 0;
}

int Animals::reproduction ( std::unordered_multimap<int, Animals *> * VisibleAnimals, int specie )
{
    std::pair<MMAnimalIterator, MMAnimalIterator> LeucoFound = VisibleAnimals->equal_range ( 0 );

    int trigger = 0;

    for ( MMAnimalIterator it = LeucoFound.first; it != LeucoFound.second; ++it )
    {
        if ( it->second->getSex() == 1 && ! it->second->getHiddenState() )
        {
            trigger = runRNG ( 0,100 );
            if ( trigger < reproductionProbability )
            {
                it->second->setSpawnAbility ( true );
            }
        }
    }

    return 0;
}

int Animals::attack ( Environment* environment )
{
    std::cout << "Attacking..." << std::endl;
    return 0;
}

int Animals::dead ( Environment * environment )
{
    environment->getCell ( location[0], location[1] )->removeAnimal ( id, this );
    death = true;
    return 0;
}
