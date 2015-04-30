/*
 *
 *	
 *
 *
 *
 */

#include "EncoderParam.h"
#include "getopt.h"

EncoderParam glbEncoderParam;
/**************************************************************
 *   getopt()
 *   w: yuv width, h: yuv height, f: yuv total frame num
 *   s: start frame num for coding, e:  end frame num for coding
 *   q: qp used for coding, 
 *   o: out put file name
 **************************************************************/  
const char glbGetOptStr[] = "w:h:f:s:e:q:o:c:";

int EncoderParam_Init()
{
	memset( &glbEncoderParam, 0, sizeof(glbEncoderParam) );
	glbEncoderParam.codedFrameMax = -1;

	return 0;
}




int EncoderParam_InterpretInputParam(int argc, char *argv[])
{
	int c;
	int index;

	glbEncoderParam.argc = argc;
	glbEncoderParam.argv = argv;

	while( (c = getopt(argc, argv, glbGetOptStr)) != -1 )
	{
		switch( c )
		{
		case 'w':
			glbEncoderParam.yuvWidth = atoi(optarg);
			break;

		case 'h':
			glbEncoderParam.yuvHeight = atoi(optarg);
			break;

		case 'f':
			glbEncoderParam.yuvFrameTotal = atoi(optarg);
			break;

		case 's':
			glbEncoderParam.codedFrameMin = atoi(optarg);
			break;

		case 'e':
			glbEncoderParam.codedFrameMax = atoi(optarg);
			break;

		case 'q':
			glbEncoderParam.qp = atoi(optarg);
			break;

		case 'o':
			glbEncoderParam.codedFileStrSize = strlen(optarg) + 1;
			if(glbEncoderParam.codedFileStrSize > FILE_PATH_LENGTH_MAX || glbEncoderParam.codedFileStrSize <= 0)
			{
				printf("[error]codedFileStrSize(%d) larger than FILE_PATH_LENGTH_MAX(%d)\n", 
					glbEncoderParam.codedFileStrSize, FILE_PATH_LENGTH_MAX);
				EncoderParam_PrintUsageAndExit();
			}
			glbEncoderParam.codedFileStr = malloc(glbEncoderParam.codedFileStrSize);

			memcpy(glbEncoderParam.codedFileStr, optarg, glbEncoderParam.codedFileStrSize);
			glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 1] = 0x00;
			break;

		case 'c':
			glbEncoderParam.coefFileStrSize = strlen(optarg) + 1;
			if(glbEncoderParam.coefFileStrSize > FILE_PATH_LENGTH_MAX || glbEncoderParam.coefFileStrSize <= 0)
			{
				printf("[error]coefFileStrSize(%d) larger than FILE_PATH_LENGTH_MAX(%d)\n", 
					glbEncoderParam.coefFileStrSize, FILE_PATH_LENGTH_MAX);
				EncoderParam_PrintUsageAndExit();
			}
			glbEncoderParam.coefFileStr = malloc(glbEncoderParam.coefFileStrSize);

			memcpy(glbEncoderParam.coefFileStr, optarg, glbEncoderParam.coefFileStrSize);
			glbEncoderParam.coefFileStr[glbEncoderParam.coefFileStrSize - 1] = 0x00;
			break;

		case '?':
		default:
			EncoderParam_PrintUsageAndExit();
			break;

		}
	}

	index = optind;
	if (argc - index  == 1)
	{
		glbEncoderParam.yuvFileStrSize = strlen(argv[index]) + 1;
		if(glbEncoderParam.yuvFileStrSize > FILE_PATH_LENGTH_MAX || glbEncoderParam.yuvFileStrSize <= 0)
		{
			printf("[error]yuvFileStrSize(%d) larger than FILE_PATH_LENGTH_MAX(%d)\n", 
					glbEncoderParam.yuvFileStrSize, FILE_PATH_LENGTH_MAX);
			EncoderParam_PrintUsageAndExit();
		}
		glbEncoderParam.yuvFileStr = malloc(glbEncoderParam.yuvFileStrSize);
		memcpy(glbEncoderParam.yuvFileStr, argv[index], glbEncoderParam.yuvFileStrSize);
		glbEncoderParam.yuvFileStr[glbEncoderParam.yuvFileStrSize - 1] = 0x00;
	}
	else if(argc - index  == 0)
	{
		printf("[error]no input YUV file specified!\n");
		EncoderParam_PrintUsageAndExit();
	}
	else
	{
		EncoderParam_PrintUsageAndExit();
	}
	
	//Set output frame size
	glbEncoderParam.codedHeight = glbEncoderParam.yuvHeight;
	glbEncoderParam.codedWidth = glbEncoderParam.yuvWidth;

	//Set output file name
	if(glbEncoderParam.codedFileStrSize == 0 || glbEncoderParam.codedFileStr == NULL)
	{
		if( ! memcmp(glbEncoderParam.yuvFileStr + strlen(glbEncoderParam.yuvFileStr) - 4, ".yuv", 4) )
		{
			glbEncoderParam.codedFileStrSize = glbEncoderParam.yuvFileStrSize;
			glbEncoderParam.codedFileStr = malloc(glbEncoderParam.codedFileStrSize);
			memcpy(glbEncoderParam.codedFileStr, glbEncoderParam.yuvFileStr, glbEncoderParam.codedFileStrSize);
		}
		else
		{
			glbEncoderParam.codedFileStrSize = glbEncoderParam.yuvFileStrSize + 4;
			glbEncoderParam.codedFileStr = malloc(glbEncoderParam.codedFileStrSize);
			memcpy(glbEncoderParam.codedFileStr, glbEncoderParam.yuvFileStr, glbEncoderParam.codedFileStrSize);
			glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 1] = 0x00;
		}
		glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 5] = '.';
		glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 4] = 'e';
		glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 3] = 'n';
		glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 2] = 'd';
		glbEncoderParam.codedFileStr[glbEncoderParam.codedFileStrSize - 1] = 0x00;
	}

	//Set endding frame number
	if(glbEncoderParam.codedFrameMax < 0)
		glbEncoderParam.codedFrameMax = glbEncoderParam.yuvFrameTotal - 1;
	//glbEncoderParam.codedFrameMax = (glbEncoderParam.codedFrameMax / 8) * 8;

	return 0;
}




