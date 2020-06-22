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


#include "ComponentSystem.h"
#include <UnigineGame.h>
#include <UnigineEditor.h>
#include <UnigineEngine.h>
#include <UnigineApp.h>
#include <UnigineProperties.h>
#include <UnigineDir.h>
#include <UnigineStreams.h>
#include <UnigineProfiler.h>
#include <UnigineTimer.h>
#include <UnigineConsole.h>
#include <functional>

// need for MultiByteToWideChar() func
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#endif

#undef min

using namespace Unigine;
using namespace Math;

////////////////////////////////////////////////////////////////////////////////////////
// Component System
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GNUC__
#pragma region System
#endif

ComponentSystem::ComponentSystem()
	: initialized(0)
	, shutdowned(0)
	, profiler_time(0)
	, warning_level(WARNING_LEVEL::LOW)
{
}

ComponentSystem::~ComponentSystem()
{
	if (!initialized)
		return;

	// clear components
	for (auto i = components.begin(); i != components.end(); ++i)
		for (int k = 0; k < i->data.size(); k++)
			delete i->data[k];
	components.clear();
}

void ComponentSystem::initialize()
{
	// run callbacks before initialization
	// (usually we call ComponentSystem::get()->registerComponent<>() here)
	for (int i = 0; i < initialize_callbacks.size(); i++)
	{
		initialize_callbacks[i]->run();
		delete initialize_callbacks[i];
	}
	initialize_callbacks.clear();

	// modify property files if needed
	createPropertyFiles();

	// don't subscribe or addWorldLogic twice
	if (initialized)
		return;

	// subscribe to create nodes with properties
	Node::addCallback(Node::CALLBACK_PROPERTY_NODE_SLOTS_CHANGED, MakeCallback(this, &ComponentSystem::on_property_slots_changed));
	Node::addCallback(Node::CALLBACK_PROPERTY_NODE_ADD, MakeCallback(this, &ComponentSystem::on_property_created));
	Node::addCallback(Node::CALLBACK_PROPERTY_NODE_SWAP, MakeCallback(this, &ComponentSystem::on_property_swapped));
	Node::addCallback(Node::CALLBACK_PROPERTY_NODE_REMOVE, MakeCallback(this, &ComponentSystem::on_property_removed));
	Node::addCallback(Node::CALLBACK_PROPERTY_CHANGE_ENABLED, MakeCallback(this, &ComponentSystem::on_property_change_enabled));
	Node::addCallback(Node::CALLBACK_NODE_CHANGE_ENABLED, MakeCallback(this, &ComponentSystem::on_node_change_enabled));

	Engine::get()->addWorldLogic(this);

	initialized = 1;
}

void ComponentSystem::addInitCallback(Unigine::CallbackBase *callback)
{
	initialize_callbacks.append(callback);
}

void ComponentSystem::createPropertyFiles()
{
	// create instances
	NodePtr null_node;
	Vector<String> names;
	Vector<ComponentBase *> c;
	component_factory.getComponentNames(names);
	for (int i = 0; i < names.size(); i++)
		c.append(component_factory.create(names[i], null_node, 0));

	for (int i = 0; i < c.size(); i++)
		if (c[i]->isAutoSaveProperty())
			c[i]->save_property(names[i].get());

	// delete instances
	for (int i = 0; i < c.size(); i++)
		delete c[i];
}

void ComponentSystem::createPropertyFile(const char *name)
{
	// create instance
	ComponentBase *c = component_factory.create(name, NodePtr(), 0);

	// make file and directory
	c->save_property(name);

	// delete instance
	delete c;
}

void ComponentSystem::refreshProperty(const char *name)
{
	// rewrite property file
	PropertyPtr prop = Properties::findManualProperty(name);
	if (prop)
	{
		ComponentBase *c = component_factory.create(name, NodePtr(), 0);
		c->save_property(name);
		delete c;
	}

	// reload property
	prop->reload();
}

int ComponentSystem::getNumComponents()
{
	int count = 0;
	for (auto i = components.begin(); i != components.end(); ++i)
		for (int k = 0; k < i->data.size(); k++)
			if (i->data[k])
				count++;

	return count;
}

#define CHECK_INVOKE_DISABLED if (invoke_disabled) component->invoke_disabled_all_init_methods = true;
#define CHECK_INVOKE_DISABLED_Init CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_UpdateAsyncThread CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_UpdateSyncThread CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_Update CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_PostUpdate CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_UpdatePhysics CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_Swap CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_Shutdown CHECK_INVOKE_DISABLED
#define CHECK_INVOKE_DISABLED_DestroyRenderResources CHECK_INVOKE_DISABLED


