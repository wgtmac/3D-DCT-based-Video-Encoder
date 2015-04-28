


#pragma once

#include "DctDef.h"
#include "Common.h"
#include <math.h>


void DCT_dct2( int64* x );
void DCT_dct4( int64* x );
void DCT_dct8( int64* x );
void DCT_dct16( int64* x );
void DCT_dct32( int64* x );
void DCT_dct64_1D( int64* x );
void DCT_dct8_1D( int64* x );

void DCT_block( uint8* data, int64* output);