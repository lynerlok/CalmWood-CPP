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

    const int MonthDuration = environment.MaxDayMonth * environment.MaxDailyRun;
    const int SimulationDuration = environment.MaxNumberAgentAnimal * environment.MaxTimeSimulation * environment.MaxDayMonth * environment.MaxDailyRun;
    const int AddDayTime = 24 / environment.MaxDailyRun;

    float runTime = environment.RunDuration;
    float monthTime = environment.MaxDayMonth;
    float simulationTime = SimulationDuration;

    int spawn ( Animal * animal );

};

#endif // __APP_SYSTEM_LOGIC_H__

