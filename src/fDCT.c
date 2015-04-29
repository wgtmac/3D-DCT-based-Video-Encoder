
#include "fDCT.h"

void fDCT2( double x[], double* Coeff )
{
	Coeff[0] = x[0] + x[1];
	Coeff[1] = (x[0] - x[1]) * w(2,0) * 1/2 ;
}

void fDCT4( double x[], double* Coeff )
{
#define N 4
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	
	fDCT2( oddX, &adCoeff[0] );
	fDCT2( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

#undef N
}
void fDCT8( double x[], double* Coeff )
{
#define N 8
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	fDCT4( oddX, &adCoeff[0] );
	fDCT4( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

#undef N
}
void fDCT16( double x[], double* Coeff )
{
#define N 16
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	fDCT8( oddX, &adCoeff[0] );
	fDCT8( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

#undef N
}

void fDCT32( double x[], double* Coeff )
{
#define N 32
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	fDCT16( oddX, &adCoeff[0] );
	fDCT16( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

#undef N
}

void fDCT64_1D( double x[], double* Coeff )
{
#define N 64
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];
	double para = sqrt(2.0/N);

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	fDCT32( oddX, &adCoeff[0] );
	fDCT32( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

	// ÐÞÕý
	for(i=1; i!=N; i++)
		Coeff[i] *= para;
	Coeff[0] *= sqrt(1.0/N);

#undef N
}

void fDCT8_1D( double x[], double* Coeff )
{
#define N 8
	double oddX[N/2], evenX[N/2];
	int i;
	double adCoeff[N];
	double para = sqrt(2.0/N);

	for(i=0; i!=N/2; i++)
	{
		oddX[i]  = x[i] + x[N-1-i] ;
		evenX[i] = (x[i] - x[N-1-i]) * w(N,i) ;
	}

	fDCT4( oddX, &adCoeff[0] );
	fDCT4( evenX,&adCoeff[N/2] );

	for(i=0; i!=N/2; i++)
	{
		Coeff[2*i] = adCoeff[i];
		Coeff[2*i+1] = (i==0)? adCoeff[N/2+i]/2 : ( adCoeff[N/2+i] - Coeff[2*(i-1)+1] ) ;
	}

	for(i=1; i!=N; i++)
		Coeff[i] *= para;
	Coeff[0] *= sqrt(1.0/N);

#undef N
}


void DCT_float_block( uint8* data, int64* output)
{
	size_t i,j,k;
	double* inData = (double*) malloc( BLOCK_SIZE_BYTE*sizeof(double) );
	double* Coeff = (double*) malloc( BLOCK_SIZE_BYTE*sizeof(double) );
	double  iTemp[64];

	// uint8=>int64  left shift
	for(i=0; i!=32768 ; i++)		// 64x64x8
	{
		inData[i] = (double)data[i] ;
	}

	// 64-point horizontal ( 64x8 )
	for(i=0; i!=512; i++)
		fDCT64_1D(inData+64*i, Coeff+64*i);

	// 64-point vertical ( 64x8 )
	for (i=0; i!=8; i++)					// frame
	{
		for(j=0; j!=64; j++)				// x
		{
			for (k=0; k!=64; k++)		// y
			{
				iTemp[k] = Coeff[i*4096 + j + k*64];
			}

			fDCT64_1D(iTemp, iTemp);

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

			fDCT8_1D( iTemp, iTemp );

			for (k=0; k!=8; k++)
			{
				Coeff[k*4096 + i + j*64] = iTemp[k] ;
			}

		}
	}

	for(i=0; i!=32768 ; i++)		// 64x64x8
	{
		output[i] = (int64)(floor(Coeff[i]+0.5)) ;
	}

	free(inData);
	free(Coeff);

}