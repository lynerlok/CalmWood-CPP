#ifndef __GC_ENVIRONMENT_H_INCLUDED__
#define __GC_ENVIRONMENT_H_INCLUDED__

using namespace std;
using namespace Unigine;
using namespace Math;

class GAnimal;
class GPlant;

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
        void update ( float ifps );
        void shutdown();

        int triggerSimulationEnd();

protected :

        Environment environment;
        vector<ObjectMeshStaticPtr> animalMesh;
        vector<ObjectMeshStaticPtr> plantMesh;
        vector<ObjectMeshStaticPtr>::iterator agent;
        
        GAnimal * animal;
        GPlant * plant;
        int agentNumber = 0;

        std::string meshPathStr;
        const char *meshPathConst;
        ObjectMeshStaticPtr temporaryMesh;
        PropertyPtr property;
        PropertyParameterPtr param;

        const int MonthDuration = MaxDayMonth * MaxDailyRun;
        const int SimulationDuration = MaxTimeSimulation * MaxDayMonth * MaxDailyRun;
        const int AddDayTime = 24 / MaxDailyRun;

        float runTime = RunDuration;
        float monthTime = MaxDayMonth;
        float simulationTime = SimulationDuration;

        int deadCount = 0;
        int spawnCount = 0;

        bool simulationEnd = false;
        float ifps = 0.0;

        int spawn ( GAnimal * animal );
        
};

#endif // __GC_ENVIRONMENT_H_INCLUDED__
