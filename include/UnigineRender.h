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
#include "UniginePtr.h"
#include "UnigineMathLib.h"
#include "UnigineCallback.h"
#include "UnigineGUID.h"

namespace Unigine
{

class BakeLighting;
class Material;
class Object;
class Viewport;
class Shader;
class Texture;
class RenderTarget;
class Light;
class Camera;
class StructuredBuffer;
class Image;
class Node;
class Xml;
class Stream;

class UNIGINE_API RenderEnvironmentPreset : public APIInterface
{
public:
	int getNum() const;
	void setIntensity(float intensity);
	float getIntensity() const;
	void setHazeColor(const Math::vec4 &color);
	Math::vec4 getHazeColor() const;
	void setHazeDensity(float density);
	float getHazeDensity() const;
	void setHazeMaxDistance(float distance);
	float getHazeMaxDistance() const;
	void setScatteringBaseLUTName(const char *name);
	const char *getScatteringBaseLUTName() const;
	void setScatteringMieLUTName(const char *name);
	const char *getScatteringMieLUTName() const;
	void setScatteringLightColorLUTName(const char *name);
	const char *getScatteringLightColorLUTName() const;
	void setSunTextureName(const char *name);
	const char *getSunTextureName() const;
	void setSunAngularSize(float size);
	float getSunAngularSize() const;
	void setSunTextureColor(const Math::vec4 &color);
	Math::vec4 getSunTextureColor() const;
	void setSunTextureIntensity(float intensity);
	float getSunTextureIntensity() const;
	void setMoonTextureName(const char *name);
	const char *getMoonTextureName() const;
	void setMoonAngularSize(float size);
	float getMoonAngularSize() const;
	void setMoonTextureColor(const Math::vec4 &color);
	Math::vec4 getMoonTextureColor() const;
	void setMoonTextureIntensity(float intensity);
	float getMoonTextureIntensity() const;
	void setTextureColor(const Math::vec4 &color);
	Math::vec4 getTextureColor() const;
	void setTextureRotation(const Math::vec3 &rotation);
	Math::vec3 getTextureRotation() const;
	void setTextureBlur(float blur);
	float getTextureBlur() const;
	void setTextureName(const char *name);
	const char *getTextureName() const;
	void setAmbientIntensity(float intensity);
	float getAmbientIntensity() const;
	void setReflectionIntensity(float intensity);
	float getReflectionIntensity() const;
	void setSkyIntensity(float intensity);
	float getSkyIntensity() const;
};
typedef Ptr<RenderEnvironmentPreset> RenderEnvironmentPresetPtr;

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Render
{
protected:
	

public:
	static int isInitialized(); 

	enum
	{
		STREAMING_ASYNC,
		STREAMING_FORCE,
	};

	enum
	{
		API_UNKNOWN = 0,
		API_NULL,
		API_OPENGL,
		API_DIRECT3D11,
	};

	enum
	{
		GPU_UNKNOWN = 0,
		GPU_AMD,
		GPU_NVIDIA,
		GPU_INTEL,
		GPU_ARM,
		GPU_APPLE,
		GPU_IMGTEC,
		GPU_QUALCOMM,
	};

	enum
	{
		QUALITY_LOW = 0,
		QUALITY_MEDIUM,
		QUALITY_HIGH,
	};

	enum
	{
		EXPOSURE_DISABLED = 0,
		EXPOSURE_LOGARITHMIC,
		EXPOSURE_QUADRATIC,
	};

	enum PASS
	{
		PASS_WIREFRAME = 0,
		PASS_VISUALIZER_SOLID,
		PASS_DEFERRED,
		PASS_AUXILIARY,
		PASS_EMISSION,
		PASS_REFLECTION,
		PASS_REFRACTION,
		PASS_TRANSPARENT_BLUR,
		PASS_AMBIENT,
		PASS_LIGHT_VOXEL_PROBE,
		PASS_LIGHT_ENVIRONMENT_PROBE,
		PASS_LIGHT_OMNI,
		PASS_LIGHT_PROJ,
		PASS_LIGHT_WORLD,
		PASS_SHADOW,
		PASS_DEPTH_PRE_PASS,
		PASS_POST,
		PASS_CUSTOM_0,
		PASS_CUSTOM_1,
		PASS_CUSTOM_2,
		PASS_CUSTOM_3,
		PASS_CUSTOM_4,
		PASS_CUSTOM_5,
		PASS_CUSTOM_6,
		PASS_CUSTOM_7,
		PASS_CUSTOM_8,
		PASS_CUSTOM_9,
		PASS_CUSTOM_10,
		PASS_CUSTOM_11,
		PASS_CUSTOM_12,
		PASS_CUSTOM_13,
		PASS_CUSTOM_14,
		PASS_CUSTOM_15,
		PASS_CUSTOM_16,
		PASS_CUSTOM_17,
		PASS_CUSTOM_18,
		PASS_CUSTOM_19,
		PASS_CUSTOM_20,
		PASS_CUSTOM_21,
		PASS_CUSTOM_22,
		PASS_CUSTOM_23,
		PASS_CUSTOM_24,
		PASS_CUSTOM_25,
		PASS_CUSTOM_26,
		PASS_CUSTOM_27,
		PASS_CUSTOM_28,
		PASS_CUSTOM_29,
		PASS_CUSTOM_30,
		PASS_CUSTOM_31,
		PASS_CUSTOM_32,
		NUM_PASSES,
	};

	enum
	{
		ENVIRONMENT_NUM_PRESETS = 3,
	};

	enum CORRECT_ROUGHNESS
	{
		CORRECT_ROUGHNESS_DISABLED = 0,
		CORRECT_ROUGHNESS_LOW,
		CORRECT_ROUGHNESS_MEDIUM,
		CORRECT_ROUGHNESS_HIGH,
		CORRECT_ROUGHNESS_ULTRA,
	};

	enum
	{
		HAZE_DISABLED = 0,
		HAZE_SOLID,
		HAZE_SCATTERING,
	};

	enum CALLBACK_INDEX
	{
		CALLBACK_BEGIN = 0,
		CALLBACK_BEGIN_OPACITY_GBUFFER,
		CALLBACK_END_OPACITY_GBUFFER,
		CALLBACK_BEGIN_OPACITY_DECALS,
		CALLBACK_END_OPACITY_DECALS,
		CALLBACK_BEGIN_CURVATURE,
		CALLBACK_END_CURVATURE,
		CALLBACK_BEGIN_CURVATURE_COMPOSITE,
		CALLBACK_END_CURVATURE_COMPOSITE,
		CALLBACK_BEGIN_SSRTGI,
		CALLBACK_END_SSRTGI,
		CALLBACK_BEGIN_OPACITY_LIGHTS,
		CALLBACK_END_OPACITY_LIGHTS,
		CALLBACK_BEGIN_OPACITY_VOXEL_PROBES,
		CALLBACK_END_OPACITY_VOXEL_PROBES,
		CALLBACK_BEGIN_OPACITY_ENVIRONMENT_PROBES,
		CALLBACK_END_OPACITY_ENVIRONMENT_PROBES,
		CALLBACK_BEGIN_AUXILIARY_BUFFER,
		CALLBACK_END_AUXILIARY_BUFFER,
		CALLBACK_BEGIN_REFRACTION_BUFFER,
		CALLBACK_END_REFRACTION_BUFFER,
		CALLBACK_BEGIN_TRANSPARENT_BLUR_BUFFER,
		CALLBACK_END_TRANSPARENT_BLUR_BUFFER,
		CALLBACK_BEGIN_SSR,
		CALLBACK_END_SSR,
		CALLBACK_BEGIN_SSAO,
		CALLBACK_END_SSAO,
		CALLBACK_BEGIN_SSGI,
		CALLBACK_END_SSGI,
		CALLBACK_BEGIN_COMPOSITE_DEFERRED,
		CALLBACK_END_COMPOSITE_DEFERRED,
		CALLBACK_BEGIN_TRANSPARENT,
		CALLBACK_BEGIN_CLOUDS,
		CALLBACK_END_CLOUDS,
		CALLBACK_BEGIN_WATER,
		CALLBACK_BEGIN_WATER_DECALS,
		CALLBACK_END_WATER_DECALS,
		CALLBACK_BEGIN_WATER_LIGHTS,
		CALLBACK_END_WATER_LIGHTS,
		CALLBACK_BEGIN_WATER_VOXEL_PROBES,
		CALLBACK_END_WATER_VOXEL_PROBES,
		CALLBACK_BEGIN_WATER_ENVIRONMENT_PROBES,
		CALLBACK_END_WATER_ENVIRONMENT_PROBES,
		CALLBACK_END_WATER,
		CALLBACK_END_TRANSPARENT,
		CALLBACK_BEGIN_SRGB_CORRECTION,
		CALLBACK_END_SRGB_CORRECTION,
		CALLBACK_BEGIN_ADAPTATION_COLOR_AVERAGE,
		CALLBACK_END_ADAPTATION_COLOR_AVERAGE,
		CALLBACK_BEGIN_ADAPTATION_COLOR,
		CALLBACK_END_ADAPTATION_COLOR,
		CALLBACK_BEGIN_TAA,
		CALLBACK_END_TAA,
		CALLBACK_BEGIN_CAMERA_EFFECTS,
		CALLBACK_END_CAMERA_EFFECTS,
		CALLBACK_BEGIN_POST_MATERIALS,
		CALLBACK_END_POST_MATERIALS,
		CALLBACK_BEGIN_DEBUG_MATERIALS,
		CALLBACK_END_DEBUG_MATERIALS,
		CALLBACK_BEGIN_VISUALIZER,
		CALLBACK_END_VISUALIZER,
		CALLBACK_END,
		NUM_CALLBACKS,
	};
	static void renderProcedurals(const Vector< Ptr<Material> > &materials);
	static int createMipmapsCubeGGX(const Ptr<Image> &image, float quality);
	static int createShorelineDistanceField(const Ptr<Image> &image, const Ptr<Image> &mask, int shoreline_radius, int blur_radius, int downsample_resolution);
	static int compressTexture(const Ptr<Texture> &texture, Ptr<Image> &destination, int quality = 1, int new_texture_format = -1, int use_mip_maps = -1);
	static int compressImage(Ptr<Image> &image, int quality = 1, int new_image_format = -1, int use_mip_maps = -1);
	static void renderImage2D(const Ptr<Camera> &camera, const Ptr<Image> &image, int skip_flags);
	static void renderImage2D(const Ptr<Camera> &camera, const Ptr<Image> &image, int width, int height, int hdr, int skip_flags);
	static void renderImageCube(const Ptr<Camera> &camera, const Ptr<Image> &image, int size, int hdr, int skip_flags, bool local_space = false);
	static void renderImageCube(const Ptr<Camera> &camera, const Ptr<Image> &image, int skip_flags);
	static void renderNodeImage2D(const Ptr<Camera> &camera, const Ptr<Node> &node, const Ptr<Image> &image, int skip_flags, int light_usage, const char *environment_texture_name);
	static void renderNodeImage2D(const Ptr<Camera> &camera, const Ptr<Node> &node, const Ptr<Image> &image, int width, int height, int hdr, int skip_flags, int light_usage, const char *environment_texture_name);
	static void renderScreenMaterial(const char *material_name, const char *texture_name, const Ptr<Texture> &texture);
	static void renderScreenMaterial(const char *material_name, const Ptr<Texture> &color_texture);
	static void renderScreenMaterial(const char *material_name);
	static void renderComputeMaterial(Render::PASS pass, const Ptr<Material> &material, int width, int height, int depth);
	static void renderTAA(const Ptr<Texture> &color_texture, const Ptr<Texture> &color_old_texture);
	static void convertColorSpecularToMetalness(Math::vec4 &diffuse, Math::vec4 &specular, Math::vec4 &albedo, Math::vec4 &shading);
	static void convertImageSpecularToMetalness(const Ptr<Image> &diffuse, const Ptr<Image> &specular, Ptr<Image> &albedo, Ptr<Image> &shading);
	static void getScreenshot(const Ptr<Image> &image);
	static void beginDebugGroup(const char *name);
	static void endDebugGroup();
	static int getAPI();
	static bool isAPISupported(int api);
	static int getGPUName();
	static int getGPUMemory();
	static size_t getMaxTextureBufferSize();
	static bool isFlipped();
	static int getNumInstances();
	static int getMaxFieldSpacers();
	static int getMaxFieldAnimations();
	static int getMaxFieldHeights();
	static int getMaxFieldShorelines();
	static int isEnabled();
	static void setEnabled(int arg1);
	static void *addCallback(Render::CALLBACK_INDEX callback, Unigine::CallbackBase *func);
	static bool removeCallback(Render::CALLBACK_INDEX callback, void *id);
	static void clearCallbacks(Render::CALLBACK_INDEX callback);
	static void setData(const char *data);
	static const char *getData();
	static void setFirstFrame(bool frame);
	static bool isFirstFrame();
	static void setClearBufferMask(int mask);
	static int getClearBufferMask();
	static void setShaderDefines(const char *defines);
	static const char *getShaderDefines();
	static void setViewport(const Ptr<Viewport> &viewport);
	static Ptr<Viewport> getViewport();
	static void clearScriptableMaterials();
	static int getNumScriptableMaterials();
	static Ptr<Material> getScriptableMaterial(int num);
	static void setScriptableMaterial(int num, const Ptr<Material> &material);
	static int findScriptableMaterial(const Ptr<Material> &material);
	static void addScriptableMaterial(const Ptr<Material> &material);
	static void removeScriptableMaterial(int num);
	static void swapScriptableMaterials(int num_0, int num_1);
	static void setScriptableMaterialEnabled(int num, bool enabled);
	static bool getScriptableMaterialEnabled(int num);
	static void setPrePostMaterials(const char *materials);
	static const char *getPrePostMaterials();
	static void setCompositeMaterial(const char *material);
	static const char *getCompositeMaterial();
	static void setPostMaterials(const char *materials);
	static const char *getPostMaterials();
	static void setBudget(float budget);
	static float getBudget();
	static void setBorder(const Math::vec2 &border);
	static Math::vec2 getBorder();
	static void setMaxFPS(float maxfps);
	static float getMaxFPS();
	static void setVirtualResolution(const Math::vec2 &resolution);
	static Math::vec2 getVirtualResolution();
	static void setDepthPrePass(bool pass);
	static bool isDepthPrePass();
	static void setGbufferLightmap(bool lightmap);
	static bool isGbufferLightmap();
	static void setDebug(bool debug);
	static bool isDebug();
	static void setDebugMaterials(const char *materials);
	static const char *getDebugMaterials();
	static void setDeferredMaterial(const char *material);
	static const char *getDeferredMaterial();
	static void setLatency(int latency);
	static int getLatency();
	static void setTexturesQuality(int quality);
	static int getTexturesQuality();
	static void setTexturesMaxResolution(int resolution);
	static int getTexturesMaxResolution();
	static void setTexturesMinResolution(int resolution);
	static int getTexturesMinResolution();
	static void setTexturesFilter(int filter);
	static int getTexturesFilter();
	static void setTexturesAnisotropy(int anisotropy);
	static int getTexturesAnisotropy();
	static void setStreamingMode(int mode);
	static int getStreamingMode();
	static void setStreamingUseMemoryLimit(bool limit);
	static bool isStreamingUseMemoryLimit();
	static void setStreamingMaxThreads(int threads);
	static int getStreamingMaxThreads();
	static void setStreamingDestroyDuration(int duration);
	static int getStreamingDestroyDuration();
	static void setStreamingTexturesMemoryLimit(int limit);
	static int getStreamingTexturesMemoryLimit();
	static void setStreamingTexturesCachePreload(bool preload);
	static bool isStreamingTexturesCachePreload();
	static void setStreamingTexturesCacheResolution(int resolution);
	static int getStreamingTexturesCacheResolution();
	static void setStreamingMeshesMemoryLimit(int limit);
	static int getStreamingMeshesMemoryLimit();
	static void setStreamingParticlesMemoryLimit(int limit);
	static int getStreamingParticlesMemoryLimit();
	static void setShadersPreload(bool preload);
	static bool isShadersPreload();
	static void setFPSStabilization(bool stabilization);
	static bool isFPSStabilization();
	static void setFPSStabilizationSpeedUP(float fpsstabilizationspeedup);
	static float getFPSStabilizationSpeedUP();
	static void setFPSStabilizationSpeedDown(float down);
	static float getFPSStabilizationSpeedDown();
	static void setFPSStabilizationMin(int min);
	static int getFPSStabilizationMin();
	static void setFPSStabilizationRounding(int rounding);
	static int getFPSStabilizationRounding();
	static void setFPSStabilizationOffset(int offset);
	static int getFPSStabilizationOffset();
	static void setDistanceScale(float scale);
	static float getDistanceScale();
	static void setFieldDistance(float distance);
	static float getFieldDistance();
	static void setLightDistance(float distance);
	static float getLightDistance();
	static void setDecalDistance(float distance);
	static float getDecalDistance();
	static void setObjectDistance(float distance);
	static float getObjectDistance();
	static void setReflectionDistance(float distance);
	static float getReflectionDistance();
	static void setShadowDistanceScale(float scale);
	static float getShadowDistanceScale();
	static void setShadowDistance(float distance);
	static float getShadowDistance();
	static void setAnimationStem(float stem);
	static float getAnimationStem();
	static void setAnimationLeaf(float leaf);
	static float getAnimationLeaf();
	static void setAnimationScale(float scale);
	static float getAnimationScale();
	static void setAnimationWind(const Math::vec3 &wind);
	static Math::vec3 getAnimationWind();
	static void setAnimationTime(float time);
	static float getAnimationTime();
	static float getAnimationOldTime();
	static void setVREmulation(int emulation);
	static int getVREmulation();
	static void setStereo(int stereo);
	static int getStereo();
	static void setStereoDistance(float distance);
	static float getStereoDistance();
	static void setStereoRadius(float radius);
	static float getStereoRadius();
	static void setStereoOffset(float offset);
	static float getStereoOffset();
	static void setStereoHiddenArea(int area);
	static int getStereoHiddenArea();
	static void setStereoHiddenAreaTransform(const Math::vec4 &transform);
	static Math::vec4 getStereoHiddenAreaTransform();
	static void setStereoHiddenAreaExposureTransform(const Math::vec4 &transform);
	static Math::vec4 getStereoHiddenAreaExposureTransform();
	static void setStereoReprojection(int reprojection);
	static int getStereoReprojection();
	static void setStereoReprojectionFixBlur(bool blur);
	static bool isStereoReprojectionFixBlur();
	static void setStereoReprojectionBuffersFixBlur(bool blur);
	static bool isStereoReprojectionBuffersFixBlur();
	static void setStereoReprojectionThreshold(float threshold);
	static float getStereoReprojectionThreshold();
	static void setPanorama(int panorama);
	static int getPanorama();
	static void setSupersampling(float supersampling);
	static float getSupersampling();
	static void setTAA(bool taa);
	static bool isTAA();
	static void setTAAFixFlicker(bool flicker);
	static bool isTAAFixFlicker();
	static void setTAAAntialiasingInMotion(bool motion);
	static bool isTAAAntialiasingInMotion();
	static void setTAAFramesByColor(bool color);
	static bool isTAAFramesByColor();
	static void setTAAFramesByVelocity(bool velocity);
	static bool isTAAFramesByVelocity();
	static void setTAADiagonalNeighbors(bool neighbors);
	static bool isTAADiagonalNeighbors();
	static void setTAAPreserveDetails(float details);
	static float getTAAPreserveDetails();
	static void setTAAFrameCount(float count);
	static float getTAAFrameCount();
	static void setTAAFramesVelocityThreshold(float threshold);
	static float getTAAFramesVelocityThreshold();
	static void setTAAMaxFramesByVelocity(float velocity);
	static float getTAAMaxFramesByVelocity();
	static void setTAAMinFramesByVelocity(float velocity);
	static float getTAAMinFramesByVelocity();
	static void setTAAPixelOffset(float offset);
	static float getTAAPixelOffset();
	static void setTAACatmullResampling(bool resampling);
	static bool isTAACatmullResampling();
	static void setTAASamples(int samples);
	static int getTAASamples();
	static void setFXAA(bool fxaa);
	static bool isFXAA();
	static void setFXAAIntensity(float intensity);
	static float getFXAAIntensity();
	static void setSharpen(bool sharpen);
	static bool isSharpen();
	static void setSharpenIntensity(float intensity);
	static float getSharpenIntensity();
	static void setAlphaFade(bool fade);
	static bool isAlphaFade();
	static void setAuxiliary(bool auxiliary);
	static bool isAuxiliary();
	static void setDecals(bool decals);
	static bool isDecals();
	static void setRefraction(bool refraction);
	static bool isRefraction();
	static void setRefractionDispersion(const Math::vec3 &dispersion);
	static Math::vec3 getRefractionDispersion();
	static void setTransparentBlur(bool blur);
	static bool isTransparentBlur();
	static void setReflectionDynamic(bool dynamic);
	static bool isReflectionDynamic();
	static void setReflectionLods(bool lods);
	static bool isReflectionLods();
	static void setSSRTGI(bool ssrtgi);
	static bool isSSRTGI();
	static void setSSRTGIFastTracing(bool tracing);
	static bool isSSRTGIFastTracing();
	static void setSSRTGIIncreasedAccuracy(bool accuracy);
	static bool isSSRTGIIncreasedAccuracy();
	static void setSSRTGIUpscaling(bool upscaling);
	static bool isSSRTGIUpscaling();
	static void setSSRTGIResolution(int resolution);
	static int getSSRTGIResolution();
	static void setSSRTGIResolutionDepth(int depth);
	static int getSSRTGIResolutionDepth();
	static void setSSRTGINumRays(int rays);
	static int getSSRTGINumRays();
	static void setSSRTGINumSteps(int steps);
	static int getSSRTGINumSteps();
	static void setSSRTGINoiseRay(float ray);
	static float getSSRTGINoiseRay();
	static void setSSRTGINoiseStep(float step);
	static float getSSRTGINoiseStep();
	static void setSSRTGIStepSize(float size);
	static float getSSRTGIStepSize();
	static void setSSAO(bool ssao);
	static bool isSSAO();
	static void setSSAOCavity(bool cavity);
	static bool isSSAOCavity();
	static void setSSAONoise(bool noise);
	static bool isSSAONoise();
	static void setSSAORayTracing(bool tracing);
	static bool isSSAORayTracing();
	static void setSSAORayTracingDenoise(bool denoise);
	static bool isSSAORayTracingDenoise();
	static void setSSAOQuality(int quality);
	static int getSSAOQuality();
	static void setSSAODenoiseQuality(int quality);
	static int getSSAODenoiseQuality();
	static void setSSAOResolution(int resolution);
	static int getSSAOResolution();
	static void setSSAOIntensity(float intensity);
	static float getSSAOIntensity();
	static void setSSAOIntensityLightedSide(float side);
	static float getSSAOIntensityLightedSide();
	static void setSSAOIntensityReflection(float reflection);
	static float getSSAOIntensityReflection();
	static void setSSAORayTracingThreshold(float threshold);
	static float getSSAORayTracingThreshold();
	static void setSSAORadius(float radius);
	static float getSSAORadius();
	static void setSSAOCavityIntensity(float intensity);
	static float getSSAOCavityIntensity();
	static void setSSAOCavityRadius(float radius);
	static float getSSAOCavityRadius();
	static void setSSAOThreshold(float threshold);
	static float getSSAOThreshold();
	static void setSSGI(bool ssgi);
	static bool isSSGI();
	static void setSSGIRayTracing(bool tracing);
	static bool isSSGIRayTracing();
	static void setSSGIRayTracingDenoise(bool denoise);
	static bool isSSGIRayTracingDenoise();
	static void setSSGIDenoiseQuality(int quality);
	static int getSSGIDenoiseQuality();
	static void setSSGIDenoiseIntensity(float intensity);
	static float getSSGIDenoiseIntensity();
	static void setSSGIDenoiseGaussianSigma(float sigma);
	static float getSSGIDenoiseGaussianSigma();
	static void setSSGIDenoiseThreshold(float threshold);
	static float getSSGIDenoiseThreshold();
	static void setSSGIDenoiseRadius(int radius);
	static int getSSGIDenoiseRadius();
	static void setSSGIQuality(int quality);
	static int getSSGIQuality();
	static void setSSGIResolution(int resolution);
	static int getSSGIResolution();
	static void setSSGIResolutionColor(int color);
	static int getSSGIResolutionColor();
	static void setSSGIIntensity(float intensity);
	static float getSSGIIntensity();
	static void setSSGIRayTracingThreshold(float threshold);
	static float getSSGIRayTracingThreshold();
	static void setSSGIRadius(float radius);
	static float getSSGIRadius();
	static void setSSGINormalThreshold(float threshold);
	static float getSSGINormalThreshold();
	static void setSSGIColorClampingIntensity(float intensity);
	static float getSSGIColorClampingIntensity();
	static void setSSGIColorClampingVelocityThreshold(float threshold);
	static float getSSGIColorClampingVelocityThreshold();
	static void setBentNormalRayTracing(bool tracing);
	static bool isBentNormalRayTracing();
	static void setBentNormalRayTracingDenoise(bool denoise);
	static bool isBentNormalRayTracingDenoise();
	static void setBentNormalDenoiseQuality(int quality);
	static int getBentNormalDenoiseQuality();
	static void setBentNormalFixOverlitAreas(bool areas);
	static bool isBentNormalFixOverlitAreas();
	static void setBentNormalRayTracingThreshold(float threshold);
	static float getBentNormalRayTracingThreshold();
	static void setSSR(bool ssr);
	static bool isSSR();
	static void setSSRImportanceSampling(bool sampling);
	static bool isSSRImportanceSampling();
	static void setSSRFastTracing(bool tracing);
	static bool isSSRFastTracing();
	static void setSSRIncreasedAccuracy(bool accuracy);
	static bool isSSRIncreasedAccuracy();
	static void setSSRDenoise(bool denoise);
	static bool isSSRDenoise();
	static void setSSRDenoiseQuality(int quality);
	static int getSSRDenoiseQuality();
	static void setSSRDenoiseIntensity(float intensity);
	static float getSSRDenoiseIntensity();
	static void setSSRDenoiseGaussianSigma(float sigma);
	static float getSSRDenoiseGaussianSigma();
	static void setSSRDenoiseThreshold(float threshold);
	static float getSSRDenoiseThreshold();
	static void setSSRDenoiseRadius(int radius);
	static int getSSRDenoiseRadius();
	static void setSSRRoughnessQuality(int quality);
	static int getSSRRoughnessQuality();
	static void setSSRResolution(int resolution);
	static int getSSRResolution();
	static void setSSRResolutionDepth(int depth);
	static int getSSRResolutionDepth();
	static void setSSRResolutionColor(int color);
	static int getSSRResolutionColor();
	static void setSSRNumRays(int rays);
	static int getSSRNumRays();
	static void setSSRNumSteps(int steps);
	static int getSSRNumSteps();
	static void setSSRStepSize(float size);
	static float getSSRStepSize();
	static void setSSRNoiseRay(float ray);
	static float getSSRNoiseRay();
	static void setSSRNoiseStep(float step);
	static float getSSRNoiseStep();
	static void setSSRVisibilityRoughnessMin(float min);
	static float getSSRVisibilityRoughnessMin();
	static void setSSRVisibilityRoughnessMax(float max);
	static float getSSRVisibilityRoughnessMax();
	static void setSSRThreshold(float threshold);
	static float getSSRThreshold();
	static void setSSRThresholdOcclusion(float occlusion);
	static float getSSRThresholdOcclusion();
	static void setSSRColorClampingIntensity(float intensity);
	static float getSSRColorClampingIntensity();
	static void setSSRColorClampingVelocityThreshold(float threshold);
	static float getSSRColorClampingVelocityThreshold();
	static void setSSSSS(bool sssss);
	static bool isSSSSS();
	static void setSSSSSQuality(int quality);
	static int getSSSSSQuality();
	static void setSSSSSResolution(int resolution);
	static int getSSSSSResolution();
	static void setSSSSSRadius(float radius);
	static float getSSSSSRadius();
	static void setSSSSSColor(const Math::vec4 &color);
	static Math::vec4 getSSSSSColor();
	static void setSSSSSDiffuse(bool diffuse);
	static bool isSSSSSDiffuse();
	static void setSSSSSAmbient(bool ambient);
	static bool isSSSSSAmbient();
	static void setSSSSSMinThreshold(float threshold);
	static float getSSSSSMinThreshold();
	static void setSSSSSMaxThreshold(float threshold);
	static float getSSSSSMaxThreshold();
	static void setSSSSSNoiseStep(float step);
	static float getSSSSSNoiseStep();
	static void setSSSSSNoiseRay(float ray);
	static float getSSSSSNoiseRay();
	static void setSSSSSInterleaved(bool interleaved);
	static bool isSSSSSInterleaved();
	static void setSSSSSInterleavedColorClamping(int clamping);
	static int getSSSSSInterleavedColorClamping();
	static void setSSSSSInterleavedSamples(int samples);
	static int getSSSSSInterleavedSamples();
	static void setSSSSSTAAFixFlicker(bool flicker);
	static bool isSSSSSTAAFixFlicker();
	static void setSSSSSTAAAntialiasingInMotion(bool motion);
	static bool isSSSSSTAAAntialiasingInMotion();
	static void setSSSSSTAAFramesByColor(bool color);
	static bool isSSSSSTAAFramesByColor();
	static void setSSSSSTAAFramesByVelocity(bool velocity);
	static bool isSSSSSTAAFramesByVelocity();
	static void setSSSSSTAAPreserveDetails(float details);
	static float getSSSSSTAAPreserveDetails();
	static void setSSSSSTAAFrameCount(float count);
	static float getSSSSSTAAFrameCount();
	static void setSSSSSTAAFramesVelocityThreshold(float threshold);
	static float getSSSSSTAAFramesVelocityThreshold();
	static void setSSSSSTAAMaxFramesByVelocity(float velocity);
	static float getSSSSSTAAMaxFramesByVelocity();
	static void setSSSSSTAAMinFramesByVelocity(float velocity);
	static float getSSSSSTAAMinFramesByVelocity();
	static void setSSSSSTAACatmullResampling(bool resampling);
	static bool isSSSSSTAACatmullResampling();
	static void setSSSSSTAASamples(int samples);
	static int getSSSSSTAASamples();
	static void setTranslucentColor(const Math::vec4 &color);
	static Math::vec4 getTranslucentColor();
	static void setCameraEffectsThreshold(float threshold);
	static float getCameraEffectsThreshold();
	static void setCameraEffectsTemporalFiltering(bool filtering);
	static bool isCameraEffectsTemporalFiltering();
	static void setDirtScale(float scale);
	static float getDirtScale();
	static void setDirtTextureName(const char *name);
	static const char *getDirtTextureName();
	static void setCameraMode(int mode);
	static int getCameraMode();
	static void setISO(float iso);
	static float getISO();
	static void setShutterSpeed(float speed);
	static float getShutterSpeed();
	static void setFStop(float fstop);
	static float getFStop();
	static void setExposureMode(int mode);
	static int getExposureMode();
	static void setExposure(float exposure);
	static float getExposure();
	static void setExposureAdaptation(float adaptation);
	static float getExposureAdaptation();
	static void setExposureMinLuminance(float luminance);
	static float getExposureMinLuminance();
	static void setExposureMaxLuminance(float luminance);
	static float getExposureMaxLuminance();
	static void setWhiteBalance(bool balance);
	static bool isWhiteBalance();
	static void setWhiteBalanceIntensity(float intensity);
	static float getWhiteBalanceIntensity();
	static void setWhiteBalanceAdaptationTime(float time);
	static float getWhiteBalanceAdaptationTime();
	static void setMotionBlur(bool blur);
	static bool isMotionBlur();
	static void setMotionBlurNeatSilhouettes(bool silhouettes);
	static bool isMotionBlurNeatSilhouettes();
	static void setMotionBlurCameraVelocity(bool velocity);
	static bool isMotionBlurCameraVelocity();
	static void setMotionBlurVelocityScale(float scale);
	static float getMotionBlurVelocityScale();
	static void setMotionBlurMaxVelocity(float velocity);
	static float getMotionBlurMaxVelocity();
	static void setMotionBlurNoiseIntensity(float intensity);
	static float getMotionBlurNoiseIntensity();
	static void setMotionBlurNumSteps(int steps);
	static int getMotionBlurNumSteps();
	static void setDOF(bool dof);
	static bool isDOF();
	static void setDOFIncreasedAccuracy(bool accuracy);
	static bool isDOFIncreasedAccuracy();
	static void setDOFFocusImprovement(bool improvement);
	static bool isDOFFocusImprovement();
	static void setDOFQuality(int quality);
	static int getDOFQuality();
	static void setDOFResolution(int resolution);
	static int getDOFResolution();
	static void setDOFBokehMode(int mode);
	static int getDOFBokehMode();
	static void setDOFFocalDistance(float distance);
	static float getDOFFocalDistance();
	static void setDOFChromaticAberration(float aberration);
	static float getDOFChromaticAberration();
	static void setDOFBlur(float blur);
	static float getDOFBlur();
	static void setDOFFarDistance(float distance);
	static float getDOFFarDistance();
	static void setDOFFarFocalOffset(float offset);
	static float getDOFFarFocalOffset();
	static void setDOFNearDistance(float distance);
	static float getDOFNearDistance();
	static void setDOFNearFocalOffset(float offset);
	static float getDOFNearFocalOffset();
	static void setBloom(bool bloom);
	static bool isBloom();
	static void setBloomResolution(int resolution);
	static int getBloomResolution();
	static void setBloomPasses(int passes);
	static int getBloomPasses();
	static void setBloomScale(float scale);
	static float getBloomScale();
	static void setBloomPower(float power);
	static float getBloomPower();
	static void setFilmic(bool filmic);
	static bool isFilmic();
	static void setFilmicShoulderScale(float scale);
	static float getFilmicShoulderScale();
	static void setFilmicLinearScale(float scale);
	static float getFilmicLinearScale();
	static void setFilmicLinearAngle(float angle);
	static float getFilmicLinearAngle();
	static void setFilmicToeScale(float scale);
	static float getFilmicToeScale();
	static void setFilmicToeNumerator(float numerator);
	static float getFilmicToeNumerator();
	static void setFilmicToeDenominator(float denominator);
	static float getFilmicToeDenominator();
	static void setFilmicWhiteLevel(float level);
	static float getFilmicWhiteLevel();
	static void setFilmicSaturationRecovery(float recovery);
	static float getFilmicSaturationRecovery();
	static void setCross(bool cross);
	static bool isCross();
	static void setCrossShafts(int shafts);
	static int getCrossShafts();
	static void setCrossLength(float length);
	static float getCrossLength();
	static void setCrossScale(float scale);
	static float getCrossScale();
	static void setCrossAngle(float angle);
	static float getCrossAngle();
	static void setCrossThreshold(float threshold);
	static float getCrossThreshold();
	static void setCrossColor(const Math::vec4 &color);
	static Math::vec4 getCrossColor();
	static void setSunShafts(bool shafts);
	static bool isSunShafts();
	static void setSunShaftsScale(float scale);
	static float getSunShaftsScale();
	static void setSunShaftsLength(float length);
	static float getSunShaftsLength();
	static void setSunShaftsAttenuation(float attenuation);
	static float getSunShaftsAttenuation();
	static void setSunShaftsThreshold(float threshold);
	static float getSunShaftsThreshold();
	static void setSunShaftsColor(const Math::vec4 &color);
	static Math::vec4 getSunShaftsColor();
	static void setShadowShafts(bool shafts);
	static bool isShadowShafts();
	static void setShadowShaftsExposure(float exposure);
	static float getShadowShaftsExposure();
	static void setShadowShaftsLength(float length);
	static float getShadowShaftsLength();
	static void setLens(bool lens);
	static bool isLens();
	static void setLensScale(float scale);
	static float getLensScale();
	static void setLensLength(float length);
	static float getLensLength();
	static void setLensRadius(float radius);
	static float getLensRadius();
	static void setLensThreshold(float threshold);
	static float getLensThreshold();
	static void setLensColor(const Math::vec4 &color);
	static Math::vec4 getLensColor();
	static void setLensDispersion(const Math::vec3 &dispersion);
	static Math::vec3 getLensDispersion();
	static void setWireframeColor(const Math::vec4 &color);
	static Math::vec4 getWireframeColor();
	static void setBackgroundColor(const Math::vec4 &color);
	static Math::vec4 getBackgroundColor();
	static void setFadeColor(const Math::vec4 &color);
	static Math::vec4 getFadeColor();
	static void setWireframeAntialiasing(bool antialiasing);
	static bool isWireframeAntialiasing();
	static void setFfpAntialiasingLines(bool lines);
	static bool isFfpAntialiasingLines();
	static void setColorBrightness(float brightness);
	static float getColorBrightness();
	static void setColorContrast(float contrast);
	static float getColorContrast();
	static void setColorSaturation(float saturation);
	static float getColorSaturation();
	static void setColorGamma(float gamma);
	static float getColorGamma();
	static void setColorWhite(const Math::vec4 &white);
	static Math::vec4 getColorWhite();
	static int setColorTextureImage(const Ptr<Image> &image);
	static int getColorTextureImage(Ptr<Image> &image);
	static void setColorTextureName(const char *name);
	static const char *getColorTextureName();
	static void setEnvironment(bool environment);
	static bool isEnvironment();
	static void setEnvironmentHazeMode(int mode);
	static int getEnvironmentHazeMode();
	static void setEnvironmentHazeGradient(int gradient);
	static int getEnvironmentHazeGradient();
	static void setEnvironmentCubemapBlendMode(int mode);
	static int getEnvironmentCubemapBlendMode();
	static void setEnvironmentCorrectRoughness(Render::CORRECT_ROUGHNESS roughness);
	static Render::CORRECT_ROUGHNESS getEnvironmentCorrectRoughness();
	static Ptr<RenderEnvironmentPreset> getEnvironmentPreset(int num);
	static Math::vec4 getEnvironmentHazeColor();
	static float getEnvironmentHazeMaxDistance();
	static float getEnvironmentHazeDensity();
	static float getEnvironmentAmbientIntensity();
	static float getEnvironmentReflectionIntensity();
	static float getEnvironmentSkyIntensity();
	static void setSkyRotation(const Math::quat &rotation);
	static Math::quat getSkyRotation();
	static void setOcclusionQueries(bool queries);
	static bool isOcclusionQueries();
	static void setOcclusionQueriesNumFrames(int frames);
	static int getOcclusionQueriesNumFrames();
	static void setOccluders(bool occluders);
	static bool isOccluders();
	static void setOccludersResolution(const Math::vec2 &resolution);
	static Math::vec2 getOccludersResolution();
	static void setOccludersShadows(bool shadows);
	static bool isOccludersShadows();
	static void setOccludersShadowsResolution(const Math::vec2 &resolution);
	static Math::vec2 getOccludersShadowsResolution();
	static void setLightsEnabled(bool enabled);
	static bool isLightsEnabled();
	static void setLightsMaxPerBatch(int batch);
	static int getLightsMaxPerBatch();
	static void setLightsTileGridSize(int size);
	static int getLightsTileGridSize();
	static void setLightsInterleaved(bool interleaved);
	static bool isLightsInterleaved();
	static void setLightsInterleavedCatmullResampling(bool resampling);
	static bool isLightsInterleavedCatmullResampling();
	static void setLightsInterleavedColorClamping(int clamping);
	static int getLightsInterleavedColorClamping();
	static void setLightsInterleavedSamples(int samples);
	static int getLightsInterleavedSamples();
	static void setLightsForwardPerObjectWorld(int world);
	static int getLightsForwardPerObjectWorld();
	static void setLightsForwardPerObjectOmni(int omni);
	static int getLightsForwardPerObjectOmni();
	static void setLightsForwardPerObjectProj(int proj);
	static int getLightsForwardPerObjectProj();
	static void setLightsForwardPerObjectEnv(int env);
	static int getLightsForwardPerObjectEnv();
	static void setLightsForwardPerObjectVoxel(int voxel);
	static int getLightsForwardPerObjectVoxel();
	static void setLightsLensFlares(bool flares);
	static bool isLightsLensFlares();
	static void setShadows(bool shadows);
	static bool isShadows();
	static void setShadowsTranslucentDepth(float depth);
	static float getShadowsTranslucentDepth();
	static void setShadowsWorldLerpCascades(bool cascades);
	static bool isShadowsWorldLerpCascades();
	static void setShadowsAlphaTest(bool test);
	static bool isShadowsAlphaTest();
	static void setShadowsScreenSpace(bool space);
	static bool isShadowsScreenSpace();
	static void setShadowsPenumbraMode(int mode);
	static int getShadowsPenumbraMode();
	static void setShadowsPenumbraNoise(bool noise);
	static bool isShadowsPenumbraNoise();
	static void setShadowsFilterMode(int mode);
	static int getShadowsFilterMode();
	static void setShadowsFilterNoise(bool noise);
	static bool isShadowsFilterNoise();
	static void setScreenPrecision(bool precision);
	static bool isScreenPrecision();
	static void setSSBevel(bool bevel);
	static bool isSSBevel();
	static void setSSBevelVertexNormal(int normal);
	static int getSSBevelVertexNormal();
	static void setSSBevelQuality(int quality);
	static int getSSBevelQuality();
	static void setSSBevelNoise(bool noise);
	static bool isSSBevelNoise();
	static void setSSBevelRadius(float radius);
	static float getSSBevelRadius();
	static void setSSDirt(bool dirt);
	static bool isSSDirt();
	static void setSSDirtQuality(int quality);
	static int getSSDirtQuality();
	static void setSSDirtResolution(int resolution);
	static int getSSDirtResolution();
	static void setSSDirtIntensity(float intensity);
	static float getSSDirtIntensity();
	static void setSSDirtRadius(float radius);
	static float getSSDirtRadius();
	static void setSSDirtThreshold(float threshold);
	static float getSSDirtThreshold();
	static void setSSDirtAngleBias(float bias);
	static float getSSDirtAngleBias();
	static void setSSDirtPerspective(float perspective);
	static float getSSDirtPerspective();
	static void setSSDirtIncreaseAccuracy(bool accuracy);
	static bool isSSDirtIncreaseAccuracy();
	static void setSSDirtCavityAlbedoTextureName(const char *name);
	static const char *getSSDirtCavityAlbedoTextureName();
	static void setSSDirtCavityShadingTextureName(const char *name);
	static const char *getSSDirtCavityShadingTextureName();
	static void setSSDirtConvexityAlbedoTextureName(const char *name);
	static const char *getSSDirtConvexityAlbedoTextureName();
	static void setSSDirtConvexityShadingTextureName(const char *name);
	static const char *getSSDirtConvexityShadingTextureName();
	static void setSSDirtCavityTextureSize(float size);
	static float getSSDirtCavityTextureSize();
	static void setSSDirtCavityColor(const Math::vec4 &color);
	static Math::vec4 getSSDirtCavityColor();
	static void setSSDirtCavityExponent(float exponent);
	static float getSSDirtCavityExponent();
	static void setSSDirtCavityMetalness(float metalness);
	static float getSSDirtCavityMetalness();
	static void setSSDirtCavityMetalnessVisibility(float visibility);
	static float getSSDirtCavityMetalnessVisibility();
	static void setSSDirtConvexityTextureSize(float size);
	static float getSSDirtConvexityTextureSize();
	static void setSSDirtConvexityColor(const Math::vec4 &color);
	static Math::vec4 getSSDirtConvexityColor();
	static void setSSDirtConvexityExponent(float exponent);
	static float getSSDirtConvexityExponent();
	static void setSSDirtConvexityMetalness(float metalness);
	static float getSSDirtConvexityMetalness();
	static void setSSDirtConvexityMetalnessVisibility(float visibility);
	static float getSSDirtConvexityMetalnessVisibility();
	static void setLandscapeTerrainVisibleDistance(float distance);
	static float getLandscapeTerrainVisibleDistance();
	static void setLandscapeTerrainTexelSize(float size);
	static float getLandscapeTerrainTexelSize();
	static void setLandscapeTerrainVTMemorySize(float size);
	static float getLandscapeTerrainVTMemorySize();
	static void setLandscapeTerrainVTTargetResolution(const Math::vec2 &resolution);
	static Math::vec2 getLandscapeTerrainVTTargetResolution();
	static void setLandscapeTerrainVTDetailLevelByAngle(float angle);
	static float getLandscapeTerrainVTDetailLevelByAngle();
	static void setLandscapeTerrainVTFiltering(int filtering);
	static int getLandscapeTerrainVTFiltering();
	static void setLandscapeTerrainVTTilesUpdatePerFrame(int frame);
	static int getLandscapeTerrainVTTilesUpdatePerFrame();
	static void setLandscapeTerrainVTTilesLoadPerFrame(int frame);
	static int getLandscapeTerrainVTTilesLoadPerFrame();
	static void setLandscapeTerrainVTTilesReloadPerFrame(int frame);
	static int getLandscapeTerrainVTTilesReloadPerFrame();
	static void setLandscapeTerrainDetailResolutionAlbedo(int albedo);
	static int getLandscapeTerrainDetailResolutionAlbedo();
	static void setLandscapeTerrainDetailResolutionHeight(int height);
	static int getLandscapeTerrainDetailResolutionHeight();
	static void setLandscapeTerrainDetailResolutionAdditionalMask(int mask);
	static int getLandscapeTerrainDetailResolutionAdditionalMask();
	static void setLandscapeTerrainGeometryHoles(bool holes);
	static bool isLandscapeTerrainGeometryHoles();
	static void setLandscapeTerrainGeometryPolygonSize(float size);
	static float getLandscapeTerrainGeometryPolygonSize();
	static void setLandscapeTerrainGeometryProgression(float progression);
	static float getLandscapeTerrainGeometryProgression();
	static void setLandscapeTerrainGeometryFadeLods(float lods);
	static float getLandscapeTerrainGeometryFadeLods();
	static void setLandscapeTerrainGeometrySubpixelReduction(float reduction);
	static float getLandscapeTerrainGeometrySubpixelReduction();
	static void setLandscapeTerrainCullingAggressive(bool aggressive);
	static bool isLandscapeTerrainCullingAggressive();
	static void setLandscapeTerrainCullingFrustumPadding(float padding);
	static float getLandscapeTerrainCullingFrustumPadding();
	static void setLandscapeTerrainCullingBackFace(float face);
	static float getLandscapeTerrainCullingBackFace();
	static void setLandscapeTerrainCullingObliqueFrustum(float frustum);
	static float getLandscapeTerrainCullingObliqueFrustum();
	static void setLandscapeCacheCPUSize(int size);
	static int getLandscapeCacheCPUSize();
	static void setLandscapeCacheGPUSize(int size);
	static int getLandscapeCacheGPUSize();
	static void setLandscapeCacheGPULifeTime(int time);
	static int getLandscapeCacheGPULifeTime();
	static void setTerrainGlobalTriplanar(bool triplanar);
	static bool isTerrainGlobalTriplanar();
	static void setTerrainGlobalDisplacement(bool displacement);
	static bool isTerrainGlobalDisplacement();
	static void setTerrainGlobalDisplacementNormal(bool normal);
	static bool isTerrainGlobalDisplacementNormal();
	static void setTerrainGlobalAnisotropy(int anisotropy);
	static int getTerrainGlobalAnisotropy();
	static void setTerrainGlobalHoles(bool holes);
	static bool isTerrainGlobalHoles();
	static void setWaterEnabled(bool enabled);
	static bool isWaterEnabled();
	static void setWaterSSR(bool waterssr);
	static bool isWaterSSR();
	static void setWaterSSRIncreasedAccuracy(bool accuracy);
	static bool isWaterSSRIncreasedAccuracy();
	static void setWaterShorelineWetness(bool wetness);
	static bool isWaterShorelineWetness();
	static void setWaterShafts(bool shafts);
	static bool isWaterShafts();
	static void setWaterOpacityDepth(bool depth);
	static bool isWaterOpacityDepth();
	static void setWaterEnvironmentProbes(bool probes);
	static bool isWaterEnvironmentProbes();
	static void setWaterVoxelProbes(bool probes);
	static bool isWaterVoxelProbes();
	static void setWaterLights(bool lights);
	static bool isWaterLights();
	static void setWaterSSRQuality(int quality);
	static int getWaterSSRQuality();
	static void setWaterRefractionQuality(int quality);
	static int getWaterRefractionQuality();
	static void setWaterAnisotropy(int anisotropy);
	static int getWaterAnisotropy();
	static void setCloudsEnabled(bool enabled);
	static bool isCloudsEnabled();
	static void setCloudsGroundShadows(bool shadows);
	static bool isCloudsGroundShadows();
	static void setCloudsShadowShafts(bool shafts);
	static bool isCloudsShadowShafts();
	static void setCloudsTransparentOrder(bool order);
	static bool isCloudsTransparentOrder();
	static void setCloudsSimplifiedDepthTest(bool test);
	static bool isCloudsSimplifiedDepthTest();
	static void setCloudsLightingQuality(int quality);
	static int getCloudsLightingQuality();
	static void setCloudsSamplingQuality(int quality);
	static int getCloudsSamplingQuality();
	static void setCloudsLightingTraceLength(float length);
	static float getCloudsLightingTraceLength();
	static void setCloudsLightingConeRadius(float radius);
	static float getCloudsLightingConeRadius();
	static void setCloudsDynamicCoverageArea(float area);
	static float getCloudsDynamicCoverageArea();
	static void setCloudsDynamicCoverageResolution(int resolution);
	static int getCloudsDynamicCoverageResolution();
	static void setCloudsInterleavedRendering(int rendering);
	static int getCloudsInterleavedRendering();
	static void setCloudsDownsamplingRendering(int rendering);
	static int getCloudsDownsamplingRendering();
	static void setCloudsSamplesCount(int count);
	static int getCloudsSamplesCount();
	static void setCloudDistortionTexture(int texture);
	static int getCloudDistortionTexture();
	static void setCloudsSoftIntersection(float intersection);
	static float getCloudsSoftIntersection();
	static void setCloudsNoiseStep(float step);
	static float getCloudsNoiseStep();
	static void setCloudsNoiseIterations(float iterations);
	static float getCloudsNoiseIterations();
	static void setCloudsNoiseLighting(float lighting);
	static float getCloudsNoiseLighting();
	static void setCloudsNoiseStepSkip(float skip);
	static float getCloudsNoiseStepSkip();
	static void setFieldHeightResolution(int resolution);
	static int getFieldHeightResolution();
	static void setFieldPrecision(bool precision);
	static bool isFieldPrecision();
	static void setFieldShorelineResolution(int resolution);
	static int getFieldShorelineResolution();
	static void setPrePostMaterialsEnabled(bool enabled);
	static bool isPrePostMaterialsEnabled();
	static void setScreenSpaceEffects(bool effects);
	static bool isScreenSpaceEffects();
	static void setTransparentEnabled(bool enabled);
	static bool isTransparentEnabled();
	static void setTransparentAmbient(bool ambient);
	static bool isTransparentAmbient();
	static void setTransparentLight(bool light);
	static bool isTransparentLight();
	static void setTransparentDeferred(bool deferred);
	static bool isTransparentDeferred();
	static void setTransparentMultipleEnvProbes(bool probes);
	static bool isTransparentMultipleEnvProbes();
	static void setShowQueries(bool queries);
	static bool isShowQueries();
	static void setShowDecals(bool decals);
	static bool isShowDecals();
	static void setShowScissors(bool scissors);
	static bool isShowScissors();
	static void setShowMipmaps(bool mipmaps);
	static bool isShowMipmaps();
	static void setShowOccluder(bool occluder);
	static bool isShowOccluder();
	static void setShowCascades(bool cascades);
	static bool isShowCascades();
	static void setShowAlphaTest(bool test);
	static bool isShowAlphaTest();
	static void setShowDynamic(bool dynamic);
	static bool isShowDynamic();
	static void setShowTransparent(bool transparent);
	static bool isShowTransparent();
	static void setShowAmbient(bool ambient);
	static bool isShowAmbient();
	static void setShowGeodeticPivot(bool pivot);
	static bool isShowGeodeticPivot();
	static void setShowLandscapeMask(int mask);
	static int getShowLandscapeMask();
	static void setShowLandscapeTerrainVTStreaming(bool streaming);
	static bool isShowLandscapeTerrainVTStreaming();
	static void setShowTextures(int textures);
	static int getShowTextures();
	static void setShowTexturesOffset(int offset);
	static int getShowTexturesOffset();
	static void setShowTexturesNumber(int number);
	static int getShowTexturesNumber();
	static void setShowTriangles(int triangles);
	static int getShowTriangles();
	static int getHDRTextureFormat();
	static Ptr<Texture> getTemporaryTexture(int width, int height, int format, int flags = 0, const char *name = 0);
	static Ptr<Texture> getTemporaryTexture(int format, const char *name = "");
	static Ptr<Texture> getTemporaryTexture(const Ptr<Texture> &texture, const char *name);
	static Ptr<Texture> getTemporaryTexture(const Ptr<Texture> &texture);
	static Ptr<Texture> getTemporary2DArrayTexture(int width, int height, int depth, int format, int flags = 0, const char *name = 0);
	static Ptr<Texture> getTemporary3DTexture(int width, int height, int depth, int format, int flags = 0, const char *name = 0);
	static void releaseTemporaryTexture(const Ptr<Texture> &texture);
	static Ptr<RenderTarget> getTemporaryRenderTarget();
	static void releaseTemporaryRenderTarget(const Ptr<RenderTarget> &render_target);
	static Ptr<Texture> getBlack2DTexture();
	static Ptr<Texture> getBlack3DTexture();
	static Ptr<Texture> getBlackCubeTexture();
	static Ptr<Texture> getBlack2DArrayTexture();
	static Ptr<Texture> getWhite2DTexture();
	static Ptr<Texture> getWhite3DTexture();
	static Ptr<Texture> getWhiteCubeTexture();
	static Ptr<Texture> getWhite2DArrayTexture();
	static Ptr<Texture> getGray2DTexture();
	static Ptr<Texture> getGray3DTexture();
	static Ptr<Texture> getGrayCubeTexture();
	static Ptr<Texture> getGray2DArrayTexture();
	static int getNumDecals();
	static int getNumDips();
	static int getNumLights();
	static int getNumMaterials();
	static int getNumPrimitives();
	static int getNumProcedurals();
	static int getNumReflections();
	static long long getNumShaders();
	static int getNumShadows();
	static int getNumSurfaces();
	static int getNumTriangles();
	static bool loadSettings(const char *file);
	static bool saveSettings(const char *file);
	static bool loadWorld(const Ptr<Xml> &xml);
	static bool saveWorld(const Ptr<Xml> &xml);
	static bool restoreState(const Ptr<Stream> &stream);
	static bool saveState(const Ptr<Stream> &stream);
	static void destroyCacheTexture(const UGUID & guid);
	static void createCacheTexture(const UGUID & guid);
	static void destroyCacheTextures();
	static void unloadCacheTextures();
	static void createCacheTextures();
	static void loadCacheTextures();
};

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API RenderState
{
protected:
	

public:
	static int isInitialized(); 

	enum
	{
		BUFFER_NONE = 0,
		BUFFER_RED = 1 << 0,
		BUFFER_GREEN = 1 << 1,
		BUFFER_BLUE = 1 << 2,
		BUFFER_ALPHA = 1 << 3,
		BUFFER_DEPTH = 1 << 4,
		BUFFER_STENCIL = 1 << 5,
		BUFFER_COLOR = (BUFFER_RED | BUFFER_GREEN | BUFFER_BLUE | BUFFER_ALPHA),
		BUFFER_DEPTH_STENCIL = (BUFFER_DEPTH | BUFFER_STENCIL),
		BUFFER_ALL = (BUFFER_COLOR | BUFFER_DEPTH_STENCIL),
	};

	enum
	{
		DEPTH_NONE = 0,
		DEPTH_EQUAL,
		DEPTH_LEQUAL,
		DEPTH_GEQUAL,
		DEPTH_ALWAYS,
		DEPTH_NOT_EQUAL,
	};

	enum
	{
		STENCIL_NONE = 0,
		STENCIL_LESS,
		STENCIL_EQUAL,
		STENCIL_LESS_EQUAL,
		STENCIL_GREATER,
		STENCIL_NOT_EQUAL,
		STENCIL_GREATER_EQUAL,
		STENCIL_ALWAYS,
	};

	enum
	{
		STENCIL_KEEP = 0,
		STENCIL_INCR,
		STENCIL_REPLACE,
	};

	enum
	{
		BLEND_NONE = 0,
		BLEND_ZERO,
		BLEND_ONE,
		BLEND_SRC_COLOR,
		BLEND_ONE_MINUS_SRC_COLOR,
		BLEND_SRC_ALPHA,
		BLEND_ONE_MINUS_SRC_ALPHA,
		BLEND_DEST_COLOR,
		BLEND_ONE_MINUS_DEST_COLOR,
		BLEND_DEST_ALPHA,
		BLEND_ONE_MINUS_DEST_ALPHA,
		BLEND_SRC1_COLOR,
		BLEND_ONE_MINUS_SRC1_COLOR,
		BLEND_SRC1_ALPHA,
		BLEND_ONE_MINUS_SRC1_ALPHA,
	};

	enum
	{
		BLEND_OP_ADD = 0,
		BLEND_OP_SUBTRACT,
		BLEND_OP_REVERSE_SUBTRACT,
		BLEND_OP_MIN,
		BLEND_OP_MAX,
	};

	enum
	{
		FRONT_CCW = 0,
		FRONT_CW,
		FRONT_INVERT,
	};

	enum
	{
		CULL_NONE = 0,
		CULL_BACK,
		CULL_FRONT,
	};

	enum
	{
		FILL_SOLID = 0,
		FILL_WIREFRAME,
	};

	enum
	{
		BIND_ALL = 0,
		BIND_FRAGMENT,
	};
	static void clearStates();
	static void clearStructuredBuffers();
	static void clearStructuredBuffer(const Ptr<StructuredBuffer> &buffer);
	static void clearTextures();
	static void clearTexture(const Ptr<Texture> &texture);
	static void clearBuffer(int buffer, const Math::vec4 &color, float depth = 0.0f, int stencil = 0);
	static void dispatch(int group_threads_x, int group_threads_y, int group_threads_z);
	static void saveState();
	static void restoreState();
	static void flushStates();
	static void flushRender();
	static void setViewport(int x, int y, int width, int height);
	static int getWidth();
	static int getHeight();
	static void setScissorTest(float x, float y, float width, float height);
	static void setScissorTest(const Math::vec4 &rectangle);
	static void setScissorTest(const Math::ivec4 &rectangle);
	static int getScissorTest();
	static void setBufferMask(int num, int mask);
	static int getBufferMask(int num);
	static void setDepthFunc(int func);
	static int getDepthFunc();
	static void setStencilFunc(int func, int pass, int ref);
	static int getStencilFunc();
	static int getStencilPass();
	static int getStencilRef();
	static void setBlendFunc(int src, int dest, int blend_op = 0);
	static int getBlendSrcFunc();
	static int getBlendDestFunc();
	static int getBlendOperation();
	static void setBlendFuncBuffer(int num, int src, int dest, int blend_op = 0);
	static int getBlendSrcFuncBuffer(int num);
	static int getBlendDestFuncBuffer(int num);
	static int getBlendOperationBuffer(int num);
	static void setPolygonFront(int front);
	static int getPolygonFront();
	static void setPolygonCull(int cull);
	static int getPolygonCull();
	static void setPolygonFill(int fill);
	static int getPolygonFill();
	static void setPolygonOffset(float bias, float offset);
	static float getPolygonBias();
	static float getPolygonSlope();
	static void setAnisotropy(int anisotropy);
	static int getAnisotropy();
	static void setShader(const Ptr<Shader> &shader);
	static Ptr<Shader> getShader();
	static void setMaterial(const Ptr<Material> &material);
	static Ptr<Material> getMaterial();
	static void setMaterial(Render::PASS pass, const Ptr<Material> &material);
	static void setTexture(int binding, int num, const Ptr<Texture> &texture);
	static void setStructuredBuffer(int num, const Ptr<StructuredBuffer> &buffer);
	static Ptr<Texture> getTexture(int num);
	static Ptr<Texture> getScreenDepthTexture();
	static Ptr<Texture> getScreenColorTexture();
};

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API Renderer
{
protected:
	

public:
	static int isInitialized(); 

	enum
	{
		RENDER_STEREO_DEFAULT = 0,
		RENDER_STEREO_HORIZONTAL,
		RENDER_STEREO_VERTICAL,
	};
	static bool hasGeodeticPivot();
	static bool isNode();
	static bool isReflection();
	static bool isShadow();
	static bool isStereo();
	static int getViewportMask();
	static int getReflectionViewportMask();
	static int getSkipFlags();
	static int checkSkipFlags(int flags);
	static int getStereoMode();
	static Ptr<Viewport> getViewport();
	static void setProjection(const Math::mat4 &projection);
	static Math::mat4 getProjection();
	static void setOldProjection(const Math::mat4 &projection);
	static Math::mat4 getOldProjection();
	static Math::mat4 getProjectionWithoutTAA();
	static void setModelview(const Math::Mat4 & modelview);
	static Math::Mat4 getModelview();
	static Math::Mat4 getIModelview();
	static void setOldModelview(const Math::Mat4 & modelview);
	static Math::Mat4 getOldModelview();
	static void setCameraPosition(const Math::Vec3 & position);
	static Math::Vec3 getCameraPosition();
	static float getZNear();
	static float getZFar();
	static void setObliqueFrustumPlane(const Math::Vec4 & plane);
	static Math::Vec4 getObliqueFrustumPlane();
	static void setObliqueFrustum(bool frustum);
	static bool isObliqueFrustum();
	static bool useVelocityBuffer();
	static bool useTAA();
	static bool useShadows();
	static bool useVisualizer();
	static bool useDynamicReflections();
	static bool usePostEffects();
	static bool useOcclusionQueries();
	static void saveState();
	static void restoreState();
	static void setBufferMask(Render::PASS pass, const Ptr<Material> &material);
	static void setDepthFunc(Render::PASS pass, const Ptr<Material> &material);
	static void setBlendFunc(Render::PASS pass, const Ptr<Material> &material);
	static void setPolygonCull(Render::PASS pass, const Ptr<Material> &material);
	static void setPolygonOffset(Render::PASS pass, const Ptr<Material> &material);
	static void clearShader();
	static void clearStates();
	static void setMaterial(Render::PASS pass, const Ptr<Material> &material);
	static void setShaderParameters(Render::PASS pass, const Ptr<Shader> &shader, const Ptr<Material> &material, const Ptr<Object> &object, int surface, int is_screen_space);
	static void setShaderParameters(Render::PASS pass, const Ptr<Shader> &shader, const Ptr<Material> &material, int is_screen_space);
	static void setShaderParameters(Render::PASS pass, const Ptr<Shader> &shader, int is_screen_space);
	static void setShaderParameters(Render::PASS pass, const Ptr<Material> &material, int is_screen_space);
	static void setShaderParameters(Render::PASS pass, const Ptr<Object> &object, int surface, int is_screen_space);
	static Vector< Ptr<Object> >  getObjects();
	static int getWidth();
	static int getHeight();
	static Ptr<RenderTarget> getRenderTarget();
	static Ptr<RenderTarget> getPostRenderTarget();
	static Ptr<Texture> getTextureColor();
	static Ptr<Texture> getTextureColorOld();
	static Ptr<Texture> getTextureColorOldReprojection();
	static Ptr<Texture> getTextureCurrentDepth();
	static Ptr<Texture> getTextureOpacityDepth();
	static Ptr<Texture> getTextureColorOpacity();
	static Ptr<Texture> getTextureAuxiliary();
	static Ptr<Texture> getTextureRefraction();
	static Ptr<Texture> getTextureRefractionMask();
	static Ptr<Texture> getTextureTransparentBlur();
	static Ptr<Texture> getTextureLights();
	static Ptr<Texture> getTextureBentNormal();
	static Ptr<Texture> getTextureSSAO();
	static Ptr<Texture> getTextureSSGI();
	static Ptr<Texture> getTextureSSR();
	static Ptr<Texture> getTextureSSCurvature();
	static Ptr<Texture> getTextureDOFMask();
	static Ptr<Texture> getTextureAutoExposure();
	static Ptr<Texture> getTextureAutoWhiteBalance();
	static Ptr<Texture> getTextureClouds();
	static Ptr<Texture> getTextureGBufferAlbedo();
	static Ptr<Texture> getTextureGBufferShading();
	static Ptr<Texture> getTextureGBufferNormal();
	static Ptr<Texture> getTextureGBufferMaterialMask();
	static Ptr<Texture> getTextureGBufferLightmap();
	static Ptr<Texture> getTextureGBufferFeatures();
	static Ptr<Texture> getTextureGBufferVelocity();
	static Ptr<Texture> createCustomTexture3D(const char *name, int width, int height, int depth, int format, int flags = 0);
	static Ptr<Texture> createCustomTexture2DArray(const char *name, int width, int height, int depth, int format, int flags = 0);
	static Ptr<Texture> createCustomTexture2D(const char *name, int width, int height, int format, int flags = 0);
	static Ptr<Texture> getCustomTexture(const char *name);
};

//////////////////////////////////////////////////////////////////////////

class UNIGINE_API BakeLighting
{
protected:
	

public:
	static int isInitialized(); 
	static void bakeEnvironmentProbes();
	static void bakeVoxelProbes();
	static void bakeAll();
	static void bake(const Vector< Ptr<Node> > &probes);
	static void stop();
	static bool isBaking();
	static void setVoxelsPerFrame(int frame);
	static int getVoxelsPerFrame();
	static void setBounces(int bounces);
	static int getBounces();
	static void setVoxelSizeMultiplier(float multiplier);
	static float getVoxelSizeMultiplier();
	static float getTimer();
	static Ptr<Light> getCurrentLight();
	static int getCurrentBounce();
	static int getProgressLight();
	static int getProgressBounce();
	static int getProgress();
	static void addReadOnlyTexture(const UGUID & guid);
	static void removeReadOnlyTexture(const UGUID & guid);
};

} // namespace Unigine
