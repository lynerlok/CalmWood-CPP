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

        bool isMoving = false;

        vector<int> hook{2};
        vector<int> coord{2};
        vector<int> goal{2};

        float X = 0.0f;
        float Y = 0.0f;

        float movement_speed = 5.0f;
        float angleMultiplicator = 1.2f;
        float angle = 0.0f;

        void init();
        void update();
        void shutdown();

        int move ( float ifps );

        int landOff ( float ifps );

        int landOffProbability = 0;

};

#endif // __GC_ANIMAL_H_INCLUDED__
