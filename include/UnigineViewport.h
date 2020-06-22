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

#include "UnigineNode.h"
#include "UnigineCamera.h"
#include "UnigineImage.h"
#include "UnigineTextures.h"
#include "UnigineCallback.h"
#include "UnigineMesh.h"
#include "UnigineRender.h"

namespace Unigine
{


class UNIGINE_API Viewport : public APIInterface
{
public:
	static Ptr<Viewport> create();

	enum
	{
		SKIP_SHADOWS = 1 << 0,
		SKIP_VISUALIZER = 1 << 1,
		SKIP_POSTEFFECTS = 1 << 2,
		SKIP_DYNAMIC_REFLECTIONS = 1 << 3,
		SKIP_VELOCITY_BUFFER = 1 << 4,
		SKIP_SRGB = 1 << 5,
		SKIP_FORMAT_RG11B10 = 1 << 6,
		SKIP_TRANSPARENT = 1 << 7,
		SKIP_STREAMING = 1 << 8,
	};

	enum
	{
		MODE_DEFAULT,
		MODE_STEREO_ANAGLYPH,
		MODE_STEREO_INTERLACED,
		MODE_STEREO_HORIZONTAL,
		MODE_STEREO_VERTICAL,
		MODE_STEREO_SEPARATE,
		MODE_STEREO_REPLICATE,
		MODE_PANORAMA_180_CURVED,
		MODE_PANORAMA_180_LINEAR,
		MODE_PANORAMA_180_FISHEYE,
		MODE_PANORAMA_360_CURVED,
		MODE_PANORAMA_360_LINEAR,
		MODE_PANORAMA_360_FISHEYE,
	};

	enum
	{
		RENDER_DEPTH,
		RENDER_DEPTH_GBUFFER,
		RENDER_DEPTH_GBUFFER_FINAL,
		RENDER_REPROJECTION,
	};

	enum
	{
		USAGE_WORLD_LIGHT = 0,
		USAGE_AUX_LIGHT = 1,
		USAGE_NODE_LIGHT = 2,
	};
	int getID();
	void setAspectCorrection(int correction);
	int getAspectCorrection() const;
	void setFirstFrame(int frame);
	int getFirstFrame() const;
	void setSkipFlags(int flags);
	int getSkipFlags() const;
	int checkSkipFlags(int flags);
	void appendSkipFlags(int flags);
	void removeSkipFlags(int flags);
	void setMode(int mode);
	int getMode() const;
	void setRenderMode(int mode);
	int getRenderMode() const;
	bool isStereo() const;
	bool isPanorama180() const;
	bool isPanorama360() const;
	void setStereoDistance(float distance);
	float getStereoDistance() const;
	void setStereoRadius(float radius);
	float getStereoRadius() const;
	void setStereoOffset(float offset);
	float getStereoOffset() const;
	void renderEngine(const Ptr<Camera> &camera);
	void render(const Ptr<Camera> &camera);
	void render(const Ptr<Camera> &camera, int width, int height);
	void renderTexture2D(const Ptr<Camera> &camera, const Ptr<Texture> &texture);
	void renderImage2D(const Ptr<Camera> &camera, const Ptr<Image> &image);
	void renderImage2D(const Ptr<Camera> &camera, const Ptr<Image> &image, int width, int height, int hdr = 0);
	void renderImageCube(const Ptr<Camera> &camera, const Ptr<Image> &image, int size, int hdr = 0, int local_space = 0);
	void renderImageCube(const Ptr<Camera> &camera, const Ptr<Image> &image);
	void renderStereo(const Ptr<Camera> &camera_left, const Ptr<Camera> &camera_right, const char *stereo_material);
	void setStereoHiddenAreaMesh(const Ptr<Mesh> &hidden_area_mesh_left, const Ptr<Mesh> &hidden_area_mesh_right);
	void clearStereoHiddenAreaMesh();
	void setNodeLightUsage(int usage);
	int getNodeLightUsage() const;
	void setNodeEnvironmentTextureName(const char *name);
	void renderNode(const Ptr<Camera> &camera, const Ptr<Node> &node);
	void renderNode(const Ptr<Camera> &camera, const Ptr<Node> &node, int width, int height);
	void renderNodeTexture2D(const Ptr<Camera> &camera, const Ptr<Node> &node, const Ptr<Texture> &texture);
	void renderNodeImage2D(const Ptr<Camera> &camera, const Ptr<Node> &node, const Ptr<Image> &image, int width, int height, int hdr);
	void renderNodeImage2D(const Ptr<Camera> &camera, const Ptr<Node> &node, const Ptr<Image> &image);
	void renderNodes(const Ptr<Camera> &camera, const Vector< Ptr<Node> > &nodes);
	void renderNodes(const Ptr<Camera> &camera, const Vector< Ptr<Node> > &nodes, int width, int height);
	void renderNodesTexture2D(const Ptr<Camera> &camera, const Vector< Ptr<Node> > &nodes, const Ptr<Texture> &texture);
	void renderNodesImage2D(const Ptr<Camera> &camera, const Vector< Ptr<Node> > &nodes, const Ptr<Image> &image, int width, int height, int hdr);
	void renderNodesImage2D(const Ptr<Camera> &camera, const Vector< Ptr<Node> > &nodes, const Ptr<Image> &image);
	void *addCallback(Render::CALLBACK_INDEX callback, Unigine::CallbackBase *func);
	bool removeCallback(Render::CALLBACK_INDEX callback, void *id);
	void clearCallbacks(Render::CALLBACK_INDEX callback);
};
typedef Ptr<Viewport> ViewportPtr;

} // namespace Unigine