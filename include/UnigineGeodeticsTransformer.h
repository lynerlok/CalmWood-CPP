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


#pragma once

#include <UnigineBase.h>
#include <UnigineMathLib.h>
#include <UnigineString.h>

namespace Unigine
{

class GeodeticsTransformer
{
public:
	virtual ~GeodeticsTransformer() {}

public:
	static UNIGINE_API GeodeticsTransformer *get();

public:
	virtual Math::dmat4 geodeticToWorld(const Math::dvec3 &geo_coords) = 0;
	virtual Math::dvec3 worldToGeodetic(const Math::dvec3 & world_pos) = 0;
	virtual int setProjectionWkt(const char *projection_cs_wkt_string, const Unigine::Math::dvec3 &world_origin_geo_coords,
		const char *geodetic_cs_string = "WGS84", int geodetic_cs_is_well_known = 1) = 0;
	virtual int setProjectionEpsg(int projection_cs_epsg_code, const Unigine::Math::dvec3 &world_origin_geo_coords,
		const char *geodetic_cs_string = "WGS84", int geodetic_cs_is_well_known = 1) = 0;
};

} //namespace Unigine
