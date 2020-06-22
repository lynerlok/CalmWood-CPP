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


#ifndef __UNIGINE_INTERFACE_H__
#define __UNIGINE_INTERFACE_H__

#include <UnigineGui.h>
#include <UnigineWidgets.h>
#include <UnigineEngine.h>

namespace Unigine
{
namespace Plugins
{
class Interface;
class InterfaceWindow;

class Interface
{
public:
	virtual ~Interface() {}

	UNIGINE_INLINE static Interface *get() { return Unigine::Engine::get()->getPlugin<Interface>("Interface"); }

	// display size
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	// mouse coordinates
	virtual void setMouse(int x, int y) = 0;
	virtual int getMouseX() const = 0;
	virtual int getMouseY() const = 0;

	// window position
	virtual int getPositionX() const = 0;
	virtual int getPositionY() const = 0;

	// windows
	virtual int getNumWindows() const = 0;
	virtual InterfaceWindow *getWindow(int num) const = 0;
	virtual int findWindow(const Unigine::GuiPtr &gui) const = 0;

	// display screens
	virtual int getNumScreens() const = 0;
	virtual int getScreenWidth(int num) const = 0;
	virtual int getScreenHeight(int num) const = 0;
	virtual int getScreenPositionX(int num) const = 0;
	virtual int getScreenPositionY(int num) const = 0;

	// center window position
	virtual int getCenterPositionX(int width) const = 0;
	virtual int getCenterPositionY(int height) const = 0;

	// visible window position
	virtual int getVisiblePositionX(int x, int width, int border = INTERFACE_BORDER) const = 0;
	virtual int getVisiblePositionY(int y, int height, int border = INTERFACE_BORDER) const = 0;

	// InterfaceWindow management
	virtual InterfaceWindow *createWindow(int flags, const char *name) const = 0;
	virtual void releaseWindow(InterfaceWindow *window) const = 0;

	enum
	{
		INTERFACE_BORDER = 32, // default border
	};
};

class InterfaceWindow
{
public:
	virtual ~InterfaceWindow() {}

	// Gui pointer
	virtual const Unigine::GuiPtr &getGui() const = 0;

	// Interface Widget
	virtual void setWidget(const Unigine::WidgetPtr &widget) = 0;
	virtual const Unigine::WidgetPtr &getWidget() const = 0;

	// moveable flag
	virtual void setMoveable(bool moveable) = 0;
	virtual bool isMoveable() const = 0;

	// parent flag
	virtual void setParent(bool parent) = 0;
	virtual bool isParent() const = 0;

	// hidden flag
	virtual void setHidden(bool hidden) = 0;
	virtual bool isHidden() const = 0;

	// focus
	virtual void setFocus() = 0;
	virtual bool isFocused() const = 0;
	virtual void setPermanentFocus() = 0;
	virtual bool isPermanentlyFocused() const = 0;
	virtual void removeFocus() = 0;

	// title
	virtual void setTitle(const char *title) = 0;
	virtual const char *getTitle() const = 0;

	// position
	virtual void setCenterPosition() = 0;
	virtual void setPosition(int x, int y) = 0;
	virtual int getPositionX() const = 0;
	virtual int getPositionY() const = 0;

	// current size
	virtual void setWidth(int width) = 0;
	virtual void setHeight(int height) = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;

	// mouse coordinates
	virtual void setMouse(int x, int y) = 0;
	virtual int getMouseX() const = 0;
	virtual int getMouseY() const = 0;

	// drop files
	virtual void clearDropFiles() = 0;
	virtual int getNumDropFiles() const = 0;
	virtual const char *getDropFileName(int num) const = 0;

	enum
	{
		TITLE = 1 << 0,	// has a title
		FRAME = 1 << 1,	// has a frame
		MINIMIZE = 1 << 2, // has a minimize button
		MAXIMIZE = 1 << 3, // has a maximize button
		CLOSE = 1 << 4,	// has a close button
		DROP = 1 << 5,	 // drop window
	};
};
} // namespace Plugins
} // namespace Unigine
#endif /* __UNIGINE_INTERFACE_H__ */
