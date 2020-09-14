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
#ifndef __C_PLANTS_H_INCLUDED__
#define __C_PLANTS_H_INCLUDED__

class Environment;

class Plant
{
public:
    Plant ( int newId = 0, std::string newName = "default" );
    ~Plant ();

    int getID();
    std::string getName();

    int growth ( int targetState );
    int damage();

    int setLocation ( std::vector<int> newLocation );
    std::vector <int> getLocation();
    
    int dead(Environment * environment);
    bool isDead();

protected :
    int id=0;
    std::string name;

    bool death = false;
    std::vector <int> location{0,0,0};

};

class Gentiania: public Plant
{
public :
    Gentiania ( int id = 0 ) :Plant ( id ) {}
};

class Juncus: public Plant
{
public :
    Juncus ( int id = 1 ) :Plant ( id ) {}
};

class Glyceria: public Plant
{
public :
    Glyceria ( int id = 2 ) :Plant ( id ) {}
};

class Carex: public Plant
{
public :
    Carex ( int id = 3 ) :Plant ( id ) {}
};

class Iris: public Plant
{
public :
    Iris ( int id = 4 ) :Plant ( id ) {}
};


#endif // __C_PLANTS_H_INCLUDED__

