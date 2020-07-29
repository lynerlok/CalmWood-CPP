#ifndef __C_ENVIRONMENT_H_INCLUDED__
#define __C_ENVIRONMENT_H_INCLUDED__

class Animal;
class Plant;
class Cell;

typedef std::unordered_multimap<int, Animal *>::iterator Aumit;
typedef std::unordered_multimap<int, Plant *>::iterator Pumit;
typedef std::vector<std::vector<Cell*>> MAP;

class Cell
{
public :
        Cell ( int newX = 0, int newY = 0 );
        ~Cell();

        int setViability ( bool newViability );

        bool getViabilityBoolean();

        int addAnimal ( int ID, Animal * animal );
        int removePlant ( int ID, Plant * plant );
        int removeAnimal ( int ID, Animal * animal );
        int addPlant ( int ID, Plant * plant );

        std::unordered_multimap<int, Animal *> getCellContentAnimals();
        std::unordered_multimap<int, Plant *> getCellContentPlants();
        std::vector<int> getCellContentSpecs();

        int toggleTrees();
        int toggleAnthropization();
        int toggleWetland();

protected :

        int X = 0;
        int Y = 0;

        int viability = 1;
        int containTrees = 0;
        int containAnthropization = 0;
        int containWetland = 1;
        int isWater = 0;

        int waterEutrophisationRate = 0;
        int waterPlantClosedRate = 0;
        int sunExpositionRate = 60;

        std::unordered_multimap<int, Animal *> AnimalCellContent;
        std::unordered_multimap<int, Plant *> PlantCellContent;

};

class Environment
{
public :
        Environment ();
        ~Environment ();

        int setTemperature ( float newTemperature );

        int setHygrometry ( float newHygrometry );

        int setAntropization ( float newAntropizationRate );

        int initializeEnvironmentMAP();

        int setEnvironmentParameters ( float newTemperature, float newHygrometry, float newAntropizationRate );

        unsigned int getTimeOfDay();

        int setTimeOfDay ( unsigned int newTimeOfDay );

        int setMonth ( unsigned int newMonthOfYear );

        unsigned int getMonth();

        unsigned int getOriginDayTime();

        unsigned int getOriginMonth();

        unsigned int getOriginYear();

        int setYear ( unsigned int newYear );

        unsigned int getYear();

        std::vector<float> getEnvironmentParameters();

        const unsigned int getMapLength();

        Cell * getCell ( int x, int y );
        
        int mapParser (std::string level);

        const int numberOfSpeciesAnimal = 5;
        const int numberOfSpeciesPlant = 5;

        int MaxNumberAgentAnimal = 0; // The max number of agent for the most large specie.
        std::vector<float> MaxNumberAgentByTypeAnimal; // MaxNumberAgentAnimal multiplicator !
        int MaxNumberAgentPlant = 0;
        std::vector<float> MaxNumberAgentByTypePlant; // MaxNumberAgentPlant multiplicator !
        int MaxDailyRun = 0;
        int MaxDayMonth = 0;
        int MaxTimeSimulation = 0;
        int RunDuration = 0;

protected :
        float temperature = 0.0;
        float hygrometry = 0.0 ;
        float antropizationRate = 0.0; // Default a super dry, cold and wild environment :)

        // map, action field
        unsigned int mapLength = 0;

        MAP map{mapLength};

        unsigned int timeOfDay = 0; // In hours always % 24
        unsigned int monthOfYear = 0; // Always % 12
        unsigned int yearOfSimulation = 0; // 2100 max

        const unsigned int originTimeOfDay = timeOfDay;
        const unsigned int originMonth = monthOfYear;
        const unsigned int originYear = yearOfSimulation;
        
        std::unordered_map<std::string, std::string> mapContent;
        std::vector<std::string> mapCells;
        std::unordered_map<std::string,std::vector<int>> mapCellsParameters;

};

#endif // __C_ENVIRONMENT_H_INCLUDED__
