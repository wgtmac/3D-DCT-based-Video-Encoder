

#include "DCT.h"



void DCT_dct2( int64* x )
{
	int64 temp;
	int64 Coeff[2];

	Coeff[0] = x[0] + x[1] ;
	temp = x[0] - x[1];		Coeff[1] =  (EXP_1  + EXP_DIV4  + EXP_DIV8)>>1  ;		// 1.414

	x[0] = Coeff[0];
	x[1] = Coeff[1];
}

void DCT_dct4( int64* x )
{
#define N 4
	int64 oddX[N/2], evenX[N/2];
	int64 temp;

	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[3]);		evenX[0] = EXP_2  - EXP_DIV8  ;
	temp = (x[1] - x[2]);		evenX[1] = EXP_1  - EXP_DIV8  - EXP_DIV16  ; 

	DCT_dct2( oddX );
	DCT_dct2( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

#undef N
}

void DCT_dct8( int64* x )
{
#define N 8
	int64 oddX[N/2], evenX[N/2];
	int64 temp;
	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[7]);		evenX[0] = EXP_4 - EXP_DIV16  ;
	temp = (x[1] - x[6]);		evenX[1] = EXP_3  + EXP_DIV4  + EXP_DIV16  ;
	temp = (x[2] - x[5]);		evenX[2] = EXP_2 + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[3] - x[4]);		evenX[3] = EXP_1 - EXP_DIV8  - EXP_DIV16  ;

	DCT_dct4( oddX );
	DCT_dct4( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		evenX[i] >>= 1;
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

#undef N
}
void DCT_dct16( int64* x )
{
#define N 16
	int64 oddX[N/2], evenX[N/2];
	int64 temp;
	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[15]);		evenX[0] = EXP_8 ;
	temp = (x[1] - x[14]);		evenX[1] = EXP_8  - EXP_DIV4  - EXP_DIV16  ;
	temp = (x[2] - x[13]);		evenX[2] = EXP_7 ;
	temp = (x[3] - x[12]);		evenX[3] = EXP_6 + EXP_DIV8  ;
	temp = (x[4] - x[11]);		evenX[4] = EXP_5 + EXP_DIV16  ;
	temp = (x[5] - x[10]);		evenX[5] = EXP_4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[6] - x[9]);		evenX[6] = EXP_2  + EXP_DIV4  + EXP_DIV16  ;
	temp = (x[7] - x[8]);		evenX[7] = EXP_1 - EXP_DIV8  - EXP_DIV16  ;

	DCT_dct8( oddX );
	DCT_dct8( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		evenX[i] >>= 2;
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

#undef N
}

void DCT_dct32( int64* x )
{
#define N 32
	int64 oddX[N/2], evenX[N/2];
	int64 temp;
	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[31]);		evenX[0] = EXP_16 ;
	temp = (x[1] - x[30]);		evenX[1] = EXP_16 - EXP_DIV8  ;
	temp = (x[2] - x[29]);		evenX[2] = EXP_16  - EXP_DIV4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[3] - x[28]);		evenX[3] = EXP_15 + EXP_DIV16  ;
	temp = (x[4] - x[27]);		evenX[4] = EXP_14  + EXP_DIV4  + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[5] - x[26]);		evenX[5] = EXP_14 - EXP_DIV4  ;
	temp = (x[6] - x[25]);		evenX[6] = EXP_13 - EXP_DIV8  ;
	temp = (x[7] - x[24]);		evenX[7] = EXP_12 - EXP_DIV8  ;
	temp = (x[8] - x[23]);		evenX[8] = EXP_11 - EXP_DIV4  ;
	temp = (x[9] - x[22]);		evenX[9] = EXP_10  - EXP_DIV4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[10] - x[21]);		evenX[10] = EXP_8  + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[11] - x[20]);		evenX[11] = EXP_7  - EXP_DIV8  ;
	temp = (x[12] - x[19]);		evenX[12] = EXP_5 + EXP_DIV4  + EXP_DIV8  ;
	temp = (x[13] - x[18]);		evenX[13] = EXP_4 - EXP_DIV16  ;
	temp = (x[14] - x[17]);		evenX[14] = EXP_2 + EXP_DIV4  + EXP_DIV16  ;
	temp = (x[15] - x[16]);		evenX[15] = EXP_1  - EXP_DIV8  - EXP_DIV16  ;

	DCT_dct16( oddX );
	DCT_dct16( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		evenX[i] >>= 3;
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

#undef N
}

