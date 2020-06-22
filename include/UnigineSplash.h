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

#include "UnigineImage.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Splash
{
protected:
	

public:
	static int isInitialized(); 
	static void setColor(const Math::vec4 &color);
	static void setSplash(const char *name, int threshold = 0);
	static void setSplashImage(const Ptr<Image> &image, int threshold = 0);
	static void setSplashTransform(const Math::vec4 &transform);
	static void setSplashBackground(const Math::vec4 &color);
	static void setSplashText(const char *str);
	static void setSystem(const char *name, int threshold = 0);
	static void setSystemImage(const Ptr<Image> &image, int threshold = 0);
	static void setSystemTransform(const Math::vec4 &transform);
	static void setSystemBackground(const Math::vec4 &color);
	static void setSystemText(const char *str);
	static void setWorld(const char *name, int threshold = 0);
	static void setWorldImage(const Ptr<Image> &image, int threshold = 0);
	static void setWorldTransform(const Math::vec4 &transform);
	static void setWorldBackground(const Math::vec4 &color);
	static void setWorldText(const char *str);
	static void setEnabled(bool enabled);
	static bool isEnabled();
	static void renderSplash(int progress);
	static void renderSystem(int progress);
	static void renderWorld(int progress);
	static void renderInterface();
};

} // namespace Unigine
