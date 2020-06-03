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

int Animals::setName ( std::string newName )
{
    name = newName;
    return 0;
}

std::string Animals::getName()
{
    return name;
}

int Animals::setParameters ( int newLength,
                             int newActionRadius,
                             int newDetectionRadius,
                             int newGrowthState,
                             int newSex )
{

    length = newLength;
    actionRadius = newActionRadius;
    detectionRadius = newDetectionRadius;
    growthState = newGrowthState;
    sex = newSex;


    return 0;
}

int Animals::setProbabilities ( int newMoveProbability,
                                int newEatProbability,
                                int newGrowthProbability,
                                int newDeadProbability )
{

    moveProbability = newMoveProbability;
    eatProbability = newEatProbability;
    growthProbability = newGrowthProbability;
    deadProbability = newDeadProbability;


    return 0;
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
            growth();
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
    int x = getLocation() [0];
    int y = getLocation() [1];

    std::unordered_map<int,int> VisibleAnimals;
    std::unordered_map<int,int> VisiblePlants;
    std::vector<int> CellSpecs;

    VisibleAnimals = environment->getCell ( x,y )->getCellContentAnimals();
    VisiblePlants = environment->getCell ( x,y )->getCellContentPlants();
    CellSpecs = environment->getCell ( x,y )->getCellContentSpecs();

    decision ( environment, &VisibleAnimals, &VisiblePlants, &CellSpecs );

    return 0;
}

int Leucorrhinia::decision ( Environment * environment, std::unordered_map<int,int> * VisibleAnimals, std::unordered_map<int,int> * VisiblePlants, std::vector<int> * CellSpecs )
{

    // {viability,containTrees,containAnthropization,containWetland};

    int timeOfDay = environment->getTimeOfDay();
    int month = environment->getMonth();
    int viability = CellSpecs->at ( 0 );

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

int Animals::move ( Environment * environment )
{
    std::vector<float> location ( 3 );
    std::vector<float> newLocation ( 3 );

    int locationOffset = 0;
    int orientation = 0;

    const unsigned int mapLength = environment->getMapLength();

    location = getLocation();
    environment->getCell ( location[0],location[1] )->removeAnimal ( id, this );

    do
    {
        location = getLocation();

        for ( int i=0; i<2; ++i )
        {
            locationOffset = runRNG ( 0,actionRadius );
            orientation = runRNG ( 0,1 );

            satietyIndex -= locationOffset;

            if ( satietyIndex <= 0 )
            {
                if ( triggerAgent ( environment,2,eatProbability ) == 0 )
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

    setLocation ( location );
    environment->getCell ( location[0],location[1] )->addAnimal ( id, this );

    detection ( environment );

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

int Animals::growth()
{

    if ( satietyIndex > 80 )
    {
        growthState += 1;
        if ( growthState >= 3 )
        {
            dead();
        }
    }

    return 0;
}

int Animals::dead()
{
    death = true;
    return 0;
}