void DCT_dct64_1D( int64* x )
{
#define N 64

	int64 oddX[N/2], evenX[N/2];
	int64 temp;
	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[63]);		evenX[0] = EXP_32       ;
	temp = (x[1] - x[62]);		evenX[1] = EXP_32  - EXP_DIV16  ;
	temp = (x[2] - x[61]);		evenX[2] = EXP_32  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[3] - x[60]);		evenX[3] = EXP_32  - EXP_DIV4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[4] - x[59]);		evenX[4] = EXP_31   + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[5] - x[58]);		evenX[5] = EXP_31  - EXP_DIV8  ;
	temp = (x[6] - x[57]);		evenX[6] = EXP_30  + EXP_DIV4  + EXP_DIV8  ;
	temp = (x[7] - x[56]);		evenX[7] = EXP_30 - EXP_DIV8  ;
	temp = (x[8] - x[55]);		evenX[8] = EXP_29 + EXP_DIV4  ;
	temp = (x[9] - x[54]);		evenX[9] = EXP_29  - EXP_DIV4  - EXP_DIV8  ;
	temp = (x[10] - x[53]);		evenX[10] = EXP_28 - EXP_DIV8  ;
	temp = (x[11] - x[52]);		evenX[11] = EXP_27  ;	
	temp = (x[12] - x[51]);		evenX[12] = EXP_26 + EXP_DIV8  ;
	temp = (x[13] - x[50]);		evenX[13] = EXP_25 + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[14] - x[49]);		evenX[14] = EXP_24 + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[15] - x[48]);		evenX[15] = EXP_23 + EXP_DIV8  ;
	temp = (x[16] - x[47]);		evenX[16] = EXP_22+ EXP_DIV16  ;
	temp = (x[17] - x[46]);		evenX[17] = EXP_21- EXP_DIV16  ;
	temp = (x[18] - x[45]);		evenX[18] = EXP_20- EXP_DIV4  - EXP_DIV16  ;
	temp = (x[19] - x[44]);		evenX[19] = EXP_18+ EXP_DIV4  + EXP_DIV8  ;
	temp = (x[20] - x[43]);		evenX[20] = EXP_17+ EXP_DIV16  ;
	temp = (x[21] - x[42]);		evenX[21] = EXP_16- EXP_DIV8  - EXP_DIV16  ;
	temp = (x[22] - x[41]);		evenX[22] = EXP_14  + EXP_DIV4  + EXP_DIV8  ;
	temp = (x[23] - x[40]);		evenX[23] = EXP_13 ;
	temp = (x[24] - x[39]);		evenX[24] = EXP_12 - EXP_DIV4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[25] - x[38]);		evenX[25] = EXP_10 ;
	temp = (x[26] - x[37]);		evenX[26] = EXP_9  - EXP_DIV4  - EXP_DIV8  - EXP_DIV16  ;
	temp = (x[27] - x[36]);		evenX[27] = EXP_7  ;
	temp = (x[28] - x[35]);		evenX[28] = EXP_5 + EXP_DIV4  + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[29] - x[34]);		evenX[29] = EXP_4 - EXP_DIV16  ;
	temp = (x[30] - x[33]);		evenX[30] = EXP_2 + EXP_DIV4  + EXP_DIV16  ;
	temp = (x[31] - x[32]);		evenX[31] = EXP_1 - EXP_DIV8  - EXP_DIV16  ;

	DCT_dct32( oddX );
	DCT_dct32( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		evenX[i] >>= 4;
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

	x[0] = (x[0]>>3) ;
	for (i=1; i!=N; i++)
	{
		x[i] =  (x[i]>>3) + (x[i]>>4) - (x[i]>>6) + (x[i]>>8);
	}

#undef N
}


void DCT_dct8_1D( int64* x )
{
#define N 8
	int64 oddX[N/2], evenX[N/2];
	int64 temp;

	size_t i;

	for(i=0; i!=N/2; i++)
		oddX[i]  = x[i] + x[N-1-i] ;

	temp = (x[0] - x[7]);		evenX[0] = EXP_4 - EXP_DIV16  ;
	temp = (x[1] - x[6]);		evenX[1] = EXP_3  + EXP_DIV4  + EXP_DIV16  ;
	temp = (x[2] - x[5]);		evenX[2] = EXP_2 + EXP_DIV8  + EXP_DIV16  ;
	temp = (x[3] - x[4]);		evenX[3] = EXP_1 - EXP_DIV8  - EXP_DIV16  ;

	DCT_dct4( oddX );
	DCT_dct4( evenX );

	for(i=0; i!=N/2; i++)
	{
		x[2*i] = oddX[i];
		evenX[i] >>= 1;
		x[2*i+1] = (i==0)? (evenX[i]>>1) : ( evenX[i] - x[2*(i-1)+1] ) ;
	}

	x[0] = (x[0]>>2) + (x[0]>>3) - (x[0]>>6) - (x[0]>>8) - (x[0]>>9) ;
	for (i=1; i!=N; i++)
	{
		x[i] >>= 1;
	}

#undef N
}

void DCT_block( uint8* data, int64* output)
{
	size_t i,j,k;
	int64* Coeff = output;
	int64  iTemp[64];

	// uint8=>int64  left shift
	for(i=0; i!=32768 ; i++)		// 64x64x8
	{
		Coeff[i] = data[i] ;
		Coeff[i] <<= 6 ;
	}

	// 64-point horizontal ( 64x8 )
	for(i=0; i!=512; i++)
		DCT_dct64_1D(Coeff+64*i);

	// 64-point vertical ( 64x8 )
	for (i=0; i!=8; i++)					// frame
	{
		for(j=0; j!=64; j++)				// x
		{
			for (k=0; k!=64; k++)		// y
			{
				iTemp[k] = Coeff[i*4096 + j + k*64];
			}

			DCT_dct64_1D(iTemp);

			for (k=0; k!=64; k++)
			{
				Coeff[i*4096 + j + k*64] = iTemp[k] ;
			}
		}
	}

	// 8-point (64x64)
	for (i=0; i!=64; i++)					// x
	{
		for (j=0; j!=64; j++)				// y
		{
			for (k=0; k!=8; k++)			// frame
			{
				iTemp[k] = Coeff[k*4096 + i + j*64] ;
			}

			DCT_dct8_1D( iTemp );

			for (k=0; k!=8; k++)
			{
				Coeff[k*4096 + i + j*64] = iTemp[k] ;
			}

		}
	}

	for(i=0; i!=32768 ; i++)		// 64x64x8
	{
		Coeff[i] >>= 6 ;
	}

}