#define METHOD_REGISTRATOR(METHOD, METHOD_LOWCASE)                                                                                                                              \
	void ComponentSystem::addComponentMethod##METHOD(ComponentBase *component, CallbackBase *func, const char *name, const char *func_name, int order, bool invoke_disabled)    \
	{                                                                                                                                                                           \
		CHECK_INVOKE_DISABLED_##METHOD;                                                                                                                                                \
		/* check on existence */                                                                                                                                                \
		for (int i = 0; i < component_functions_##METHOD_LOWCASE[order].size(); i++)                                                                                            \
		{                                                                                                                                                                       \
			auto &it = component_functions_##METHOD_LOWCASE[order][i];                                                                                                          \
			if (it.component == component && !strcmp(it.func_name, func_name))                                                                                                  \
			{                                                                                                                                                                   \
				/* this method overrides existed one */                                                                                                                         \
				for (int k = 0; k < component->functions_##METHOD_LOWCASE[order].size(); k++)                                                                                   \
					if (component->functions_##METHOD_LOWCASE[order][k] == it.function)                                                                                         \
					{                                                                                                                                                           \
						component->functions_##METHOD_LOWCASE[order][k] = func;                                                                                                 \
						break;                                                                                                                                                  \
					}                                                                                                                                                           \
                                                                                                                                                                                \
				it.function = func;                                                                                                                                             \
				it.name = name;                                                                                                                                                 \
				it.invoke_disabled = invoke_disabled;                                                                                                                           \
				return;                                                                                                                                                         \
			}                                                                                                                                                                   \
		}                                                                                                                                                                       \
                                                                                                                                                                                \
		/* its a new method */                                                                                                                                                  \
		component_functions_##METHOD_LOWCASE[order].append({component, func, name, func_name, false, invoke_disabled});                                                                   \
                                                                                                                                                                                \
		/* used in shutdown() before destroy a node */                                                                                                                          \
		component->functions_##METHOD_LOWCASE[order].append(func);                                                                                                              \
	}                                                                                                                                                                           \
	void ComponentSystem::removeComponentMethod##METHOD(ComponentBase *component, CallbackBase *func, const char *name, const char *func_name, int order, bool invoke_disabled) \
	{                                                                                                                                                                           \
		auto &vector = component_functions_##METHOD_LOWCASE[order];                                                                                                             \
		auto it = vector.find<ComponentCallback>({component, func, name, func_name, false, invoke_disabled});                                                                             \
		if (it != vector.end())                                                                                                                                                 \
		{                                                                                                                                                                       \
			vector.remove(it);                                                                                                                                                  \
			if (!vector.size())                                                                                                                                                 \
				component_functions_##METHOD_LOWCASE.remove(order);                                                                                                             \
		}                                                                                                                                                                       \
	}
METHOD_REGISTRATOR(Init, init);
METHOD_REGISTRATOR(UpdateAsyncThread, updateAsyncThread);
METHOD_REGISTRATOR(UpdateSyncThread, updateSyncThread);
METHOD_REGISTRATOR(Update, update);
METHOD_REGISTRATOR(PostUpdate, postUpdate);
METHOD_REGISTRATOR(UpdatePhysics, updatePhysics);
METHOD_REGISTRATOR(Swap, swap);
METHOD_REGISTRATOR(Shutdown, shutdown);
METHOD_REGISTRATOR(DestroyRenderResources, destroyRenderResources);
#undef METHOD_REGISTRATOR
#undef CHECK_INVOKE_DISABLED
#undef CHECK_INVOKE_DISABLED_Init
#undef CHECK_INVOKE_DISABLED_UpdateAsyncThread
#undef CHECK_INVOKE_DISABLED_UpdateSyncThread
#undef CHECK_INVOKE_DISABLED_Update
#undef CHECK_INVOKE_DISABLED_PostUpdate
#undef CHECK_INVOKE_DISABLED_UpdatePhysics
#undef CHECK_INVOKE_DISABLED_Swap
#undef CHECK_INVOKE_DISABLED_Shutdown
#undef CHECK_INVOKE_DISABLED_DestroyRenderResources


#define CALL_COMPONENT_FUNC(NAME, OTHER_CODE)														\
	for (auto i = component_functions_##NAME.begin(); i != component_functions_##NAME.end(); ++i)	\
		for (int k = 0; k < i->data.size(); k++)													\
		{																							\
			ComponentCallback &cc = i->data[k];														\
			OTHER_CODE																				\
		}

// check isEnabled() flag
#define GET_ENABLED_VAR() ComponentBase *c = cc.component; int is_enabled = c->isEnabled();

// call some method
#ifdef USE_MICROPROFILE
#define CALL_FUNC(PROFILER) int pid = PROFILER::beginMicro(cc.name); cc.function->run(); PROFILER::endMicro(pid);
#else
#define CALL_FUNC(PROFILER) cc.function->run();
#endif

// call some method (only if it's enabled and already initialized)
#define CALL_FUNC_IF_ENABLED()                                    \
	if ((is_enabled || cc.invoke_disabled) && c->all_init_called) \
	{                                                             \
		CALL_FUNC(Profiler)                                       \
	}

// call some method (only if it's already initialized)
#define CALL_FUNC_IF_ALL_INIT_CALLED() \
	if (cc.component->all_init_called) \
	{                                  \
		CALL_FUNC(Profiler)            \
	}

int ComponentSystem::init()
{
	shutdowned = 0;

	// call init() method (for components that created at design time)
	run_init_methods();

	destroy_nodes();
	return 1;
}

void ComponentSystem::updateAsyncThread(int id, int size)
{
	run_thread_methods(component_functions_updateAsyncThread, id, size);
}

void ComponentSystem::updateSyncThread(int id, int size)
{
	run_thread_methods(component_functions_updateSyncThread, id, size);
}

int ComponentSystem::update()
{
#ifdef USE_MICROPROFILE
	int puid = Profiler::beginMicro(__FUNCTION__);
#endif
	long long update_time = Timer::getTime();

	// run queued callbacks from another threads
	{
		ScopedLock atomic(callbacks_lock);
		for (int i = 0; i < queued_callbacks.size(); i++)
		{
			QueuedCallback &c = queued_callbacks[i];

			// skip deleted nodes
			if (!Node::isNode(c.node))
				continue;

			NodePtr n = Node::getNode(c.node);
			switch (c.type)
			{
				case QueuedCallback::SLOTS_CHANGED:
					on_property_slots_changed(n, c.num);
					break;
				case QueuedCallback::CREATED:
					on_property_created(n, Properties::findPropertyByGUID(c.prop), c.num);
					break;
				case QueuedCallback::SWAPPED:
					on_property_swapped(n, c.from_num, c.num);
					break;
				case QueuedCallback::REMOVED:
					on_property_removed(n, Properties::findPropertyByGUID(c.prop), c.num);
					break;
				case QueuedCallback::CHANGE_ENABLED:
					on_property_change_enabled(n, Properties::findPropertyByGUID(c.prop), c.num);
					break;
				case QueuedCallback::NODE_CHANGE_ENABLED:
					on_node_change_enabled(n);
					break;
			}
		}
		queued_callbacks.clear();
	}

	// call init() method (for components that created at run time)
	run_init_methods();

	// call update() method
	CALL_COMPONENT_FUNC(update, GET_ENABLED_VAR(); CALL_FUNC_IF_ENABLED());

	// destroy all queued nodes (after call destroyNode())
	destroy_nodes();

	profiler_time += Timer::getTime() - update_time;
#ifdef USE_MICROPROFILE
	Profiler::endMicro(puid);
#endif
	return 1;
}

int ComponentSystem::postUpdate()
{
#ifdef USE_MICROPROFILE
	int prid = Profiler::beginMicro(__FUNCTION__);
#endif
	long long post_update_time = Timer::getTime();

	// post update
	CALL_COMPONENT_FUNC(postUpdate, GET_ENABLED_VAR(); CALL_FUNC_IF_ENABLED());
	destroy_nodes();

	profiler_time += Timer::getTime() - post_update_time;
	render_profiler();

#ifdef USE_MICROPROFILE
	Profiler::endMicro(prid);
#endif
	return 1;
}

int ComponentSystem::updatePhysics()
{
#ifdef USE_MICROPROFILE
	int pfid = Profiler::beginMicro(__FUNCTION__);
#endif
	long long update_physics_time = Timer::getTime();

	CALL_COMPONENT_FUNC(updatePhysics, GET_ENABLED_VAR(); CALL_FUNC_IF_ENABLED());

	profiler_time += Timer::getTime() - update_physics_time;
#ifdef USE_MICROPROFILE
	Profiler::endMicro(pfid);
#endif
	return 1;
}

int ComponentSystem::swap()
{
#ifdef USE_MICROPROFILE
	int psid = Profiler::beginMicro(__FUNCTION__);
#endif
	long long update_swap_time = Timer::getTime();

	CALL_COMPONENT_FUNC(swap, GET_ENABLED_VAR(); CALL_FUNC_IF_ENABLED());

	profiler_time += Timer::getTime() - update_swap_time;
#ifdef USE_MICROPROFILE
	Profiler::endMicro(psid);
#endif
	return 1;
}

int ComponentSystem::shutdown()
{
	shutdowned = 1;
	CALL_COMPONENT_FUNC(shutdown, CALL_FUNC_IF_ALL_INIT_CALLED());

	// destroy all components and their methods
	for (auto i = components.begin(); i != components.end(); ++i)
		for (int k = 0; k < i->data.size(); k++)
			delete i->data[k];
	components.clear();
	component_functions_init.clear();
	component_functions_updateAsyncThread.clear();
	component_functions_updateSyncThread.clear();
	component_functions_update.clear();
	component_functions_postUpdate.clear();
	component_functions_updatePhysics.clear();
	component_functions_swap.clear();
	component_functions_shutdown.clear();
	component_functions_destroyRenderResources.clear();

	destroy_nodes();

	return 1;
}

int ComponentSystem::destroyRenderResources()
{
	CALL_COMPONENT_FUNC(destroyRenderResources, CALL_FUNC(Profiler));
	return 1;
}

void ComponentSystem::run_init_methods()
{
	// for "order min value" to "order max value" for "init" method
	while (component_functions_init.begin() != component_functions_init.end())
	{
		bool need_to_restart = false;
		auto it = component_functions_init.begin();

		// for components on a specific order
		for (int k = 0; k < it->data.size(); k++)
		{
			ComponentCallback &cc = it->data[k];
			ComponentBase *c = cc.component;

			if (!c->isEnabled() && !(c->invoke_disabled_all_init_methods || cc.invoke_disabled))
			{
				component_functions_init_delayed[it->key/*order*/].append(cc/*method*/);
				continue;
			}

			// initialize component (before call init() method)
			// show errors, do some things with node...
			if (!c->initialized)
			{
				c->null_check();
				c->initialize();
			}

			// run init() method
			if (!cc.called)
			{
				cc.called = true;
				c->init_called();

				// warning: after call run() function below don't do anything with
				// the "cc" variable! Vector it->data might be reallocated (moved).
				// it can happens when component creates another component in
				// its init() function

#ifdef USE_MICROPROFILE
				int pid = Profiler::beginMicro(cc.name);
				cc.function->run();
				Profiler::endMicro(pid);
#else
				// NOTE: It can reallocate component_functions_init, when inside init() new component is created
				cc.function->run();
#endif

				if (it != component_functions_init.begin())
				{
					// the component has created other components with a lower order of methods than
					// the current one. Need to restart this method (run_init_methods) to be sure
					// that all methods are called in the current frame
					need_to_restart = true;
					break;
				}
			}
		}

		if (!need_to_restart)
			component_functions_init.remove(it->key);
	}

	// add functions that haven't been executed to the queue
	component_functions_init.swap(component_functions_init_delayed);
	component_functions_init_delayed.clear();
}

void ComponentSystem::run_thread_methods(const Unigine::Map<int, Unigine::Vector<ComponentCallback>> &functions, int id, int size)
{
	for (auto i = functions.begin(); i != functions.end(); ++i)
	{
		int count = i->data.size();

		int step = Math::udiv(count, size);
		int from_k = step * id;
		int to_k = Math::min(from_k + step, count);

		for (int k = from_k; k < to_k; k++)
		{
			const ComponentCallback &cc = i->data[k];
			ComponentBase *c = cc.component;
			int is_enabled = c->isEnabled();
			if ((is_enabled || cc.invoke_disabled) && c->all_init_called)
			{
				cc.function->run();
			}
		}
	}
}

void ComponentSystem::on_property_slots_changed(const Unigine::NodePtr node, int num_slots)
{
	if (!node)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::SLOTS_CHANGED;
		callback.node = node->getID();
		callback.num = num_slots;
		return;
	}

	const int node_id = node->getID();
	auto &list = components[node_id];
	if (list.size() > num_slots)
	{
		// remove extra components
		for (int i = list.size() - 1; i >= num_slots; --i)
			if (list[i])
				on_property_removed(node, PropertyPtr(), i);
	}

	if (num_slots == 0)
	{
		// destroy key in map (node id)
		components.remove(node_id);
	} else
	{
		// add new empty slots
		int prev_size = list.size();
		list.resize(num_slots);
		for (int i = prev_size; i < num_slots; i++)
			list[i] = nullptr;
	}
}

void ComponentSystem::on_property_created(const NodePtr node, const PropertyPtr prop, int num)
{
	if (!node || !prop)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::CREATED;
		callback.node = node->getID();
		callback.prop = prop->getGUID();
		callback.num = num;
		return;
	}

	// remove duplicates
	auto it = components.find(node->getID());
	if (it != components.end() && it->data.size() > num &&
		it->data[num] && it->data[num]->property == prop)
	{
		on_property_removed(node, prop, num);
	}

	// create component for created property
	ComponentBase *c = nullptr;
	PropertyPtr p = prop;
	while (!c && p)
	{
		c = component_factory.create(p->getName(), node, num);
		p = p->getParent();
	}
	if (c)
		c->node_id = node->getID();

	// put the new component in Vector<ComponentBase*>
	// in the same index as the "num" variable
	auto &list = components[node->getID()];

	// set
	list[num] = c;

	// check the count of init() methods
	// if there are 0 methods then use auto initialization
	if (c)
	{
		int count = 0;
		for (auto i = c->functions_init.begin(); i != c->functions_init.end(); ++i)
			count += i->data.size();
		if (count == 0)
		{
			c->null_check();
			c->initialize();
			c->init_called();
		}

		c->on_ready();
	}
}

void ComponentSystem::on_property_swapped(const NodePtr node, int from_num, int to_num)
{
	if (!node)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::SWAPPED;
		callback.node = node->getID();
		callback.from_num = from_num;
		callback.num = to_num;
		return;
	}

	auto it = components.find(node->getID());
	if (it == components.end())
		return;

	// swap components
	ComponentBase *tmp = it->data[from_num];
	it->data[from_num] = it->data[to_num];
	it->data[to_num] = tmp;

	if (it->data[from_num]) it->data[from_num]->property_num = from_num;
	if (it->data[to_num]) it->data[to_num]->property_num = to_num;
}

void ComponentSystem::on_property_removed(const NodePtr node, const PropertyPtr prop, int num)
{
	if (!node || !prop)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::REMOVED;
		callback.node = node->getID();
		callback.prop = prop->getGUID();
		callback.num = num;
		return;
	}

	auto it = components.find(node->getID());
	if (it == components.end())
		return;

	// call shutdown()
	if (it->data[num] && !it->data[num]->shutdown_called && it->data[num]->initialized && it->data[num]->all_init_called)
	{
		if (!shutdowned)
		{
			// call all shutdown() methods in order
			for (auto its = it->data[num]->functions_shutdown.begin(); its != it->data[num]->functions_shutdown.end(); ++its)
				for (int ks = 0; ks < its->data.size(); ks++)
					its->data[ks]->run();
		}

		it->data[num]->node = NodePtr();
		it->data[num]->shutdown_called = 1;
	}

	// destroy component
	delete it->data[num];
	it->data[num] = nullptr;
}

