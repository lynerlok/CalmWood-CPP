#ifndef __GC_ENVIRONMENT_H_INCLUDED__
#define __GC_ENVIRONMENT_H_INCLUDED__

using namespace std;
using namespace Unigine;
using namespace Math;

class GAnimal;
class GPlant;
class AppSystemLogic;

class GEnvironment : public ComponentBase
{
public :
    COMPONENT ( GEnvironment, ComponentBase );

    COMPONENT_INIT ( init );
    COMPONENT_UPDATE ( update );
    COMPONENT_SHUTDOWN ( shutdown );

    PROP_NAME ( "environment" );

    PROP_PARAM ( Int, MaxNumberAgent, 10 ); // 100
    PROP_PARAM ( Int, PlantDensity, 1 );
    PROP_PARAM ( Int, MaxDailyRun, 1 ); // 10
    PROP_PARAM ( Int, MaxDayMonth, 2 ); // 30
    PROP_PARAM ( Int, MaxTimeSimulation, 4 ); // 12
    PROP_PARAM ( Int, RunDuration, 1 );

    void init();
    void update ();
    void shutdown();
};

#endif // __GC_ENVIRONMENT_H_INCLUDED__
