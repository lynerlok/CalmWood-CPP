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

private:

    WidgetLabelPtr label;
    PlayerDummyPtr player;
    LightWorldPtr sun;

    float ifps = 0.0f;
    
    // method creating a box
    ObjectMeshDynamicPtr create_box ( const Mat4 &transform, const vec3 &size );
};

#endif // __APP_WORLD_LOGIC_H__