int EncoderParam_CheckGlbParam()
{
	if(glbEncoderParam.yuvHeight <= 0 || glbEncoderParam.yuvHeight > YUV_HEIGHT_MAX)
	{
		printf("[error]YUV file height(%d) should be in the range (0,%d]\n", 
					glbEncoderParam.yuvHeight, YUV_HEIGHT_MAX);
		EncoderParam_PrintUsageAndExit();
	}

	
	if(glbEncoderParam.yuvWidth <= 0 || glbEncoderParam.yuvWidth > YUV_WIDTH_MAX)
	{
		printf("[error]YUV file width(%d) should be in the range (0,%d]\n", 
					glbEncoderParam.yuvWidth, YUV_WIDTH_MAX);
		EncoderParam_PrintUsageAndExit();
	}

	if(glbEncoderParam.yuvFrameTotal <= 0)
	{
		printf("[error]YUV file total frames(%d) should be large than 0\n", 
					glbEncoderParam.yuvFrameTotal);
		EncoderParam_PrintUsageAndExit();
	}

	if(glbEncoderParam.codedFrameMin < 0 || glbEncoderParam.codedFrameMin > glbEncoderParam.yuvFrameTotal - 1)
	{
		printf("[error]strart frame number(%d) should be in the range [0,yuv frames - 1(%d)]\n", 
					glbEncoderParam.codedFrameMin, glbEncoderParam.yuvFrameTotal - 1);
		EncoderParam_PrintUsageAndExit();
	}


	if( glbEncoderParam.codedFrameMax < glbEncoderParam.codedFrameMin || glbEncoderParam.codedFrameMax > glbEncoderParam.yuvFrameTotal - 1)
	{
		printf("[error]end frame number(%d) should be in the range [start frame(%d),yuv frames - 1(%d)], or less than 0\n", 
					glbEncoderParam.codedFrameMax, glbEncoderParam.codedFrameMin, glbEncoderParam.yuvFrameTotal - 1);
		EncoderParam_PrintUsageAndExit();
	}

	if(glbEncoderParam.qp < 0 || glbEncoderParam.qp > QP_CODING_MAX)
	{
		printf("[error]input qp value(%d) should be in the range [1,%d], or 0 for default\n", 
					glbEncoderParam.qp, QP_CODING_MAX);
		EncoderParam_PrintUsageAndExit();
	}

	{//check input yuv file
		FILE* fileInput = NULL;
		if( (fileInput = fopen(glbEncoderParam.yuvFileStr, "rb"))== NULL)
		{
			printf("[error]cannot open input yuv file '%s'\n", glbEncoderParam.yuvFileStr);
			EncoderParam_PrintUsageAndExit();
		}


		if( fileInput )
			fclose(fileInput);
	}

	{//check output file
		FILE* fileOutput = NULL;
		if( (fileOutput = fopen(glbEncoderParam.codedFileStr, "rb")) == NULL)	
			;
		else
		{
			printf("[error]output file '%s' already exists!\n", glbEncoderParam.codedFileStr);
			EncoderParam_PrintUsageAndExit();
		}

		if( fileOutput )
			fclose(fileOutput);
	}

	//check output file
	if(glbEncoderParam.coefFileStr)
	{
		FILE* fileOutput = NULL;
		if( (fileOutput = fopen(glbEncoderParam.coefFileStr, "rb")) == NULL)	
			;
		else
		{
			printf("[error]output coef file '%s' already exists!\n", glbEncoderParam.coefFileStr);
			EncoderParam_PrintUsageAndExit();
		}

		if( fileOutput )
			fclose(fileOutput);
	}

	return 0;
}

