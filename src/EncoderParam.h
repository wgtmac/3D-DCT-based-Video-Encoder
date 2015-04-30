/*
 *
 *	
 *
 *
 *
 */


#pragma once

#include "common.h"
#include "YUVInput.h"

#define			FILE_PATH_LENGTH_MAX		((int)1024 - 1)
#define			YUV_HEIGHT_MAX				((int)2000)
#define			YUV_WIDTH_MAX				((int)2000)
#define			QP_CODING_MAX				((int)2000)

extern const char glbGetOptStr[];

typedef struct EncoderParam{
	int		yuvHeight;
	int		yuvWidth;
	int		yuvFrameTotal;

	int		codedHeight;
	int		codedWidth;
	int		codedFrameMin;
	int		codedFrameMax;

	char	*yuvFileStr;
	size_t	yuvFileStrSize;
	char	*codedFileStr;
	size_t	codedFileStrSize;
	char	*coefFileStr;
	size_t coefFileStrSize;
	FILE*	coefFile;


	int		qp;
	
	YUVInput*	yuvInputParam;

	int		argc;
	char	**argv;		
} EncoderParam;

extern EncoderParam glbEncoderParam;


int EncoderParam_Init();
int EncoderParam_InterpretInputParam(int argc, char *argv[]);
int EncoderParam_CheckGlbParam();
void EncoderParam_PrintGlbParam();

void EncoderParam_PrintUsage();
void EncoderParam_PrintUsageAndExit();