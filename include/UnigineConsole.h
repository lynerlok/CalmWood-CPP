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
#include "UnigineMathLib.h"
#include "UnigineCallback.h"

namespace Unigine
{

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Console
{
protected:
	

public:
	static int isInitialized(); 

	enum
	{
		LEVEL_NORMAL = 0,
		LEVEL_WARNING,
		LEVEL_ERROR,
	};
	static void setActivity(bool activity);
	static bool getActivity();
	static void run(const char *command);
	static void flush();
	static int getNumVariables();
	static const char *getVariableName(int num);
	static const char *getVariableDescription(const char *name);
	static int getNumCommands();
	static const char *getCommandName(int num);
	static const char *getCommandDescription(const char *name);
	static bool isCommand(const char *name);
	static bool isVariable(const char *name);
	static bool isInt(const char *name);
	static void setInt(const char *name, int value);
	static int getInt(const char *name);
	static int getIntMin(const char *name);
	static int getIntMax(const char *name);
	static bool isFloat(const char *name);
	static void setFloat(const char *name, float value);
	static float getFloat(const char *name);
	static float getFloatMin(const char *name);
	static float getFloatMax(const char *name);
	static bool isVec4(const char *name);
	static void setVec4(const char *name, const Math::vec4 &value);
	static Math::vec4 getVec4(const char *name);
	static bool isVec3(const char *name);
	static void setVec3(const char *name, const Math::vec3 &value);
	static Math::vec3 getVec3(const char *name);
	static bool isVec2(const char *name);
	static void setVec2(const char *name, const Math::vec2 &value);
	static Math::vec2 getVec2(const char *name);
	static bool isString(const char *name);
	static void setString(const char *name, const char *value);
	static const char *getString(const char *name);
	static int addCommand(const char *name, const char *desc, Unigine::CallbackBase2<int, char **> *func);
	static bool removeCommand(const char *name);
	static void *addOutputCallback(Unigine::CallbackBase2< const char *, int > *func);
	static bool removeOutputCallback(void *id);
	static void clearOutputCallbacks();
	static void setBackgroundColor(const Math::vec4 &color);
	static void setMessageColor(const Math::vec4 &color);
	static void setWarningColor(const Math::vec4 &color);
	static void setErrorColor(const Math::vec4 &color);
	static void setTextColor(const Math::vec4 &color);
	static void setPrompt(const char *str);
	static void setLock(int lock);
	static int getLock();
};

class UNIGINE_API ConsoleVariableInt
{
	public:
		ConsoleVariableInt(const char *name, const char *desc, int save, int value, int min, int max);
		~ConsoleVariableInt();
		UNIGINE_INLINE int operator=(int value) { set(value); return value; }
		UNIGINE_INLINE operator int() const { return get(); }
		void set(int value) const;
		int get() const;
	private:
		void *data;
};

class UNIGINE_API ConsoleVariableFloat
{
	public:
		ConsoleVariableFloat(const char *name, const char *desc, int save, float value, float min, float max);
		~ConsoleVariableFloat();
		UNIGINE_INLINE float operator=(float value) { set(value); return value; }
		UNIGINE_INLINE operator float() const { return get(); }
		void set(float value) const;
		float get() const;
	private:
		void *data;
};

class UNIGINE_API ConsoleVariableVec4
{
	public:
		ConsoleVariableVec4(const char *name, const char *desc, int save, const Math::vec4 &value);
		~ConsoleVariableVec4();
		UNIGINE_INLINE Math::vec4 operator=(const Math::vec4 &value) { set(value); return value; }
		UNIGINE_INLINE operator Math::vec4() const { return get(); }
		void set(const Math::vec4 &value) const;
		Math::vec4 get() const;
	private:
		void *data;
};

class UNIGINE_API ConsoleVariableVec3
{
	public:
		ConsoleVariableVec3(const char *name, const char *desc, int save, const Math::vec3 &value);
		~ConsoleVariableVec3();
		UNIGINE_INLINE Math::vec3 operator=(const Math::vec3 &value) { set(value); return value; }
		UNIGINE_INLINE operator Math::vec3() const { return get(); }
		void set(const Math::vec3 &value) const;
		Math::vec3 get() const;
	private:
		void *data;
};

class UNIGINE_API ConsoleVariableVec2
{
	public:
		ConsoleVariableVec2(const char *name, const char *desc, int save, const Math::vec2 &value);
		~ConsoleVariableVec2();
		UNIGINE_INLINE Math::vec2 operator=(const Math::vec2 &value) { set(value); return value; }
		UNIGINE_INLINE operator Math::vec2() const { return get(); }
		void set(const Math::vec2 &value) const;
		Math::vec2 get() const;
	private:
		void *data;
};

class UNIGINE_API ConsoleVariableString
{
	public:
		ConsoleVariableString(const char *name, const char *desc, int save, const char *value);
		~ConsoleVariableString();
		UNIGINE_INLINE const char *operator=(const char *value) { set(value); return value; }
		UNIGINE_INLINE operator const char*() const { return get(); }
		void set(const char *value) const;
		const char *get() const;
	private:
		void *data;
};
} // namespace Unigine
