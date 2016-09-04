/*
* MIT License
* 
* Copyright (c) 2016 Keith J. Cancel
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
/**
* @file crc32.h
* @author  Keith Cancel <admin@keith.pro>
* @version 1.0
*
* This utility library helps calculate CRC32 checksums. I wrote to it to
* calculate the crc32 checks for the PNG standard.  
*/
#include <stdint.h>
#include <stdbool.h>

#pragma once

#ifndef KC_CRC32_H
/**
* crc32.h inclusion gaurd.
*/
#define KC_CRC32_H 1
    
//forward declaration
struct plat_crc32_lut;
/**
* This struct stores look up tables for a polynomial when calculating the
* CRC-32. You can use create_crc32_lut to make new a instance.
*
* @see create_crc32_lut
* @see destory_crc32_lut
*/
typedef struct plat_crc32_lut crc32_lut;
/**
* This struct defines compile time look up tables of polynomials for convience,
* and performance.
*
* @see crc32_luts
*/
typedef struct {
	/**
	* This is a compile time look up table for the polynomial: '0xedb88320'.
	* IEEE refers to IEEE 802.3. This is probably the most common polynomial
	* used for CRC-32. It's used for PNG, Serial ATA, ZIP, Ethernet, MPEG-2, and ect.
	*/
	const crc32_lut IEEE;//
	//polynomials with better dectection than IEEE
	/**
	* This is a compile time look up table for the polynomial: '0x82f63b78'.
	* The polynomial has better error detection than IEEE, and is also fairly
	* common.
	*/
	const crc32_lut Castagnoli;
	/**
	* This is a compile time look up table for the polynomial: '0xeb31d82e'.
	* Koopman {1,3,28}/CRC-32K has better error detection than IEEE. It was
	* derived by Philip Koopman who has extensively studied the properties of
	* CRC polynomials.
	*/
	const crc32_lut Koopman;
	/**
	* This is a compile time look up table for the polynomial: '0x973afb51'.
	* Another polynomial from Philip Koopman's website on the topic. This has a
	* hamming distance of 18.
	* https://users.ece.cmu.edu/~koopman/crc/index.html
	*/
	const crc32_lut Koopman_hd18;
} crc32_default_luts;

/**
* This constant variable has some helpful look up tables defined. You can use
* the look up tables here to calclate a CRC-32. 
*
* @see crc32_default_luts
*/
extern const crc32_default_luts crc32_luts;
/**
*
* This function creates a look up table for a custom polynomial. Please 
* ensure to ensure to destroy the lut when done!
* 
* @see destory_crc32_lut
* 
* @param polynomial The polynomial to generate a look up table for.
* @return Returns an instance of the crc32_lut to use for calculating CRC-32/s.
*/
crc32_lut* create_crc32_lut(uint32_t polynomial);
/**
*
* This function frees an existings look up tables's resources. Call once for
* any instance of crc32_luts your created.
* 
* @see create_crc32_lut
* 
* @param lut The crc32 lut instance we wish to free.
* @return Returns a bool. true for sucess, and false for failure.
*/
bool destory_crc32_lut(crc32_lut *lut);
/**
*
* This function creates a look up table for a custom polynomial. Please 
* ensure to call destory  when done!
* 
* @param lut A lookup table to calculate the CRC-32 checksum with.
* @param data The data we wish to calculate the CRC-32 of.
* @param length The length of the data.
* @param previous_crc32 A previous CRC-32 to use. This will normally be Zero,
* but if you are working on a stream of data it can be quite helpful.
* @return Returns the calculated CRC-32 check sum as a uint32_t.
*/
uint32_t calculate_crc32(
	const crc32_lut * lut,
	const void * data,
	size_t length,
	uint32_t previous_crc32
);
#endif /*KC_CRC32_H*/