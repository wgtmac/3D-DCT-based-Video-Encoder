

#pragma once

#include "Common.h"

#define BITSTREAM_SIZE			16000000
#define  EXPGOLOMB_THRESHOLD 15

#define AC_THRESHOLD  EXPGOLOMB_THRESHOLD
#define DC_THRESHOLD	 EXPGOLOMB_THRESHOLD

#define ABAC_CTX_DC_SIG_COEFF	0
#define ABAC_CTX_DC_LAST_SIG		1
#define ABAC_CTX_DC_ABS				2
#define ABAC_CTX_AC_SIG_COEFF	(ABAC_CTX_DC_ABS+DC_THRESHOLD+2+1)
#define ABAC_CTX_AC_LAST_SIG		(ABAC_CTX_AC_SIG_COEFF+1)
#define ABAC_CTX_AC_ABS				(ABAC_CTX_AC_SIG_COEFF+2)
#define NUM_MODEL	(ABAC_CTX_AC_ABS+AC_THRESHOLD+2+1)

#define MIN(a,b) ( (a)<(b) ? (a) : (b) )

typedef struct
{
	/* state */
	int i_low;
	int i_range;

	/* bit stream */
	int i_queue;
	int i_bytes_outstanding;

	uint8 *p_start;
	uint8 *p;
	uint8 *p_end;

	uint8 state[NUM_MODEL];

} Abac_t;

// Table of the simplified multiplication result of LPS probability and range R
const uint8 Abac_range_lps[64][4];
const uint8 Abac_transition[128][2];
const uint8 Abac_renorm_shift[64];

void Abac_encode_init_core( Abac_t *cb );
void Abac_encode_init( Abac_t *cb , uint8* BitStream );

void Abac_putbyte( Abac_t *cb );
void Abac_encode_renorm( Abac_t *cb ) ;

void Abac_encode_decision( Abac_t *cb, int i_ctx, int b ) ;
void Abac_encode_bypass( Abac_t *cb, int b );
void Abac_encode_terminal( Abac_t *cb )  ;
void Abac_encode_flush(  Abac_t *cb )  ;

size_t Abac_count_bits( Abac_t *cb );

void Abac_GOP_dc(Abac_t* cb, int32 *piCoeff);
void Abac_block_ac(Abac_t* cb, int32 *piCoeff);

void Abac_ScanMode(Abac_t* cb, uint8 mode);

