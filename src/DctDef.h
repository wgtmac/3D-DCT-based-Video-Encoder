

#pragma once

#define EXP_41		( temp<<5 ) + ( temp<<3 ) + ( temp )
#define EXP_40		( temp<<5 ) + ( temp<<3 )
#define EXP_39		( temp<<5 ) + ( temp<<2 ) + ( temp<<1 ) + ( temp )
#define EXP_38		( temp<<5 ) + ( temp<<2 ) + ( temp<<1 )
#define EXP_37		( temp<<5 ) + ( temp<<2 ) + ( temp )
#define EXP_36		( temp<<5 ) + ( temp<<2 )
#define EXP_35		( temp<<5 ) + ( temp<<1 ) + ( temp )
#define EXP_34		( temp<<5 ) + ( temp<<1 )
#define EXP_33		( temp<<5 ) + ( temp )
#define EXP_32		( temp<<5 )
#define EXP_31		( temp<<4 ) + ( temp<<3 ) + ( temp<<2 ) + ( temp<<1 ) +( temp )
#define EXP_30		( temp<<4 ) + ( temp<<3 ) + ( temp<<2 ) + ( temp<<1 )
#define EXP_29		( temp<<4 ) + ( temp<<3 ) + ( temp<<2 ) + ( temp )
#define EXP_28		( temp<<4 ) + ( temp<<3 ) + ( temp<<2 )
#define EXP_27		( temp<<4 ) + ( temp<<3 ) + ( temp<<1 ) + ( temp )
#define EXP_26		( temp<<4 ) + ( temp<<3 ) + ( temp<<1 )
#define EXP_25		( temp<<4 ) + ( temp<<3 ) + ( temp )
#define EXP_24		( temp<<4 ) + ( temp<<3 )
#define EXP_23		( temp<<4 ) + ( temp<<2 ) + ( temp<<1 ) + ( temp )
#define EXP_22		( temp<<4 ) + ( temp<<2 ) + ( temp<<1 )
#define EXP_21		( temp<<4 ) + ( temp<<2 ) + ( temp )
#define EXP_20		( temp<<4 ) + ( temp<<2 )
#define EXP_19		( temp<<4 ) + ( temp<<1 ) + ( temp )
#define EXP_18		( temp<<4 ) + ( temp<<1 )
#define EXP_17		( temp<<4 ) + ( temp )
#define EXP_16		( temp<<4 )
#define EXP_15		( temp<<3 ) + ( temp<<2 ) + ( temp<<1 ) + ( temp )
#define EXP_14		( temp<<3 ) + ( temp<<2 ) + ( temp<<1 )
#define EXP_13		( temp<<3 ) + ( temp<<2 ) + ( temp )
#define EXP_12		( temp<<3 ) + ( temp<<2 )
#define EXP_11		( temp<<3 ) + ( temp<<1 ) + ( temp )
#define EXP_10		( temp<<3 ) + ( temp<<1 )
#define EXP_9		( temp<<3 ) + ( temp )
#define EXP_8		( temp<<3 )
#define EXP_7		( temp<<2 ) + ( temp<<1 ) + ( temp )
#define EXP_6		( temp<<2 ) + ( temp<<1 )
#define EXP_5		( temp<<2	) + ( temp )
#define EXP_4		( temp<<2 )
#define EXP_3		( temp<<1 ) + ( temp )
#define EXP_2		( temp<<1 )
#define EXP_1		( temp )

#define EXP_1OF2		( temp>>1 )
#define EXP_1OF4		( temp>>2 )
#define EXP_1OF8		( temp>>3 )
#define EXP_1OF16	( temp>>4 )

#define EXP_DIV16		( temp>>4 )
#define EXP_DIV8		( temp>>3 )
#define EXP_DIV4		( temp>>2 )
#define EXP_DIV2		( temp>>1 )
#define EXP_DIV1		( temp )