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
        Cell ( int newX = 0, int newY = 0, std::string name = "default" );
        ~Cell();

        int setViability ( bool newViability );

        bool getViabilityBoolean();
        
        std::string getName();

        int addAnimal ( int ID, Animal * animal );
        int removePlant ( int ID, Plant * plant );
        int removeAnimal ( int ID, Animal * animal );
        int addPlant ( int ID, Plant * plant );

        std::unordered_multimap<int, Animal *> getCellContentAnimals();
        std::unordered_multimap<int, Plant *> getCellContentPlants();
        std::vector<int> getCellContentSpecs();

        int setTrees( int status );
        int setAnthropization( int status );
        int setWetland( int status );
        int setViability( int status );
        int setWater( int status );
        int setRates( std::vector<int> rates );

protected :

        int X = 0;
        int Y = 0;
        std::string name;

        int viability = 1;
        int containTrees = 0;
        int containAnthropization = 0;
        int containWetland = 1;
        int isWater = 0;

        int waterEutrophisationRate = 0;
        int waterPlantClosedRate = 0;
        int sunExpositionRate = 50;

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

        int setAnthropization ( float newAnthropizationRate );

        int initializeEnvironmentMAP();

        int setEnvironmentParameters ( float newTemperature, float newHygrometry, float newAntropizationRate );

        int setMonth ( unsigned int newMonthOfYear );

        unsigned int getMonth();

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
        std::string timeType = "month";
        int MaxAgentRun = 0;
        int MaxRunPerRunTime = 0;
        int MaxRunTime = 0;
        float RunDuration = 0;

protected :
        float temperature = 0.0;
        float hygrometry = 0.0 ;
        float anthropizationRate = 0.0; // Default a super dry, cold and wild environment :)

        // map, action field
        unsigned int mapLength = 1;

        MAP map{300};

        unsigned int monthOfYear = 0; // Always % 12
        unsigned int yearOfSimulation = 0; // 2100 max

        unsigned int originMonth = 0;
        unsigned int originYear = 0;
        
        std::unordered_map<std::string, std::string> mapContent;
        std::vector<std::vector<std::string>> mapCells{300};
        std::unordered_map<std::string,std::vector<int>> mapCellsParameters;

};

#endif // __C_ENVIRONMENT_H_INCLUDED__
