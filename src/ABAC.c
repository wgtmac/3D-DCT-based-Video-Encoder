


#include "ABAC.h"
#include "Scan.h"
#include "EncoderParam.h"

// Table of the simplified multiplication result of LPS probability and range R
const uint8 Abac_range_lps[64][4] =
{
	{  2,   2,   2,   2}, {  6,   7,   8,   9}, {  6,   7,   9,  10}, {  6,   8,   9,  11},
	{  7,   8,  10,  11}, {  7,   9,  10,  12}, {  7,   9,  11,  12}, {  8,   9,  11,  13},
	{  8,  10,  12,  14}, {  9,  11,  12,  14}, {  9,  11,  13,  15}, { 10,  12,  14,  16},
	{ 10,  12,  15,  17}, { 11,  13,  15,  18}, { 11,  14,  16,  19}, { 12,  14,  17,  20},
	{ 12,  15,  18,  21}, { 13,  16,  19,  22}, { 14,  17,  20,  23}, { 14,  18,  21,  24},
	{ 15,  19,  22,  25}, { 16,  20,  23,  27}, { 17,  21,  25,  28}, { 18,  22,  26,  30},
	{ 19,  23,  27,  31}, { 20,  24,  29,  33}, { 21,  26,  30,  35}, { 22,  27,  32,  37},
	{ 23,  28,  33,  39}, { 24,  30,  35,  41}, { 26,  31,  37,  43}, { 27,  33,  39,  45},
	{ 29,  35,  41,  48}, { 30,  37,  43,  50}, { 32,  39,  46,  53}, { 33,  41,  48,  56},
	{ 35,  43,  51,  59}, { 37,  45,  54,  62}, { 39,  48,  56,  65}, { 41,  50,  59,  69},
	{ 43,  53,  63,  72}, { 46,  56,  66,  76}, { 48,  59,  69,  80}, { 51,  62,  73,  85},
	{ 53,  65,  77,  89}, { 56,  69,  81,  94}, { 59,  72,  86,  99}, { 62,  76,  90, 104},
	{ 66,  80,  95, 110}, { 69,  85, 100, 116}, { 73,  89, 105, 122}, { 77,  94, 111, 128},
	{ 81,  99, 117, 135}, { 85, 104, 123, 142}, { 90, 110, 130, 150}, { 95, 116, 137, 158},
	{100, 122, 144, 166}, {105, 128, 152, 175}, {111, 135, 160, 185}, {116, 142, 169, 195},
	{123, 150, 178, 205}, {128, 158, 187, 216}, {128, 167, 197, 227}, {128, 176, 208, 240}
};

// state transfer table , return new state when one of 128 states receives a symbol 1 / 0 as MPS/LPS
const uint8 Abac_transition[128][2] =          // only  2 to 127 are useful     label 0: LPS probablity = 1   label 1: probablity = 0
{
	{  0,   0}, {  1,   1}, {  2,  50}, { 51,   3}, {  2,  50}, { 51,   3}, {  4,  52}, { 53,   5},
	{  6,  52}, { 53,   7}, {  8,  52}, { 53,   9}, { 10,  54}, { 55,  11}, { 12,  54}, { 55,  13},
	{ 14,  54}, { 55,  15}, { 16,  56}, { 57,  17}, { 18,  56}, { 57,  19}, { 20,  56}, { 57,  21},
	{ 22,  58}, { 59,  23}, { 24,  58}, { 59,  25}, { 26,  60}, { 61,  27}, { 28,  60}, { 61,  29},
	{ 30,  60}, { 61,  31}, { 32,  62}, { 63,  33}, { 34,  62}, { 63,  35}, { 36,  64}, { 65,  37},
	{ 38,  66}, { 67,  39}, { 40,  66}, { 67,  41}, { 42,  66}, { 67,  43}, { 44,  68}, { 69,  45},
	{ 46,  68}, { 69,  47}, { 48,  70}, { 71,  49}, { 50,  72}, { 73,  51}, { 52,  72}, { 73,  53},
	{ 54,  74}, { 75,  55}, { 56,  74}, { 75,  57}, { 58,  76}, { 77,  59}, { 60,  78}, { 79,  61},
	{ 62,  78}, { 79,  63}, { 64,  80}, { 81,  65}, { 66,  82}, { 83,  67}, { 68,  82}, { 83,  69},
	{ 70,  84}, { 85,  71}, { 72,  84}, { 85,  73}, { 74,  88}, { 89,  75}, { 76,  88}, { 89,  77},
	{ 78,  90}, { 91,  79}, { 80,  90}, { 91,  81}, { 82,  94}, { 95,  83}, { 84,  94}, { 95,  85},
	{ 86,  96}, { 97,  87}, { 88,  96}, { 97,  89}, { 90, 100}, {101,  91}, { 92, 100}, {101,  93},
	{ 94, 102}, {103,  95}, { 96, 104}, {105,  97}, { 98, 104}, {105,  99}, {100, 108}, {109, 101},
	{102, 108}, {109, 103}, {104, 110}, {111, 105}, {106, 112}, {113, 107}, {108, 114}, {115, 109},
	{110, 116}, {117, 111}, {112, 118}, {119, 113}, {114, 118}, {119, 115}, {116, 122}, {123, 117},
	{118, 122}, {123, 119}, {120, 124}, {125, 121}, {122, 126}, {127, 123}, {124, 127}, {126, 125}
};

