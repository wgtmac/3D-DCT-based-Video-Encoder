/*
 *
 *	
 *
 *
 *
 */


#pragma once

#include "common.h"

#define		YUV_FRAME_BUF_NUM		((int)10)


typedef struct YUVFrameBuf{
//	char	isValid;
//	int		frameNo;

	char	*data;
} YUVFrameBuf;



typedef struct YUVInput{
	YUVFrameBuf		frameBuf[YUV_FRAME_BUF_NUM];

	int				frameBufTable[YUV_FRAME_BUF_NUM];
	int				frameBufNextSlot;
	
	FILE*			yuvFile;
	int				yuvFrameDataSize;
} YUVInput;


int YUVInput_Init( YUVInput *yuvInputParam );

uint8* YUVInput_GetFrameData(int frameNo);
