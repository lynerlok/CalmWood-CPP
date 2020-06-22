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

// DO NOT EDIT DIRECTLY. This is an auto-generated file. Your changes will be lost.

#pragma once

#include "UnigineObjects.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Visualizer
{
protected:
	

public:
	static int isInitialized(); 

	enum MODE
	{
		MODE_DISABLED,
		MODE_ENABLED_DEPTH_TEST_ENABLED,
		MODE_ENABLED_DEPTH_TEST_DISABLED,
	};
	static void setMode(Visualizer::MODE mode);
	static Visualizer::MODE getMode();
	static void setEnabled(bool enabled);
	static bool isEnabled();
	static void setSize(int size);
	static int getSize();
	static void setTextureName(const char *name);
	static const char *getTextureName();
	static void clear();
	static void renderPoint2D(const Math::vec3 &v, float size, const Math::vec4 &color);
	static void renderPoint3D(const Math::Vec3 & v, float size, const Math::vec4 &color, int screen_space = 0);
	static void renderLine2D(const Math::vec3 &v0, const Math::vec3 &v1, const Math::vec4 &color);
	static void renderLine3D(const Math::Vec3 & v0, const Math::Vec3 & v1, const Math::vec4 &color);
	static void renderLine2D(const Math::vec3 &v0, const Math::vec3 &v1, const Math::vec3 &v2, const Math::vec4 &color);
	static void renderLine3D(const Math::Vec3 & v0, const Math::Vec3 & v1, const Math::Vec3 & v2, const Math::vec4 &color);
	static void renderLine2D(const Math::vec3 &v0, const Math::vec3 &v1, const Math::vec3 &v2, const Math::vec3 &v3, const Math::vec4 &color);
	static void renderLine3D(const Math::Vec3 & v0, const Math::Vec3 & v1, const Math::Vec3 & v2, const Math::Vec3 & v3, const Math::vec4 &color);
	static void renderTriangle2D(const Math::vec3 &v0, const Math::vec3 &v1, const Math::vec3 &v2, const Math::vec4 &color);
	static void renderTriangle3D(const Math::Vec3 & v0, const Math::Vec3 & v1, const Math::Vec3 & v2, const Math::vec4 &color);
	static void renderQuad2D(const Math::vec3 &v0, const Math::vec3 &v1, const Math::vec3 &v2, const Math::vec3 &v3, const Math::vec4 &color);
	static void renderQuad3D(const Math::Vec3 & v0, const Math::Vec3 & v1, const Math::Vec3 & v2, const Math::Vec3 & v3, const Math::vec4 &color);
	static void renderBillboard3D(const Math::Vec3 & v, float size, const Math::vec4 &texcoord, int screen_space = 0);
	static void renderVector(const Math::Vec3 & position_start, const Math::Vec3 & position_end, const Math::vec4 &color, float arrow_size = 0.25f, int screen_space = 0);
	static void renderDirection(const Math::Vec3 & position, const Math::vec3 &direction, const Math::vec4 &color, float arrow_size = 0.25f, int screen_space = 1);
	static void renderBox(const Math::vec3 &size, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderFrustum(const Math::mat4 &projection, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderCircle(float radius, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSector(float radius, float angle, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderCone(float radius, float angle, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSphere(float radius, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderCapsule(float radius, float height, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderCylinder(float radius, float height, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderEllipse(const Math::vec3 &radius, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSolidBox(const Math::vec3 &size, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSolidSphere(float radius, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSolidCapsule(float radius, float height, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSolidCylinder(float radius, float height, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderSolidEllipse(const Math::vec3 &radius, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderBoundBox(const BoundBox & bb, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderBoundSphere(const BoundSphere & bs, const Math::Mat4 & transform, const Math::vec4 &color);
	static void renderNodeBoundBox(const Ptr<Node> &node, const Math::vec4 &color);
	static void renderNodeBoundSphere(const Ptr<Node> &node, const Math::vec4 &color);
	static void renderObjectSurfaceBoundBox(const Ptr<Object> &object, int surface, const Math::vec4 &color);
	static void renderObjectSurfaceBoundSphere(const Ptr<Object> &object, int surface, const Math::vec4 &color);
	static void renderNodeHandler(const Ptr<Node> &node);
	static void renderObject(const Ptr<Object> &object, const Math::vec4 &color);
	static void renderObjectSurface(const Ptr<Object> &object, int surface, const Math::vec4 &color);
	static void renderSolidObject(const Ptr<Object> &object, const Math::vec4 &color);
	static void renderSolidObjectSurface(const Ptr<Object> &object, int surface, const Math::vec4 &color);
	static void renderMessage2D(const Math::vec3 &position, const Math::vec3 &center, const char *str, const Math::vec4 &color, int outline);
	static void renderMessage2D(const Math::vec3 &position, const Math::vec3 &center, const char *str, const Math::vec4 &color, int outline, int font_size);
	static void renderMessage3D(const Math::Vec3 & position, const Math::vec3 &center, const char *str, const Math::vec4 &color, int outline);
	static void renderMessage3D(const Math::Vec3 & position, const Math::vec3 &center, const char *str, const Math::vec4 &color, int outline, int font_size);
};

} // namespace Unigine
