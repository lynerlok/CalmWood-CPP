#include "headers/C_animals.hpp"

int Animals::getID()
{
    return id;
}

int Animals::run ( Environment * environment )
{
    std::cout << "ID : " << getID() << std::endl;

    std::vector<int> probabilities = getProbabilities();

    detection ( environment );

    for ( int alteration = 0; alteration < 4; ++alteration )
    {
        triggerAgent ( environment,alteration,probabilities[alteration] );
    }

    return 0;
}

int Animals::setLocation ( std::vector<float> newLocation )
{
    if ( newLocation.size() != 3 )
        return -1;

    location = newLocation;

    return 0;
}

std::vector <float> Animals::getLocation()
{
    return location;
}

std::vector<int> Animals::getProbabilities()
{

    std::vector<int> probabilities = {moveProbability, eatProbability, growthProbability, deadProbability};

    return probabilities;
}

int Animals::triggerAgent ( Environment * environment, int alterationType, int associatedProbability )
{
    if ( ( runRNG ( 0,100 ) ) < associatedProbability )
    {

        switch ( alterationType )
        {
        case 0 : // move
            std::cout << "MOVE" << std::endl;
            move ( environment );
            break;
        case 1 : // eat
            std::cout << "EAT" << std::endl;
            eat ( environment );
            break;
        case 2 : // growth
            std::cout << "GROWTH" << std::endl;
            growth ( environment );
            break;
        case 3 : // dead
            std::cout << "DEAD" << std::endl;
            dead();
            break;
        }
    }


    return 0;
}

bool Animals::isDead()
{
    return death;
}

int Animals::detection ( Environment * environment )
{
    int currentX = getLocation() [0];
    int currentY = getLocation() [1];
    int newX = 0;
    int newY = 0;

    int mapLength = environment->getMapLength();
    int detectionRangeSize = 0;

    std::unordered_map<int,int> VisibleAnimals;
    std::unordered_map<int,int> VisiblePlants;
    std::vector<int> CellSpecs;
    std::vector<std::vector<int>> detectionRange;

    for ( int i = ( 0 - detectionRadius ); i <= detectionRadius; ++i )
    {
        for ( int j = ( 0 - detectionRadius ); j <= detectionRadius; ++j )
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
    std::vector<float> newLocation ( 3 );

    int locationOffset = 0;
    int orientation = 0;

    const unsigned int mapLength = environment->getMapLength();

    environment->getCell ( location[0],location[1] )->removeAnimal ( id, this );

    do
    {
        for ( int i=0; i<2; ++i )
        {
            locationOffset = runRNG ( 0, actionRadius );
            orientation = runRNG ( 0,1 );

            satietyIndex -= locationOffset;

            if ( satietyIndex <= 0 )
            {
                if ( triggerAgent ( environment,2, eatProbability ) == 0 )
                    dead();
            }

            if ( orientation )
            {
                newLocation[i] = location[i] + locationOffset;
                if ( newLocation[i] < mapLength )
                {
                    location[i] = newLocation[i];
                }

            }

            if ( ! orientation )
            {
                newLocation[i] = location[i] - locationOffset;
                if ( newLocation[i] > 0 )
                {
                    location[i] = newLocation[i];
                }
            }
        }
    }
    while ( ! environment->getCell ( location[0],location[1] )->getViabilityBoolean() );

    environment->getCell ( location[0],location[1] )->addAnimal ( id, this );

    detection ( environment );

    return 0;
}

int Animals::moveTowards ( Environment * environment, int X, int Y )
{

    int mapLength = environment->getMapLength();

    if ( ( X < 0 && X >= mapLength ) && ( Y < 0 && Y >= mapLength ) )
        return -1;

    environment->getCell ( location[0],location[1] )->removeAnimal ( id, this );
    
    location[0] = X;
    location[1] = Y;
    
    environment->getCell ( X,Y )->addAnimal ( id, this );

    return 0;
}

int Animals::eat ( Environment * environment )
{

    // detection ( environment );

    int eatAmount = runRNG ( 1,25 );
    satietyIndex = ( satietyIndex + eatAmount ) % 100;

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
    
    std::cout << "Grow state : " << growthState << std::endl;
    
    if( growthState >= 3)
        return -1;
    
    if ( timeLifeCycle >= lifeCycle[growthState] )
    {
        if ( satietyIndex < 80 ){
            dead();
            return 0;
        }
        
        growthState += 1;
        timeLifeCycle = 0;

    }

    if ( growthState == 3 )
        dead();

    return 0;
}

int Animals::dead()
{
    std::cout << "Unfortunaly i'm dead : " << id << std::endl;
    death = true;
    return 0;
}