const uint8 Abac_renorm_shift[64] =
{
	6,5,4,4,3,3,3,3,2,2,2,2,2,2,2,2,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

void Abac_encode_init_core( Abac_t *cb )     // initialize cabac encoder
{
	int state = 63;
	int i;
	/*
	int j ;
	for( j = 0; j < NUM_MODEL; j++ )
		cb->state[j] = (MIN( state, 127-state ) << 1) | (state >> 6);    // state storage = 2 4 6 ... 126 | 127 125 123 ... 5 3
	*/

	cb->state[ABAC_CTX_AC_SIG_COEFF] = (MIN( (4), 127-(4) ) << 1) | ((4) >> 6);    // state storage = 2 4 6 ... 126 | 127 125 123 ... 5 3
	cb->state[ABAC_CTX_AC_LAST_SIG] = (MIN( state, 127-state ) << 1) | (state >> 6);    // state storage = 2 4 6 ... 126 | 127 125 123 ... 5 3

	cb->state[ABAC_CTX_DC_SIG_COEFF] = (MIN( (4), 127-(4) ) << 1) | ((4) >> 6);    // state storage = 2 4 6 ... 126 | 127 125 123 ... 5 3
	cb->state[ABAC_CTX_DC_LAST_SIG] = (MIN( state, 127-state ) << 1) | (state >> 6);    // state storage = 2 4 6 ... 126 | 127 125 123 ... 5 3

	for(i=0;i<( AC_THRESHOLD+3 ); i++)
	{
		cb->state[ABAC_CTX_AC_ABS+i] = (MIN( state, 127-state ) << 1) | (state >> 6); 
	}

	for(i=0;i<( DC_THRESHOLD+3 ); i++)
	{
		cb->state[ABAC_CTX_DC_ABS+i] = (MIN( state, 127-state ) << 1) | (state >> 6); 
	}

	cb->i_low   = 0;
	cb->i_range = 0x01FE;
	cb->i_queue = -9; // the first bit will be shifted away and not written
	cb->i_bytes_outstanding = 0;
}

void Abac_encode_init( Abac_t *cb , uint8* BitStream )    // initialize cabac bitstream
{
	Abac_encode_init_core(cb);
	cb->p_start = BitStream;
	cb->p       = cb->p_start;
	cb->p_end   = cb->p_start + BITSTREAM_SIZE;
}


void Abac_putbyte( Abac_t *cb )
{
	if( cb->i_queue >= 0 )    // if i_queue below 0 , that means the cabac bitstream is not meet with a byte
	{
		int out = cb->i_low >> (cb->i_queue+10);           	// last 10 bits of i_low is not for writing out
		cb->i_low &= (0x400<<cb->i_queue)-1;		// make the writen bits to be 0 , i_queue stands for how many bits before last 10 bits are not for writing out
		cb->i_queue -= 8;

		if( (out & 0xff) == 0xff )
			cb->i_bytes_outstanding++;
		else
		{
			int carry = out >> 8;
			int bytes_outstanding = cb->i_bytes_outstanding;

			cb->p[-1] += carry;        // first 2 bits of total 10 bits to be added in the stream
			while( bytes_outstanding > 0 )          // carry = 0 / 1
			{
				*(cb->p++) = carry-1;     // 255 or 0
				bytes_outstanding--;
			}
			*(cb->p++) = out;
			cb->i_bytes_outstanding = 0;
		}
	}
}

void Abac_encode_renorm( Abac_t *cb )         // has no asm version
{
	int shift = Abac_renorm_shift[cb->i_range>>3];
	cb->i_range <<= shift;    // make sure i_range is upon 0x100
	cb->i_low   <<= shift;
	cb->i_queue  += shift;     // we can see the default value of every bit is 0
	Abac_putbyte( cb );
}

void Abac_encode_decision( Abac_t *cb, int i_ctx, int b )    // b is input symbol
{
	int i_state = cb->state[i_ctx];
	int i_range_lps = Abac_range_lps[i_state>>1][(cb->i_range>>6)-4];  // i_state>>1 = 0 - 62   and 63 is never used     range is always upon 256
	cb->i_range -= i_range_lps;
	if( b != (i_state & 1) )
	{
		cb->i_low += cb->i_range;
		cb->i_range = i_range_lps;
	}
	cb->state[i_ctx] = Abac_transition[i_state][b];   // i_state usually equals 2 to 127
	Abac_encode_renorm( cb );
}

void Abac_encode_bypass( Abac_t *cb, int b )
{
	cb->i_low <<= 1;
	cb->i_low += b & cb->i_range;
	cb->i_queue += 1;
	Abac_putbyte( cb );
}

void Abac_encode_terminal( Abac_t *cb )         // block end
{
	cb->i_range -= 2;
	Abac_encode_renorm( cb );
}

void Abac_encode_flush(  Abac_t *cb )			// GOP end
{
	cb->i_low += cb->i_range - 2;
	cb->i_low |= 1;          // last bit set value = 1
	cb->i_low <<= 9;      // push first 9 bits to be written
	cb->i_queue += 9;
	Abac_putbyte( cb );
	Abac_putbyte( cb );
	cb->i_low <<= -cb->i_queue;     // in order to let unwritten bits to be written out (because i_queue<0)   |||  now the first bit of last 10 bits is 1 === the last bit
	cb->i_low |= 0 /* (0x35a4e4f5 >> (h->i_frame & 31) & 1) << 10*/ ; 
	cb->i_queue = 0;
	Abac_putbyte( cb );          // make all left bits be written

	while( cb->i_bytes_outstanding > 0 )         // in x264_cabac_putbyte( cb ) make this !=0 , so write this
	{
		*(cb->p++) = 0xff;
		cb->i_bytes_outstanding--;
	}
}

size_t Abac_count_bits( Abac_t *cb )
{
	return (cb->p - cb->p_start) ;
}

void Abac_GOP_dc(Abac_t* cb, int32 *piCoeff)
{
	unsigned short uiNum = glbEncoderParam.codedHeight*glbEncoderParam.codedWidth/(BLOCK_SIZE_X*BLOCK_SIZE_Y);			// GOP中系数个数
	unsigned short ui;
	unsigned short uiNumSig = 0;
	unsigned short uiCodedSig = 0;
	unsigned short uiSymbol ;
	unsigned short uiCount;
	uint8 bNoExGo ;
	unsigned short  uiAbs, uiSign, uiLast;
	int32   iCoeff;
	uint8 uiSig ;

	for( ui = 0; ui < uiNum; ui++ )
	{  
		if( piCoeff[ ui ] )    
		{
			uiNumSig++;
		}
	}

	//----- encode significance map -----
	for( ui = 0; ui < uiNum; ui++ ) // if last coeff is reached, it has to be significant
	{
		uiSig = piCoeff[ ui ] ? 1 : 0;
		Abac_encode_decision( cb, ABAC_CTX_DC_SIG_COEFF, uiSig );			// 按位置

		if( uiSig )
		{
			uiLast = (++uiCodedSig == uiNumSig ? 1 : 0);
			Abac_encode_decision( cb, ABAC_CTX_DC_LAST_SIG , uiLast) ;		// 按位置
			if( uiLast)
			{
				break;
			}
		}
	}

	//int   c1 = 1;
	//int   c2 = 0;
	//----- encode significant coefficients -----
	ui++;
	while( (ui--) != 0 )
	{
		iCoeff = piCoeff[ui];

		if( iCoeff )
		{
			if( iCoeff > 0) { uiAbs = (unsigned short)( iCoeff);  uiSign = 0; }
			else            { uiAbs = (unsigned short)(-iCoeff);  uiSign = 1; }


			uiSymbol = uiAbs > 1 ? 1 : 0;
			Abac_encode_decision(cb, ABAC_CTX_DC_ABS , uiSymbol );

			if( uiSymbol )
			{
				/* uiCtx  = MIN (c2,4);*/
				uiAbs -= 2;
				//c1     = 0;
				//c2++;
				{
					if( uiAbs )
					{
						uiSymbol = uiAbs;
						Abac_encode_decision( cb, ABAC_CTX_DC_ABS+1, 1 );
						uiCount = 0;
						bNoExGo = (uiSymbol < DC_THRESHOLD/*13*/);

						while( --uiSymbol && ++uiCount <DC_THRESHOLD/* 13*/ )
						{
							Abac_encode_decision( cb, ABAC_CTX_DC_ABS+1+uiCount , 1 );
						}
						if( bNoExGo )
						{
							Abac_encode_decision( cb, ABAC_CTX_DC_ABS+1+DC_THRESHOLD, 0 );
						}
						else
						{
							uiCount = 0 ;
							while( uiSymbol >= (unsigned short)(1<<uiCount) )
							{
								Abac_encode_bypass( cb, 1 );
								uiSymbol -= 1<<uiCount;
								uiCount  ++;
							}
							Abac_encode_bypass( cb, 0 );
							while( uiCount-- )
							{
								Abac_encode_bypass( cb, (uiSymbol>>uiCount) & 1 );
							}
						}
					}
					else
					{
						Abac_encode_decision( cb, ABAC_CTX_DC_ABS+2+DC_THRESHOLD , 0 );
					}
				}
			}
			//else if( c1 )
			//{
			//  c1++;
			//}
			Abac_encode_bypass( cb, uiSign );
		}
	}


}

void Abac_block_ac(Abac_t* cb, int32 *piCoeff )
{
	unsigned short uiNum = BLOCK_SIZE_BYTE - 1;			// AC coeff numbers in a 64x64x8 block
	unsigned short ui;
	unsigned short uiNumSig = 0;
	unsigned short uiCodedSig = 0;
	unsigned short uiSymbol ;
	unsigned short uiCount;
	uint8 bNoExGo ;
	unsigned short  uiAbs, uiSign, uiLast;
	int32   iCoeff;
	uint8 uiSig ;

	for( ui = 0; ui < uiNum; ui++ )
	{  
		if( piCoeff[ ui ] )    
		{
			uiNumSig++;
		}
	}

	//----- encode significance map -----
	for( ui = 0; ui < uiNum; ui++ ) // if last coeff is reached, it has to be significant
	{
		uiSig = piCoeff[ ui ] ? 1 : 0;
		Abac_encode_decision( cb, ABAC_CTX_AC_SIG_COEFF, uiSig );			// 按位置

		if( uiSig )
		{
			uiLast = (++uiCodedSig == uiNumSig ? 1 : 0);
			Abac_encode_decision( cb, ABAC_CTX_AC_LAST_SIG , uiLast) ;		// 按位置
			if( uiLast)
			{
				break;
			}
		}
	}

	//int   c1 = 1;
	//int   c2 = 0;
	//----- encode significant coefficients -----
	ui++;
	while( (ui--) != 0 )
	{
		iCoeff = piCoeff[ui];

		if( iCoeff )
		{
			if( iCoeff > 0) { uiAbs = (unsigned short)( iCoeff);  uiSign = 0; }
			else            { uiAbs = (unsigned short)(-iCoeff);  uiSign = 1; }


			uiSymbol = uiAbs > 1 ? 1 : 0;
			Abac_encode_decision(cb, ABAC_CTX_AC_ABS , uiSymbol );

			if( uiSymbol )
			{
				/* uiCtx  = MIN (c2,4);*/
				uiAbs -= 2;
				//c1     = 0;
				//c2++;
				{
					if( uiAbs )
					{
						uiSymbol = uiAbs;
						Abac_encode_decision( cb, ABAC_CTX_AC_ABS+1, 1 );
						uiCount = 0;
						bNoExGo = (uiSymbol < AC_THRESHOLD/*13*/);

						while( --uiSymbol && ++uiCount <AC_THRESHOLD/* 13*/ )
						{
							Abac_encode_decision( cb, ABAC_CTX_AC_ABS+1+uiCount , 1 );
						}
						if( bNoExGo )
						{
							Abac_encode_decision( cb, ABAC_CTX_AC_ABS+1+AC_THRESHOLD, 0 );
						}
						else
						{
							uiCount = 0 ;
							while( uiSymbol >= (unsigned short)(1<<uiCount) )
							{
								Abac_encode_bypass( cb, 1 );
								uiSymbol -= 1<<uiCount;
								uiCount  ++;
							}
							Abac_encode_bypass( cb, 0 );
							while( uiCount-- )
							{
								Abac_encode_bypass( cb, (uiSymbol>>uiCount) & 1 );
							}
						}
					}
					else
					{
						Abac_encode_decision( cb, ABAC_CTX_AC_ABS+2+AC_THRESHOLD , 0 );
					}
				}
			}
			//else if( c1 )
			//{
			//  c1++;
			//}
			Abac_encode_bypass( cb, uiSign );
		}
	}

}

void Abac_ScanMode(Abac_t* cb, uint8 mode)
{
	switch(mode)
	{
	case MODE_1:
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 0 );
		break;
	case MODE_2:
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 1 );
		break;
	case MODE_3:
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 0 );
		break;
	case MODE_4:
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 1 );
		break;
	case MODE_5:
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 0 );
		break;
	case MODE_6:
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 0 );
		Abac_encode_bypass( cb, 1 );
		break;
	case MODE_7:
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 0 );
		break;
	case MODE_8:
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 1 );
		Abac_encode_bypass( cb, 1 );
		break;
	default:
		printf("[error]: Scan mode is out of range!\n");
		exit(-1);
	}
}
