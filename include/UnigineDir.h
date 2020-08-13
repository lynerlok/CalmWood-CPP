/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
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
#include "UniginePtr.h"

namespace Unigine
{


class UNIGINE_API Dir : public APIInterface
{
public:
	static Ptr<Dir> create();
	static Ptr<Dir> create(const char *name);
	static int setMTime(const char *name, long long value);
	static long long getMTime(const char *name);
	static int isAbsolute(const char *name);
	static int isFile(const char *name);
	static int isDir(const char *name);
	static int copy(const char *name, const char *new_name);
	static int mkdir(const char *name);
	int open(const char *name);
	int close();
	const char *getDirName(int num) const;
	long long getFileMTime(int num) const;
	const char *getFileName(int num) const;
	size_t getFileSize(int num) const;
	const char *getName() const;
	int getNumDirs() const;
	int getNumFiles() const;
	size_t getSize() const;
	bool isOpened() const;
};
typedef Ptr<Dir> DirPtr;

} // namespace Unigine
