#ifndef __GC_ANIMAL_H_INCLUDED__
#define __GC_ANIMAL_H_INCLUDED__

using namespace std;
using namespace Unigine;
using namespace Math;

class Animal;

class GAnimal : public ComponentBase
{
public :
        COMPONENT ( GAnimal, ComponentBase );

        COMPONENT_INIT ( init );
        COMPONENT_UPDATE ( update );
        COMPONENT_SHUTDOWN ( shutdown );

        PROP_NAME ( "animal" );
        PROP_PARAM ( Int, id, 99 );

        int setAnimal ( Animal *newAnimal );

        int run ( Environment * environment );

        bool isDead();

        bool isSpawn();

        bool getSpawnProbability();

protected :

        Animal *animal;
        float ifps = 0.0f;
        float rotationTrigger = 3.0f;
        vector<float> rotation = {0.0f,0.0f,0.0f};
        vector<int> hook;
        vector<int> oldHook;
        float X = 0.0f;
        float Y = 0.0f;
        
        float movement_speed = 5.0f;
        float angle = ( float ) runRNG ( -180,180 );
        
        bool changeHook = false;
    
        void init();
        void update();
        void shutdown();

        int move ( float ifps );

};

#endif // __GC_ANIMAL_H_INCLUDED__