void ComponentSystem::on_node_change_enabled(const Unigine::NodePtr node)
{
	if (!node)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::NODE_CHANGE_ENABLED;
		callback.node = node->getID();
		return;
	}

	auto it = components.find(node->getID());
	if (it == components.end())
		return;

	for (auto c : it->data)
		if (c)
			c->refresh_enabled();
}

void ComponentSystem::on_property_change_enabled(const Unigine::NodePtr node, const Unigine::PropertyPtr prop, int num)
{
	if (!node || !prop)
		return;

	// callbacks processes in the Main Thread only
	if (!Engine::get()->isMainThread())
	{
		ScopedLock atomic(callbacks_lock);
		QueuedCallback &callback = queued_callbacks.append();
		callback.type = QueuedCallback::CHANGE_ENABLED;
		callback.node = node->getID();
		callback.prop = prop->getGUID();
		callback.num = num;
		return;
	}

	auto it = components.find(node->getID());
	if (it == components.end())
		return;

	auto comp = it->data[num];
	if (!comp)
		return;
	comp->enabled_self = node->isPropertyEnabled(num);
	comp->refresh_enabled();
}

void ComponentSystem::destroy_nodes()
{
	if (!destroy_node_queue.size())
		return;

	for (int i = 0; i < destroy_node_queue.size(); i++)
	{
		if (!destroy_node_queue[i])
			continue;

		destroy_node_with_children(destroy_node_queue[i]);
	}
	destroy_node_queue.clear();
}

