

#pragma once

#include "Common.h"
#include "math.h"

#define		PI			3.14159265358979323846
#define		w(x,y)	( 2*cos(PI/2/x*(2*y+1)) )

void fDCT2( double x[], double* Coeff );
void fDCT4( double x[], double* Coeff );
void fDCT8( double x[], double* Coeff );
void fDCT16( double x[], double* Coeff );
void fDCT32( double x[], double* Coeff );
void fDCT64_1D( double x[], double* Coeff );
void fDCT8_1D( double x[], double* Coeff );

void DCT_float_block( uint8* data, int64* output);