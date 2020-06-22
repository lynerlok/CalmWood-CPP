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

#include "UnigineBase.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Config
{
protected:
	

public:
	static int isInitialized(); 
	static bool flush();
	static bool load(const char *name);
	static bool save(const char *name);
	static bool isExist(const char *name);
	static void remove(const char *name);
	static void setBool(const char *name, bool value);
	static bool getBool(const char *name, bool value);
	static bool getBool(const char *name);
	static void setInt(const char *name, int value);
	static int getInt(const char *name, int value);
	static int getInt(const char *name);
	static void setFloat(const char *name, float value);
	static float getFloat(const char *name, float value);
	static float getFloat(const char *name);
	static void setString(const char *name, const char *value);
	static const char *getString(const char *name, const char *value);
	static const char *getString(const char *name);
};

} // namespace Unigine
