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
 * 
 * Modified by Axel Polin, 2020, univ_apolin@protonmail.com
 */

#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__


using namespace Unigine;
using namespace Math;
using namespace std;

class AppSystemLogic;

class AppWorldLogic : public Unigine::WorldLogic
{

public:
    AppWorldLogic();
    virtual ~AppWorldLogic();

    int init() override;

    int update() override;
    int postUpdate() override;
    int updatePhysics() override;

    int shutdown() override;

    int save ( const Unigine::StreamPtr &stream ) override;
    int restore ( const Unigine::StreamPtr &stream ) override;

    AppSystemLogic *systemlogic_ptr;

    int createAnimal ( Animal * animal );
    
    int removeAnimal ( Animal * animal );
    
    int getAnimalCount ( int id, int growthState );

private:
    
    WidgetLabelPtr label;
    PlayerDummyPtr player;
    LightWorldPtr sun;

    vector<ObjectMeshSkinnedPtr> animalMesh;
    vector<ObjectMeshSkinnedPtr> plantMesh;
    vector<Animal *> animals;
    vector<Plant *> plants;
    vector<ObjectMeshSkinnedPtr>::iterator agent;
    vector<Animal *>::iterator agentAnimal;
    vector<Plant *>::iterator agentPlant;
    MeshPtr mesh;

    vector<int> agentLocation = {0,0};
    int direction = 0;

    std::string meshPathStr;
    const char *meshPathConst;
    ObjectMeshSkinnedPtr temporaryMesh;
    PropertyPtr property;
    PropertyParameterPtr param;

    float ifps = 0.0f;

};

#endif // __APP_WORLD_LOGIC_H__