void ComponentSystem::destroy_node_with_children(NodePtr &node)
{
	// destroy children first
	while (node->getNumChildren())
	{
		NodePtr child = node->getChild(0);
		destroy_node_with_children(child);
	}

	// call shutdown() to all components and release pointer
	VectorStack<ComponentBase*> all_components;
	getComponents<ComponentBase>(node, all_components);
	for (int i = 0; i < all_components.size(); i++)
	{
		// if the component was shutdowned already
		if (all_components[i]->shutdown_called || !all_components[i]->initialized || !all_components[i]->all_init_called)
			continue;

		// if the world is not unloaded yet
		if (!shutdowned)
		{
			// call shutdown() methods in order
			for (auto its = all_components[i]->functions_shutdown.begin(); its != all_components[i]->functions_shutdown.end(); ++its)
				for (int ks = 0; ks < its->data.size(); ks++)
					its->data[ks]->run();
		}

		all_components[i]->node = NodePtr();
		all_components[i]->shutdown_called = 1;
	}

	// destroy node
	node.deleteLater();
}

void ComponentSystem::render_profiler()
{
	if (Profiler::isEnabled())
	{
		float time_ms = (float)(profiler_time) / (Timer::CLOCKS_PER_SECOND / 1000);
		Profiler::setValue("Components: ", "ms", time_ms, 50.0f, vec4(1, 1, 1, 1));
	}
	profiler_time = 0;
}

