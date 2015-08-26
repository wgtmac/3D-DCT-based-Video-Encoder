/*
 *
 *	
 *
 *
 *
 */


#pragma once


#include "common.h"
#include "EncoderParam.h"
#include "YUVInput.h"


int Encoder_EncodeSeq();

int Encoder_EncodeOneGOP(int frameNoBegin);

int Encoder_EncodeOneBlock(uint8 *inBlock, int32 *outBlock);	//DCT3 + Q + Scanning