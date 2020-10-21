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
#ifndef __C_ANIMALS_H_INCLUDED__
#define __C_ANIMALS_H_INCLUDED__

class Environment;
class Plant;

class Animal
{
public :
        Animal ( int newId = 99,
                 std::string newName = "nothing",
                 std::vector<unsigned int> newlifeCycle = {1,1,1},
                 std::vector<int> newprobabilities = {0,0,0,0,0,0,0,0},
                 std::vector<int> newDetectionRadius = {2,2,2},
                 std::vector<int> newActionRadius = {1,1,1},
                 bool isBorn = false,
                 int spawnNumber = 1
               );

        virtual ~Animal () = 0;

        int run ( Environment * environment );

        int getID();
        std::string getName();
        int getSex();
        int getGrowthState();

        int setLocation ( std::vector<int> newLocation );
        int setOldLocation ( std::vector<int> newLocation );

        std::vector <int> getLocation();
        std::vector <int> getOldLocation();

        bool isDead();
        bool isSpawn();
        bool isGrowing();
        
        int stopSimulation();
        int continueSimulation();
        
        int growthFinished();

        bool getHiddenState();

        int setSpawnAbility ( bool newSpawnAbility );

        int getSpawnProbability();
        int getSpawnNumber();

        int flee( Environment * environment );
        
protected :

        int id = 0;
        std::string name;
        int spawnNumber = 0;

        std::vector<int> oldLocation{0,0};
        std::vector <int> location{0,0};
        std::vector<int> actionRadius{0,0,0};
        std::vector<int>  detectionRadius{0,0,0};

        int sex = 0; // 0 = male 1 = female

        bool simulationState = true;
        
        int length = 0;
        int growthState = 0;
        int oldDetectionRadius = 0;

        int satietyIndex = 100; // MAX 100 MIN 0

        int moveProbability = 0;
        int eatProbability = 0;
        int growthProbability = 0;
        int spawnProbability = 0;
        int deadProbability = 0 ;
        int reproductionProbability = 0;
        int attackProbability = 0;
        int protectionProbability = 0;

        unsigned int timeLifeCycle = 0;
        std::vector<unsigned int> lifeCycle{0,0,0};

        bool hidden = false;
        bool death = false;
        bool spawnAbility = false;
        bool growing = false;
        bool protectTerritory = false;

        std::vector<int> territoryCoordinates{0,0};

        // Detection step
        int detection ( Environment * environment );

        // Action step
        virtual int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs ) = 0;

        int move ( Environment * environment );
        int moveTowards ( Environment * environment, int X, int Y );
        int eat ();
        int predation( Animal * target );
        int setHiddenState ( bool state );
        int reproduction ( std::unordered_multimap<int, Animal *> * VisibleAnimals, int specie );
        int attack ( Environment * environment, std::unordered_multimap<int, Animal *> * VisibleAnimals, int intruderX, int intruderY, int specie );
        int growth ( Environment * environment );
        int dead ( Environment * environment );

};

class Leucorrhinia: public Animal
{
public :
        Leucorrhinia ( int id = 0,
                       std::string newName = "leucorrhinia",
                       std::vector<unsigned int> lifeCycle = {1,24,1},
                       std::vector<int> probabilities = {80,70,20,0,40,10,0,60},
                       std::vector<int> detectionRadius = {1,1,2},
                       std::vector<int> actionRadius = {1,1,1},
                       bool isBorn = false,
                       int newSpawnNumber = 100
                     ) : Animal ( id, newName, lifeCycle, probabilities, detectionRadius, actionRadius, isBorn, newSpawnNumber ) {}
        ~Leucorrhinia() {};
protected :
        int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs );

};

class Hyla: public Animal
{
public :
        Hyla ( int id = 1, std::string newName = "hyla",
               std::vector<unsigned int> lifeCycle = {1,24,1},
               std::vector<int> probabilities = {80,70,20,0,40,10,0,60},
               std::vector<int> detectionRadius = {1,1,2},
               std::vector<int> actionRadius = {1,1,1},
               bool isBorn = false,
               int newSpawnNumber = 100 ) :Animal ( id, newName, lifeCycle, probabilities, detectionRadius, actionRadius, isBorn, newSpawnNumber ) {}
        ~Hyla() {};
protected :
       int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs );
};

class Phengaris: public Animal
{
public :
        Phengaris ( int id = 2, std::string newName = "phengaris" ) :Animal ( id, newName ) {}
        ~Phengaris() {};
protected :
        int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs );
};

class Zootoca: public Animal
{
public :
        Zootoca ( int id = 3, std::string newName = "zootoca" ) :Animal ( id, newName ) {}
        ~Zootoca() {};
protected :
        int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs );
};

class Vipera: public Animal
{
public :
        Vipera ( int id = 4, std::string newName = "vipera" ) :Animal ( id, newName ) {}
        ~Vipera() {};
protected :
        int decision ( Environment * environment, std::vector<std::unordered_multimap<int, Animal *>> * VisibleAnimals, std::vector<std::unordered_multimap<int, Plant * >> * VisiblePlants, std::vector<std::vector<int>> * CellSpecs );
};

#endif // __C_ANIMALS_H_INCLUDED__





