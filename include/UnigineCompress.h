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


#pragma once

#include "UnigineBase.h"

/**
 * Unigine namespace.
 */
namespace Unigine {
	
	/**
	 * Unigine Compress.
	 */
	class Compress {
			
		public:
			
			/**
			 * Returns the maximum compressed buffer size.
			 *
			 * @param size The uncompressed data size.
			 * @return The maximum compressed buffer size.
			 */
			static UNIGINE_API int zlibSize(int size);
			/**
			 * Compress the data.
			 *
			 * @param dest The destination buffer pointer.
			 * @param dest_size The destination buffer size.
			 * @param src The source data pointer.
			 * @param src_size The source data size.
			 * @param quality Compression quality; 0 is for better performance, 1 is for better size.
			 * @return Returns 1 if the operation was a success; otherwise, 0 is returned.
			 */
			static UNIGINE_API int zlibCompress(void *dest,int &dest_size,const void *src,int src_size,int quality);
			/**
			 * Decompress the data.
			 *
			 * @param dest The destination buffer pointer.
			 * @param dest_size The destination buffer size.
			 * @param src The source data pointer.
			 * @param src_size The source data size.
			 * @return Returns 1 if the operation was a success; otherwise, 0 is returned.
			 */
			static UNIGINE_API int zlibDecompress(void *dest,int dest_size,const void *src,int src_size);
	};
	
} /* namespace Unigine */
