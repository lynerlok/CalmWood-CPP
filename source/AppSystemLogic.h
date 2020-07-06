/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2.11.0.1 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */


#ifndef __APP_SYSTEM_LOGIC_H__
#define __APP_SYSTEM_LOGIC_H__

using namespace Unigine;
using namespace Math;
using namespace std;

class AppWorldLogic;

class AppSystemLogic : public Unigine::SystemLogic
{
public:
    AppSystemLogic();
    virtual ~AppSystemLogic();

    int init() override;

    int update() override;
    int postUpdate() override;

    int shutdown() override;

    AppWorldLogic *worldlogic_ptr;

    vector<Animal *> animals;
    vector<Plant *> plants;

protected :
    Environment environment;
    
    vector<Animal *>::iterator agentAnimal;
    vector<Plant *>::iterator agentPlant;

    int deadCount = 0;
    int spawnCount = 0;

    bool simulationEnd = false;
    float ifps = 0.0;

    vector<int> location = {0,0};

    int MaxNumberAgent = 10; // 100
    int PlantDensity = 1;
    int MaxDailyRun = 1; // 10
    int MaxDayMonth = 2; // 30
    int MaxTimeSimulation = 1; // 12
    int RunDuration = 1;

    const int MonthDuration = MaxDayMonth * MaxDailyRun;
    const int SimulationDuration = MaxNumberAgent * MaxTimeSimulation * MaxDayMonth * MaxDailyRun;
    const int AddDayTime = 24 / MaxDailyRun;

    float runTime = RunDuration;
    float monthTime = MaxDayMonth;
    float simulationTime = SimulationDuration;

    int spawn ( Animal * animal );

};

#endif // __APP_SYSTEM_LOGIC_H__

