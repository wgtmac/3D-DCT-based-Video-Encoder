/*
 *
 *	
 *
 *
 *
 */

#include "YUVInput.h"
#include "EncoderParam.h"


int YUVInput_Init( YUVInput *yuvInputParam )
{
	int bufSlotNow = 0;
	int	fileSize = 0;

	memset(yuvInputParam, 0, sizeof(YUVInput));
	memset(&(yuvInputParam->frameBufTable), -1, sizeof(yuvInputParam->frameBufTable));

	yuvInputParam->yuvFrameDataSize = glbEncoderParam.codedHeight * glbEncoderParam.codedWidth;

	//allocate YUV frame buffer
	for(bufSlotNow = 0; bufSlotNow < YUV_FRAME_BUF_NUM; ++bufSlotNow)
	{
		yuvInputParam->frameBuf[bufSlotNow].data = malloc(yuvInputParam->yuvFrameDataSize);
	}
	//Open YUV file
	if( (yuvInputParam->yuvFile = fopen(glbEncoderParam.yuvFileStr, "rb")) == NULL )
	{
		printf("[error]Cannot open input yuv file: '%s'\n", glbEncoderParam.yuvFileStr);
		exit(-1);
	}

	//Check YUV file
	if( fseek(yuvInputParam->yuvFile, 0L, SEEK_END)  )
	{
		printf("[error]fseek()\n");
		exit(-1);
	}
	fileSize = ftell(yuvInputParam->yuvFile);
	if( fseek(yuvInputParam->yuvFile, 0L, SEEK_SET))
	{
		printf("[error]fseek()\n");
		exit(-1);
	}
	if(fileSize != glbEncoderParam.yuvHeight * glbEncoderParam.yuvWidth * glbEncoderParam.yuvFrameTotal)
	{
		printf("[error]the size(%d) of input yuv file '%s' should be equal to height*width*frames(%d)\n",
			fileSize, glbEncoderParam.yuvFileStr, 
			glbEncoderParam.yuvHeight * glbEncoderParam.yuvWidth * glbEncoderParam.yuvFrameTotal);
		exit(-1);
	}

	return 0;
}

uint8* YUVInput_GetFrameData(int frameNo)
{
	int		bufSlotNow;
	size_t		freadReturn;
	YUVInput	*yuvInputParam = glbEncoderParam.yuvInputParam;

	//Search for buffered frame
	for(bufSlotNow = 0; bufSlotNow < YUV_FRAME_BUF_NUM; ++bufSlotNow)
		if(yuvInputParam->frameBufTable[bufSlotNow] == frameNo)
			return yuvInputParam->frameBuf[bufSlotNow].data;
	
	//Load unbuffered frame into slot
	bufSlotNow = yuvInputParam->frameBufNextSlot;
	yuvInputParam->frameBufNextSlot = ( (bufSlotNow+1) >= YUV_FRAME_BUF_NUM ? 0 : (bufSlotNow+1) );

	freadReturn = fread(yuvInputParam->frameBuf[bufSlotNow].data, 
							sizeof(uint8), yuvInputParam->yuvFrameDataSize, yuvInputParam->yuvFile);
	if( freadReturn	!= yuvInputParam->yuvFrameDataSize )
	{
		printf("[error]fread error!, request %d bytes, but return %d bytes.\n",
					yuvInputParam->yuvFrameDataSize, freadReturn);
		exit(-1);
	}
	yuvInputParam->frameBufTable[bufSlotNow] = frameNo;

	return yuvInputParam->frameBuf[bufSlotNow].data;;
}