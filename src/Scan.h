/*
 *
 *	
 *
 *
 *
 */


#pragma once


#include "common.h"

enum
{
	MODE_1,
	MODE_2,
	MODE_3,
	MODE_4,
	MODE_5,
	MODE_6,
	MODE_7,
	MODE_8,
	MODE_MAX
};

extern const uint16 glbScanTable[MODE_MAX][BLOCK_SIZE_BYTE];

uint8 Scan_ModeDecision( int32* coeff );
void  Scan_Sort( int32* coeff, uint8 mode );