void EncoderParam_PrintGlbParam()
{
	printf("*************** Global Parameters ***************\n");

	printf("Input YUV file : %s\n", glbEncoderParam.yuvFileStr);
	printf("Ouput file : %s\n", glbEncoderParam.codedFileStr);

	if( glbEncoderParam.coefFileStr )
		printf("Ouput coef file : %s\n", glbEncoderParam.coefFileStr);

	printf("Input YUV file width : %d\n", glbEncoderParam.yuvWidth);
	printf("Input YUV file height : %d\n", glbEncoderParam.yuvHeight);
	printf("Coded width : %d\n", glbEncoderParam.codedWidth);
	printf("Coded height : %d\n", glbEncoderParam.codedHeight);
	printf("Input YUV file total frames : %d\n", glbEncoderParam.yuvFrameTotal);
	printf("Starting frame number: %d\n", glbEncoderParam.codedFrameMin);
	printf("Ending frame number: %d\n", glbEncoderParam.codedFrameMax);
	printf("Input QP value : %d\n", glbEncoderParam.qp);

	printf("*************************************************\n");

}


void EncoderParam_PrintUsage()
{
	printf("Usage: %s {-w width} {-h height} {-f yuv frames} [-s:-e:-q:-o:-c:] {input YUV File}\n", glbEncoderParam.argv[0]);
	printf("\ts: \tstart frame number, [0,frames-1]\n");
	printf("\te: \tend frame number, [start frame,frames-1], or < 0 to encode all frames\n");
	printf("\tqp: \tqp used for coding, [1,QP_MAX], or 0 for default\n");
	printf("\to: \toutput file name\n");;
	printf("\tc: \toutput coef file name\n");
	printf("Only YUV400 supported! \n");
}

void EncoderParam_PrintUsageAndExit()
{
	EncoderParam_PrintUsage();
	exit(-1);
}