#ifndef __GNUC__
#pragma endregion System
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Component Variables
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GNUC__
#pragma region Variables
#endif

ComponentVariable::ComponentVariable(PropertyWrapper* component, const char *in_name, int in_type,
	const char *in_title, const char *in_tooltip, const char *in_group)
{
	holder = component;

	name = in_name;
	title = in_title;
	tooltip = in_tooltip;
	group = in_group;
	type = in_type;

	if (!name.empty())
		setParameter(
			component->property ?
			component->property->getParameterPtr(name.get()) :
			PropertyParameterPtr());

	component->variables.append(this);
}

ComponentVariable::~ComponentVariable()
{
}

void ComponentVariable::setParameter(const PropertyParameterPtr &param)
{
	parameter = param;
}

const char *ComponentVariable::getTypeName() const
{
	switch (type)
	{
		case (Property::PARAMETER_INT): return "int";
		case (Property::PARAMETER_FLOAT): return "float";
		case (Property::PARAMETER_DOUBLE): return "double";
		case (Property::PARAMETER_TOGGLE): return "toggle";
		case (Property::PARAMETER_SWITCH): return "switch";
		case (Property::PARAMETER_STRING): return "string";
		case (Property::PARAMETER_COLOR): return "color";
		case (Property::PARAMETER_VEC2): return "vec2";
		case (Property::PARAMETER_VEC3): return "vec3";
		case (Property::PARAMETER_VEC4): return "vec4";
		case (Property::PARAMETER_DVEC2): return "dvec2";
		case (Property::PARAMETER_DVEC3): return "dvec3";
		case (Property::PARAMETER_DVEC4): return "dvec4";
		case (Property::PARAMETER_IVEC2): return "ivec2";
		case (Property::PARAMETER_IVEC3): return "ivec3";
		case (Property::PARAMETER_IVEC4): return "ivec4";
		case (Property::PARAMETER_MASK): return "mask";
		case (Property::PARAMETER_FILE): return "file";
		case (Property::PARAMETER_PROPERTY): return "property";
		case (Property::PARAMETER_MATERIAL): return "material";
		case (Property::PARAMETER_NODE): return "node";
		case (Property::PARAMETER_ARRAY): return "array";
		case (Property::PARAMETER_STRUCT): return "struct";
		default:
			return nullptr;
	}
}

int ComponentVariable::is_type_name(const char *in_name) const
{
	String value(in_name);
	value.lower();

	if (value == "int" ||
		value == "float" ||
		value == "double" ||
		value == "toggle" ||
		value == "switch" ||
		value == "string" ||
		value == "color" ||
		value == "vec2" ||
		value == "vec3" ||
		value == "vec4" ||
		value == "dvec2" ||
		value == "dvec3" ||
		value == "dvec4" ||
		value == "ivec2" ||
		value == "ivec3" ||
		value == "ivec4" ||
		value == "mask" ||
		value == "file" ||
		value == "property" ||
		value == "material" ||
		value == "node" ||
		value == "array" ||
		value == "struct")
		return 1;

	return 0;
}

void ComponentVariable::save(const XmlPtr &in_parameter)
{
	in_parameter->setArg("name", getName());
	in_parameter->setArg("type", getTypeName());
	if (!title.empty()) in_parameter->setArg("title", title.get());
	if (!tooltip.empty()) in_parameter->setArg("tooltip", tooltip.get());
	if (!group.empty()) in_parameter->setArg("group", group.get());
	in_parameter->setData(getValueAsString().get());
}

void ComponentVariableSwitch::save(const XmlPtr &in_parameter)
{
	ComponentVariable::save(in_parameter);
	if (!items.empty()) in_parameter->setArg("items", items.get());
}

void ComponentVariableMask::save(const XmlPtr &in_parameter)
{
	ComponentVariable::save(in_parameter);
	if (!flags.empty()) in_parameter->setArg("flags", flags.get());
}

void ComponentVariableStructBase::save(const XmlPtr &in_parameter)
{
	ComponentVariable::save(in_parameter);
	in_parameter->setArg("type", struct_type.get());
}

void ComponentVariableStructBase::setParameter(const PropertyParameterPtr &param)
{
	ComponentVariable::setParameter(param);

	// set parameters to all children inside this struct
	if (param)
		for (int i = 0; i < value_base->variables.size(); i++)
			value_base->variables[i]->setParameter(param->getChild(i));
}

#define DECLARE_VARIABLE_SETTER(TYPE_LOWERCASE, TYPE_UPPERCASE, TYPE_CAMELCASE1, TYPE_CAMELCASE2, VALUE)	\
ComponentVariable##TYPE_CAMELCASE1 &ComponentVariable##TYPE_CAMELCASE1::operator=(TYPE_LOWERCASE value_in)	\
{																											\
	VALUE = value_in;																						\
																											\
	if (!parameter || type != Property::PARAMETER_##TYPE_UPPERCASE)											\
		return *this;																						\
																											\
	parameter->setValue(value_in);																			\
	return *this;																							\
}

DECLARE_VARIABLE_SETTER(int, INT, Int, Int, value);
DECLARE_VARIABLE_SETTER(int, TOGGLE, Toggle, Toggle, value);
DECLARE_VARIABLE_SETTER(int, SWITCH, Switch, Switch, value);
DECLARE_VARIABLE_SETTER(int, MASK, Mask, Mask, value);
DECLARE_VARIABLE_SETTER(float, FLOAT, Float, Float, value);
DECLARE_VARIABLE_SETTER(double, DOUBLE, Double, Double, value);
DECLARE_VARIABLE_SETTER(const char *, STRING, String, String, value);
DECLARE_VARIABLE_SETTER(const vec2 &, VEC2, Vec2, Vec2, value);
DECLARE_VARIABLE_SETTER(const vec3 &, VEC3, Vec3, Vec3, value);
DECLARE_VARIABLE_SETTER(const vec4 &, VEC4, Vec4, Vec4, value);
DECLARE_VARIABLE_SETTER(const vec4 &, COLOR, Color, Color, value);
DECLARE_VARIABLE_SETTER(const dvec2 &, DVEC2, DVec2, DVec2, value);
DECLARE_VARIABLE_SETTER(const dvec3 &, DVEC3, DVec3, DVec3, value);
DECLARE_VARIABLE_SETTER(const dvec4 &, DVEC4, DVec4, DVec4, value);
DECLARE_VARIABLE_SETTER(const ivec2 &, IVEC2, IVec2, IVec2, value);
DECLARE_VARIABLE_SETTER(const ivec3 &, IVEC3, IVec3, IVec3, value);
DECLARE_VARIABLE_SETTER(const ivec4 &, IVEC4, IVec4, IVec4, value);
DECLARE_VARIABLE_SETTER(const char *, FILE, File, File, value);
DECLARE_VARIABLE_SETTER(const PropertyPtr &, PROPERTY, Property, Property, value_guid = value_in->getGUID(); value);
DECLARE_VARIABLE_SETTER(const UGUID &, PROPERTY, Property, GUID, value = PropertyPtr(); value_guid);
DECLARE_VARIABLE_SETTER(const MaterialPtr &, MATERIAL, Material, Material, value_guid = value_in->getGUID(); value);
DECLARE_VARIABLE_SETTER(const UGUID &, MATERIAL, Material, GUID, value = MaterialPtr(); value_guid);
DECLARE_VARIABLE_SETTER(const NodePtr &, NODE, Node, Node, value_id = value_in->getID(); value);
DECLARE_VARIABLE_SETTER(int, NODE, Node, NodeID, value = NodePtr(); value_id);

#define DECLARE_VARIABLE_GETTER(TYPE_LOWERCASE, TYPE_UPPERCASE, TYPE_CAMELCASE1, TYPE_CAMELCASE2, VALUE)	\
ComponentVariable##TYPE_CAMELCASE1::operator TYPE_LOWERCASE() const											\
{																											\
	if (!parameter || type != Property::PARAMETER_##TYPE_UPPERCASE)											\
		return VALUE;																						\
																											\
	return parameter->getValue##TYPE_CAMELCASE2();															\
}

ComponentVariableString::operator const char *() const
{
	if (!parameter || type != Property::PARAMETER_STRING)
		return value;
	value = parameter->getValueString();
	return value.get();
}

DECLARE_VARIABLE_GETTER(int, INT, Int, Int, value);
DECLARE_VARIABLE_GETTER(int, TOGGLE, Toggle, Toggle, value);
DECLARE_VARIABLE_GETTER(int, SWITCH, Switch, Switch, value);
DECLARE_VARIABLE_GETTER(int, MASK, Mask, Mask, value);
DECLARE_VARIABLE_GETTER(float, FLOAT, Float, Float, value);
DECLARE_VARIABLE_GETTER(double, DOUBLE, Double, Double, value);
DECLARE_VARIABLE_GETTER(vec2, VEC2, Vec2, Vec2, value);
DECLARE_VARIABLE_GETTER(vec3, VEC3, Vec3, Vec3, value);
DECLARE_VARIABLE_GETTER(vec4, VEC4, Vec4, Vec4, value);
DECLARE_VARIABLE_GETTER(vec4, COLOR, Color, Color, value);
DECLARE_VARIABLE_GETTER(dvec2, DVEC2, DVec2, DVec2, value);
DECLARE_VARIABLE_GETTER(dvec3, DVEC3, DVec3, DVec3, value);
DECLARE_VARIABLE_GETTER(dvec4, DVEC4, DVec4, DVec4, value);
DECLARE_VARIABLE_GETTER(ivec2, IVEC2, IVec2, IVec2, value);
DECLARE_VARIABLE_GETTER(ivec3, IVEC3, IVec3, IVec3, value);
DECLARE_VARIABLE_GETTER(ivec4, IVEC4, IVec4, IVec4, value);
DECLARE_VARIABLE_GETTER(const char *, FILE, File, File, value);
DECLARE_VARIABLE_GETTER(PropertyPtr, PROPERTY, Property, Property, value);
DECLARE_VARIABLE_GETTER(UGUID, PROPERTY, Property, GUID, value_guid);
DECLARE_VARIABLE_GETTER(MaterialPtr, MATERIAL, Material, Material, value);
DECLARE_VARIABLE_GETTER(UGUID, MATERIAL, Material, GUID, value_guid);
DECLARE_VARIABLE_GETTER(NodePtr, NODE, Node, Node, value);
DECLARE_VARIABLE_GETTER(int, NODE, Node, NodeID, value_id);

#define DECLARE_VARIABLE_GETTER2(TYPE, TYPE_UPPERCASE, TYPE_CAMELCASE)					\
TYPE ComponentVariable##TYPE_CAMELCASE::get() const										\
{																						\
	if (!parameter || type != Property::PARAMETER_##TYPE_UPPERCASE)						\
		return value;																	\
																						\
	return parameter->getValue##TYPE_CAMELCASE();										\
}

const char *ComponentVariableString::get() const
{
	if (!parameter || type != Property::PARAMETER_STRING)
		return value;

	value = parameter->getValueString();
	return value.get();
}

const char *ComponentVariableFile::getRaw() const
{
	if (!parameter || type != Property::PARAMETER_FILE)
		return value;
	value = parameter->getValueString();
	return value.get();
}

DECLARE_VARIABLE_GETTER2(int, INT, Int);
DECLARE_VARIABLE_GETTER2(int, TOGGLE, Toggle);
DECLARE_VARIABLE_GETTER2(int, SWITCH, Switch);
DECLARE_VARIABLE_GETTER2(int, MASK, Mask);
DECLARE_VARIABLE_GETTER2(float, FLOAT, Float);
DECLARE_VARIABLE_GETTER2(double, DOUBLE, Double);
DECLARE_VARIABLE_GETTER2(vec2, VEC2, Vec2);
DECLARE_VARIABLE_GETTER2(vec3, VEC3, Vec3);
DECLARE_VARIABLE_GETTER2(vec4, VEC4, Vec4);
DECLARE_VARIABLE_GETTER2(vec4, COLOR, Color);
DECLARE_VARIABLE_GETTER2(dvec2, DVEC2, DVec2);
DECLARE_VARIABLE_GETTER2(dvec3, DVEC3, DVec3);
DECLARE_VARIABLE_GETTER2(dvec4, DVEC4, DVec4);
DECLARE_VARIABLE_GETTER2(ivec2, IVEC2, IVec2);
DECLARE_VARIABLE_GETTER2(ivec3, IVEC3, IVec3);
DECLARE_VARIABLE_GETTER2(ivec4, IVEC4, IVec4);
DECLARE_VARIABLE_GETTER2(const char *, FILE, File);
DECLARE_VARIABLE_GETTER2(PropertyPtr, PROPERTY, Property);
DECLARE_VARIABLE_GETTER2(MaterialPtr, MATERIAL, Material);
DECLARE_VARIABLE_GETTER2(NodePtr, NODE, Node);

#define DECLARE_VARIABLE_POINTER(TYPE, TYPE_UPPERCASE)									\
TYPE *ComponentVariable##TYPE::operator->()												\
{																						\
	if (!parameter || type != Property::PARAMETER_##TYPE_UPPERCASE)						\
		return value.get();																\
																						\
	TYPE##Ptr param_value = parameter->getValue##TYPE();								\
	if (value != param_value)															\
		value = param_value;															\
																						\
	return value.get();																	\
}

DECLARE_VARIABLE_POINTER(Property, PROPERTY);
DECLARE_VARIABLE_POINTER(Material, MATERIAL);
DECLARE_VARIABLE_POINTER(Node, NODE);

#ifndef __GNUC__
#pragma endregion Variables
#endif

////////////////////////////////////////////////////////////////////////////////////////
// Component Bases
////////////////////////////////////////////////////////////////////////////////////////

#ifndef __GNUC__
#pragma region Base
#endif

PropertyWrapper::PropertyWrapper(const PropertyPtr &prop)
	: property(prop)
{
}

int PropertyWrapper::findStructIndex(const char *name)
{
	for (int i = 0; i < structs.size(); i++)
		if (structs[i].name == name)
			return i;

	return -1;
}

ComponentBase::ComponentBase(const NodePtr &node, int num)
	: PropertyWrapper(node ? node->getProperty(num) : PropertyPtr())
	, node(node)
	, property_num(num)
	, node_id(node ? node->getID() : 0)
	, initialized(0)
	, init_calls_count(0)
	, all_init_called(0)
	, shutdown_called(0)
	, destroy_callback(nullptr)
	, enabled_self(node ? node->isPropertyEnabled(num) : 0)
{
	refresh_enabled();
}

ComponentBase::~ComponentBase()
{
	if (destroy_callback)
		destroy_callback->run();
	delete destroy_callback;
}

int ComponentBase::is_equals(const XmlPtr &xml1, const XmlPtr &xml2)
{
	if (xml1->getNumChildren() != xml2->getNumChildren())
		return 0;

	if (xml1->getNumArgs() != xml2->getNumArgs())
		return 0;

	if (strcmp(xml1->getData(), xml2->getData()))
		return 0;

	for (int i = 0; i < xml1->getNumArgs(); i++)
		if (strcmp(xml1->getArgName(i), xml2->getArgName(i)) ||
			strcmp(xml1->getArgValue(i), xml2->getArgValue(i)))
			return 0;

	for (int i = 0; i < xml1->getNumChildren(); i++)
		if (!is_equals(xml1->getChild(i), xml2->getChild(i)))
			return 0;

	return 1;
}

void ComponentBase::save_property(const char *name)
{
	auto mkdir = [](const char *name)
	{
#ifdef _WIN32
		wchar_t wbuf[1024];
		MultiByteToWideChar(CP_UTF8, 0, name, -1, wbuf, (int)(sizeof(wbuf) / sizeof(wchar_t)));
		wbuf[sizeof(wbuf) / sizeof(wchar_t) - 1] = '\0';
		for (wchar_t *d = wbuf; *d != '\0'; d++)
		{
			if (*d == '/')
				*d = '\\';
			if (*d == '\\' && *(d + 1) == '\0')
				*d = '\0';
		}

		return (_wmkdir(wbuf) == 0);
#else
		return (::mkdir(name, 0755) == 0);
#endif
	};

	StringArray<> engine_version = String::split(Console::getString("engine_version_info"), " ");

	// check parent property (create if it doesn't exist)
	StringStack<> parent_prop_name = getParentPropertyName();
	if (parent_prop_name != "node_base" &&
		!Properties::findManualProperty(parent_prop_name))
	{
		mkdir(String::format("%s/ComponentSystem", Engine::get()->getDataPath()).get());
		XmlPtr parent_xml = Xml::create("property");
		parent_xml->setArg("version", engine_version[0]);
		parent_xml->setArg("name", parent_prop_name);
		parent_xml->setArg("manual", "1");
		parent_xml->setArg("parent_name", "node_base");

		StringStack<> parent_prop_path = String::format("ComponentSystem/%s.prop", parent_prop_name.get());
		parent_xml->save(parent_prop_path);
		Properties::loadProperty(parent_prop_path);
		Log::message("ComponentSystem: property \"%s\" was created (%s)\n", parent_prop_name.get(), parent_prop_path.get());
	}

	// check current property (create if it doesn't exist)
	StringStack<> file_name;
	auto prop = Properties::findManualProperty(name);
	if (prop)
		file_name = prop->getPath();
	else
	{
		mkdir(String::format("%s/ComponentSystem", Engine::get()->getDataPath()).get());
		file_name = String::format("ComponentSystem/%s.prop", name).get();
	}

	// create property xml
	XmlPtr xml = Xml::create("property");
	xml->setArg("version", engine_version[0]);
	xml->setArg("name", name);
	xml->setArg("manual", "1");
	xml->setArg("parent_name", parent_prop_name);

	// save structs
	Vector<String> saved_structs;
	std::function<void(PropertyWrapper *)> save_structs = [&, this](PropertyWrapper *c)
	{
		// go deeper
		for (int i = 0; i < c->structs.size(); i++)
			if (c->structs[i].variable && 
				c->structs[i].variable->getType() == Property::PARAMETER_STRUCT)
			{
				ComponentVariableStructBase *cvs = dynamic_cast<ComponentVariableStructBase*>(c->structs[i].variable);
				save_structs(cvs->getBase());
			}

		// save structs from far to near
		for (int i = 0; i < c->structs.size(); i++)
		{
			String &name = c->structs[i].name;

			// add new struct and save it to xml
			if (saved_structs.findIndex(name) == -1)
			{
				XmlPtr x = xml->addChild("struct");
				x->setArg("name", name.get());
				ComponentStruct *data = c->structs[i].instance;
				for (int k = 0; k < data->variables.size(); k++)
					if (data->variables[k]->getName()[0] != '\0')
						data->variables[k]->save(x->addChild("parameter"));
				saved_structs.append(name);
			}
		}
	};
	save_structs(this);

	// save parameters
	for (int i = 0; i < variables.size(); i++)
		if (variables[i]->getName()[0] != '\0')
			variables[i]->save(xml->addChild("parameter"));

	// check for changes with previous property
	int need_to_save = 1;
	if (prop)
	{
		XmlPtr xml_prev = Xml::create();
		if (xml_prev->load(file_name.get()) && is_equals(xml_prev, xml))
			need_to_save = 0;
	}

	// save to file
	if (need_to_save)
	{
		xml->save(file_name.get());
		Properties::loadProperty(file_name.get());
		Log::message("ComponentSystem: property \"%s\" was %s (%s)\n", name, (prop ? "modified" : "created"), file_name.get());
	}
}

void ComponentBase::destroyNode(const NodePtr &in_node)
{
	ComponentSystem::get()->destroyNode(in_node);
}

void ComponentBase::null_check()
{
	if (ComponentSystem::get()->getWarningLevel() < ComponentSystem::WARNING_LEVEL::HIGH)
		return;

	for (int i = 0; i < variables.size(); i++)
		if (variables[i]->nullCheck())
			Log::warning("ComponentBase::null_check(): parameter \"%s\" of the property \"%s\" is null\n",
				variables[i]->getName(), property->getName());
}

void ComponentBase::initialize()
{
	// release ownership
	// (destroy of this component shouldn't destroy the node)
	initialized = 1;
}

void ComponentBase::init_called()
{
	init_calls_count++;

	int count = 0;
	for (auto i = functions_init.begin(); i != functions_init.end(); ++i)
		count += i->data.size();

	if (init_calls_count >= count)
		all_init_called = 1;
}

void ComponentBase::refresh_enabled()
{
	int component_enabled = node && node->isEnabled() && enabled_self;
	if (component_enabled == enabled)
		return;

	enabled = component_enabled;

	if (isInitialized())
	{
		if (enabled)
			on_enable();
		else
			on_disable();
	}
}

#ifndef __GNUC__
#pragma endregion Base
#endif
