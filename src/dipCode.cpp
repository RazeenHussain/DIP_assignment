#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<iostream>
#include<math.h>

using namespace std;

void screenMain(void);
void screenInformation(void);
void screenGreyScale(void);
void screenHistogram(void);
void screenTransformation(void);
void screenRotation(void);
void screenShear(void);
void screenScaling(void);
void screenTranslation(void);
void convertArrayToStruct(void);
void convertStructToArray(void);
void initializePallete(void);

struct coordinate
{
	int newX;
	int newY;
};

struct bmpHeader
{
	int imageType;
	long imageSize;
	long imageReserved;
	long imageOffset;
	long imageHeaderSize;
	long imageWidth;
	long imageHeight;
	int imageColorPlane;
	int imageBitsPerPixel;
	long imageCompressionMethod;
	long imageSizeOfImage;
	long imageHPperM;
	long imageVPperM;
	long imageUsedColors;
	long imageImportantColors;
};

unsigned char palleteGrey[1024]={0};
bool checkGrey=FALSE;
bool checkReal=FALSE;
unsigned char arrayHeaderReal[54]={0}; 
unsigned char arrayHeaderGreyScale[54]={0}; 
FILE * pointerImageReal=NULL;
FILE * pointerImageGreyScale=NULL;
FILE * pointerHistogram=NULL;
FILE * pointerImageTranslation=NULL;
FILE * pointerImageRotation=NULL;
FILE * pointerImageShear=NULL;
FILE * pointerImageScaling=NULL;
bmpHeader structImageReal;
bmpHeader structImageGreyScale;
unsigned char * dataImageReal=NULL;
unsigned char * arrayGrey=NULL;
unsigned char ** dataImageGrey=NULL;

int main(void)
{
	system("color f4");
	printf("\n\n\n\n\n\n\t\t\t\tDIP ASSIGNMENT\n\n\n\n\t\t\t\t       by\n\n\t\t\t\tRAZEEN HUSSAIN\n\n\n\n\n\n\t\t\t ");
	system("pause");
	initializePallete();
	screenMain();
	return 0;
}

void initializePallete(void)
{
	int k=0;
	for(int i=0;i<1024;i++)
	{
		for(int j=0;j<3;j++)
		{
			palleteGrey[k++]=i;
		}
		palleteGrey[k++]=0;
	}
}

void convertArrayToStruct(void)
{
	structImageReal.imageType=( arrayHeaderReal[0] + (arrayHeaderReal[1] * 256) );
	structImageReal.imageSize=( arrayHeaderReal[2] + (arrayHeaderReal[3] * 256) + (arrayHeaderReal[4] * 256 * 256) + (arrayHeaderReal[5] * 256 * 256 * 256) );
	structImageReal.imageReserved=( arrayHeaderReal[6] + (arrayHeaderReal[7] * 256) + (arrayHeaderReal[8] * 256 * 256) + (arrayHeaderReal[9] * 256 * 256 * 256) );
	structImageReal.imageOffset=( arrayHeaderReal[10] + (arrayHeaderReal[11] * 256) + (arrayHeaderReal[12] * 256 * 256) + (arrayHeaderReal[13] * 256 * 256 * 256) );
	structImageReal.imageHeaderSize=( arrayHeaderReal[14] + (arrayHeaderReal[15] * 256) + (arrayHeaderReal[16] * 256 * 256) + (arrayHeaderReal[17] * 256 * 256 * 256) );
	structImageReal.imageWidth=( arrayHeaderReal[18] + (arrayHeaderReal[19] * 256) + (arrayHeaderReal[20] * 256 * 256) + (arrayHeaderReal[21] * 256 * 256 * 256) );
	structImageReal.imageHeight=( arrayHeaderReal[22] + (arrayHeaderReal[23] * 256) + (arrayHeaderReal[24] * 256 * 256) + (arrayHeaderReal[25] * 256 * 256 * 256) );
	structImageReal.imageColorPlane=( arrayHeaderReal[26] + (arrayHeaderReal[27] * 256) );
	structImageReal.imageBitsPerPixel=( arrayHeaderReal[28] + (arrayHeaderReal[29] * 256) );
	structImageReal.imageCompressionMethod=( arrayHeaderReal[30] + (arrayHeaderReal[31] * 256) + (arrayHeaderReal[32] * 256 * 256) + (arrayHeaderReal[33] * 256 * 256 * 256) );
	structImageReal.imageSizeOfImage=( arrayHeaderReal[34] + (arrayHeaderReal[35] * 256) + (arrayHeaderReal[36] * 256 * 256) + (arrayHeaderReal[37] * 256 * 256 * 256) );
	structImageReal.imageHPperM=( arrayHeaderReal[38] + (arrayHeaderReal[39] * 256) + (arrayHeaderReal[40] * 256 * 256) + (arrayHeaderReal[41] * 256 * 256 * 256) );
	structImageReal.imageVPperM=( arrayHeaderReal[42] + (arrayHeaderReal[43] * 256) + (arrayHeaderReal[44] * 256 * 256) + (arrayHeaderReal[45] * 256 * 256 * 256) );
	structImageReal.imageUsedColors=( arrayHeaderReal[46] + (arrayHeaderReal[47] * 256) + (arrayHeaderReal[48] * 256 * 256) + (arrayHeaderReal[49] * 256 * 256 * 256) );
	structImageReal.imageImportantColors=( arrayHeaderReal[50] + (arrayHeaderReal[51] * 256) + (arrayHeaderReal[52] * 256 * 256) + (arrayHeaderReal[53] * 256 * 256 * 256) );
	return;
}

void convertStructToArray(void)
{
	arrayHeaderGreyScale[0]=( structImageGreyScale.imageType % 256 );
	arrayHeaderGreyScale[1]=( structImageGreyScale.imageType / 256 );
	arrayHeaderGreyScale[2]=( structImageGreyScale.imageSize % 256 );
	arrayHeaderGreyScale[3]=( ( structImageGreyScale.imageSize / 256 ) % 256 );
	arrayHeaderGreyScale[4]=( ( ( structImageGreyScale.imageSize / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[5]=( ( ( structImageGreyScale.imageSize / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[6]=( structImageGreyScale.imageReserved % 256 );
	arrayHeaderGreyScale[7]=( ( structImageGreyScale.imageReserved / 256 ) % 256 );
	arrayHeaderGreyScale[8]=( ( ( structImageGreyScale.imageReserved / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[9]=( ( ( structImageGreyScale.imageReserved / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[10]=( structImageGreyScale.imageOffset % 256 );
	arrayHeaderGreyScale[11]=( ( structImageGreyScale.imageOffset / 256 ) % 256 );
	arrayHeaderGreyScale[12]=( ( ( structImageGreyScale.imageOffset / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[13]=( ( ( structImageGreyScale.imageOffset / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[14]=( structImageGreyScale.imageHeaderSize % 256 );
	arrayHeaderGreyScale[15]=( ( structImageGreyScale.imageHeaderSize / 256 ) % 256 );
	arrayHeaderGreyScale[16]=( ( ( structImageGreyScale.imageHeaderSize / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[17]=( ( ( structImageGreyScale.imageHeaderSize / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[18]=( structImageGreyScale.imageWidth % 256 );
	arrayHeaderGreyScale[19]=( ( structImageGreyScale.imageWidth / 256 ) % 256 );
	arrayHeaderGreyScale[20]=( ( ( structImageGreyScale.imageWidth / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[21]=( ( ( structImageGreyScale.imageWidth / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[22]=( structImageGreyScale.imageHeight % 256 );
	arrayHeaderGreyScale[23]=( ( structImageGreyScale.imageHeight / 256 ) % 256 );
	arrayHeaderGreyScale[24]=( ( ( structImageGreyScale.imageHeight / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[25]=( ( ( structImageGreyScale.imageHeight / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[26]=( structImageGreyScale.imageColorPlane % 256 );
	arrayHeaderGreyScale[27]=( structImageGreyScale.imageColorPlane / 256 );
	arrayHeaderGreyScale[28]=( structImageGreyScale.imageBitsPerPixel % 256 );
	arrayHeaderGreyScale[29]=( structImageGreyScale.imageBitsPerPixel / 256 );
	arrayHeaderGreyScale[30]=( structImageGreyScale.imageCompressionMethod % 256 );
	arrayHeaderGreyScale[31]=( ( structImageGreyScale.imageCompressionMethod / 256 ) % 256 );
	arrayHeaderGreyScale[32]=( ( ( structImageGreyScale.imageCompressionMethod / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[33]=( ( ( structImageGreyScale.imageCompressionMethod / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[34]=( structImageGreyScale.imageSizeOfImage % 256 );
	arrayHeaderGreyScale[35]=( ( structImageGreyScale.imageSizeOfImage / 256 ) % 256 );
	arrayHeaderGreyScale[36]=( ( ( structImageGreyScale.imageSizeOfImage / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[37]=( ( ( structImageGreyScale.imageSizeOfImage / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[38]=( structImageGreyScale.imageHPperM % 256 );
	arrayHeaderGreyScale[39]=( ( structImageGreyScale.imageHPperM / 256 ) % 256 );
	arrayHeaderGreyScale[40]=( ( ( structImageGreyScale.imageHPperM / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[41]=( ( ( structImageGreyScale.imageHPperM / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[42]=( structImageGreyScale.imageVPperM % 256 );
	arrayHeaderGreyScale[43]=( ( structImageGreyScale.imageVPperM / 256 ) % 256 );
	arrayHeaderGreyScale[44]=( ( ( structImageGreyScale.imageVPperM / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[45]=( ( ( structImageGreyScale.imageVPperM / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[46]=( structImageGreyScale.imageUsedColors % 256 );
	arrayHeaderGreyScale[47]=( ( structImageGreyScale.imageUsedColors / 256 ) % 256 );
	arrayHeaderGreyScale[48]=( ( ( structImageGreyScale.imageUsedColors / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[49]=( ( ( structImageGreyScale.imageUsedColors / 256 ) / 256 ) / 256 );
	arrayHeaderGreyScale[50]=( structImageGreyScale.imageImportantColors % 256 );
	arrayHeaderGreyScale[51]=( ( structImageGreyScale.imageImportantColors / 256 ) % 256 );
	arrayHeaderGreyScale[52]=( ( ( structImageGreyScale.imageImportantColors / 256 ) / 256 ) % 256 );
	arrayHeaderGreyScale[53]=( ( ( structImageGreyScale.imageImportantColors / 256 ) / 256 ) / 256 );
}

void screenMain(void)
{
	system("cls");
	char inputCharacter=0;
	printf("\n\n\t\t\tMAIN SCREEN");
	printf("\n\n1)\tPress 'P' to read an image and print its information");
	printf("\n2)\tPress 'G' to convert image to grey scale");
	printf("\n3)\tPress 'E' to show histogram of the image");
	printf("\n4)\tPress 'T' to perform transformations on the image");
	printf("\n5)\tPress 'X' to exit the program");
	printf("\n\nENTER INPUT CHARACTER : ");
	cin>>inputCharacter;
	while ( (inputCharacter != 'P') && (inputCharacter != 'G') && (inputCharacter != 'E') && (inputCharacter != 'T') && (inputCharacter != 'X') )
	{
		printf("\nWRONG INPUT!\nENTER INPUT CHARACTER : ");
		cin>>inputCharacter;
	}
	switch (inputCharacter)
	{
		case 'P':
			screenInformation();
			break;
		case 'G':
			screenGreyScale();
			break;
		case 'E':
			screenHistogram();
			break;
		case 'T':
			screenTransformation();
			break;
		default:
			break;
	}
	return;
}

void screenInformation(void)
{
	char nameImageReal[50]={0};
	system("cls");
	printf("\n\n\t\t\tINFORMATION SCREEN");
	printf("\n\nENTER NAME OF IMAGE TO BE READ : \n\t");
//	cin>>nameImageReal;
	for (int i=0;i<50;i++)
	{
		nameImageReal[i]=getch();
		printf("%c",nameImageReal[i]);
		if (nameImageReal[i]<33)
		{
			nameImageReal[i]=NULL;
			break;
		}
	}
	pointerImageReal=fopen(nameImageReal , "rb");
	if (pointerImageReal == NULL)
	{
		printf("\n\nUNABLE TO OPEN FILE!");
	}
	else
	{
/*		if (arrayGrey!=NULL)
		{
			delete[] arrayGrey;
		}
		if (dataImageReal!=NULL)
		{
			delete[] dataImageReal; 
		}
		if (dataImageGrey!=NULL)
		{
			delete[] dataImageGrey;
		}
*/		checkReal=TRUE;
		checkGrey=FALSE;
		for (int i=0; i<54; i++)
		{
			arrayHeaderReal[i]=fgetc(pointerImageReal);
		}
		convertArrayToStruct();
		printf("\n\n\nSHOWING IMAGE DETAILS :\n");
		printf("\n\tIMAGE SIZE = %d Bytes" , structImageReal.imageSize);
		printf("\n\tIMAGE WIDTH = %d" , structImageReal.imageWidth);
		printf("\n\tIMAGE HEIGHT = %d" , structImageReal.imageHeight);
		printf("\n\tIMAGE RESOLUTION = %d x %d" , structImageReal.imageWidth, structImageReal.imageHeight);
		printf("\n\tIMAGE COLOR = %d bit image" , structImageReal.imageBitsPerPixel);
		if (structImageReal.imageBitsPerPixel == 8)
		{
			printf("\n\nIMAGE ALREADY IN GREY SCALE\nREAD A 24 BIT IMAGE");
			checkReal=FALSE;
		}
		else
		{
			dataImageReal = new unsigned char [3 * structImageReal.imageWidth * structImageReal.imageHeight];
			for (long i=0; i<(3 * structImageReal.imageWidth * structImageReal.imageHeight);i++)
			{
				dataImageReal[i]=fgetc(pointerImageReal);
			}
		}
		fclose(pointerImageReal);
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenMain();
	return;
}

void screenGreyScale(void)
{
	char nameImageGreyScale[50]={0};
	system("cls");
	printf("\n\n\t\t\tGREY SCALE CONVERSION SCREEN");
	if (checkReal == TRUE)
	{
		printf("\n\nENTER NAME OF IMAGE TO BE WRITTEN : \n\t");
		for (int i=0;i<50;i++)
		{
			nameImageGreyScale[i]=getch();
			printf("%c",nameImageGreyScale[i]);
			if (nameImageGreyScale[i]<33)
			{
				nameImageGreyScale[i]=NULL;
				break;
			}
		}
		pointerImageGreyScale=fopen(nameImageGreyScale , "wb");
		if (pointerImageGreyScale == NULL)
		{
			printf("\n\nUNABLE TO CREATE FILE!");
		}
		else
		{
			arrayGrey = new unsigned char[structImageReal.imageWidth*structImageReal.imageHeight];
			dataImageGrey = new unsigned char*[structImageReal.imageHeight];
			for (int i=0; i<structImageReal.imageHeight; i++)
			{
				dataImageGrey[i] = arrayGrey + structImageReal.imageWidth*i;
			}
			structImageGreyScale=structImageReal;
			int k=0, b=0, g=0, r=0;
			for (int i=0; i<structImageGreyScale.imageHeight; i++)
			{
				for (int j=0; j<structImageGreyScale.imageWidth; j++)
				{
					b=dataImageReal[k++];
					g=dataImageReal[k++];
					r=dataImageReal[k++];
					dataImageGrey[i][j]=( (30*r) + (59*g) + (11*b) )/100;
				}
			}
			structImageGreyScale.imageOffset = 1078;
			structImageGreyScale.imageBitsPerPixel = 8;
			structImageGreyScale.imageSizeOfImage = ( structImageGreyScale.imageHeight * structImageGreyScale.imageWidth );
			structImageGreyScale.imageSize = ( structImageGreyScale.imageSizeOfImage + 1078 );
			convertStructToArray();
			for (int i=0; i<54; i++)
			{
				fprintf(pointerImageGreyScale, "%c", arrayHeaderGreyScale[i]);		
			}
			for (int i=0; i<1024; i++)
			{
				fprintf(pointerImageGreyScale, "%c", palleteGrey[i]);		
			}
			for (int i=0; i<structImageGreyScale.imageHeight; i++)
			{
				for (int j=0; j<structImageGreyScale.imageWidth; j++)
				{
					fprintf(pointerImageGreyScale, "%c", dataImageGrey[i][j]);		
				}
			}
			checkGrey=TRUE;
			fclose(pointerImageGreyScale);
			printf("\n\n\nSUCCESSFULLY CONVERTED TO GREY SCALE\n");
		}

	}
	else
	{
		printf("\n\nNO ACTIVE IMAGE!\nFIRST READ AN IMAGE\n");
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenMain();
	return;
}

void screenHistogram(void)
{
	long countGrey[256]={0};
	unsigned char countScale[256]={0};
	bmpHeader structHistogram;
	unsigned char dataHistogram[108][258];
	unsigned char arrayHeaderHistogram[54]={0};
	system("cls");
	printf("\n\n\t\t\tGREY SCALE HISTOGRAM SCREEN");

	if (checkGrey==FALSE)
	{
		printf("\n\nNO GREY SCALE IMAGE!\nFIRST CONVERT TO GREY SCALE\n");
	}
	else
	{
		pointerHistogram=fopen("HISTOGRAM.bmp" , "wb");
		if (pointerImageGreyScale == NULL)
		{
			printf("\n\nUNABLE TO CREATE HISTOGRAM!");
		}
		else
		{
			for (int i=0; i<structImageGreyScale.imageHeight; i++)
			{
				for (int j=0; j<structImageGreyScale.imageWidth; j++)
				{
					countGrey[dataImageGrey[i][j]]++;
				}
			}
			unsigned long max=0;
			for (int i=0; i<256; i++)
			{
				if (countGrey[i]>max)
				{
					max=countGrey[i];
				}
			}
			for (int i=0; i<256; i++)
			{
				countScale[i]=( ( countGrey[i] * 99 ) / max );
			}
			for (int i=0; i<108; i++)
			{
				for (int j=0; j<258; j++)
				{
					dataHistogram[i][j]=255;
				}
			}
			structHistogram=structImageGreyScale;
			structHistogram.imageHeight = 108;
			structHistogram.imageWidth = 258;
			structHistogram.imageSizeOfImage = structHistogram.imageWidth * structHistogram.imageHeight;
			structHistogram.imageSize = structHistogram.imageSizeOfImage + 1078;

			arrayHeaderHistogram[0]=( structHistogram.imageType % 256 );
			arrayHeaderHistogram[1]=( structHistogram.imageType / 256 );
			arrayHeaderHistogram[2]=( structHistogram.imageSize % 256 );
			arrayHeaderHistogram[3]=( ( structHistogram.imageSize / 256 ) % 256 );
			arrayHeaderHistogram[4]=( ( ( structHistogram.imageSize / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[5]=( ( ( structHistogram.imageSize / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[6]=( structHistogram.imageReserved % 256 );
			arrayHeaderHistogram[7]=( ( structHistogram.imageReserved / 256 ) % 256 );
			arrayHeaderHistogram[8]=( ( ( structHistogram.imageReserved / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[9]=( ( ( structHistogram.imageReserved / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[10]=( structHistogram.imageOffset % 256 );
			arrayHeaderHistogram[11]=( ( structHistogram.imageOffset / 256 ) % 256 );
			arrayHeaderHistogram[12]=( ( ( structHistogram.imageOffset / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[13]=( ( ( structHistogram.imageOffset / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[14]=( structHistogram.imageHeaderSize % 256 );
			arrayHeaderHistogram[15]=( ( structHistogram.imageHeaderSize / 256 ) % 256 );
			arrayHeaderHistogram[16]=( ( ( structHistogram.imageHeaderSize / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[17]=( ( ( structHistogram.imageHeaderSize / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[18]=( structHistogram.imageWidth % 256 );
			arrayHeaderHistogram[19]=( ( structHistogram.imageWidth / 256 ) % 256 );
			arrayHeaderHistogram[20]=( ( ( structHistogram.imageWidth / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[21]=( ( ( structHistogram.imageWidth / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[22]=( structHistogram.imageHeight % 256 );
			arrayHeaderHistogram[23]=( ( structHistogram.imageHeight / 256 ) % 256 );
			arrayHeaderHistogram[24]=( ( ( structHistogram.imageHeight / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[25]=( ( ( structHistogram.imageHeight / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[26]=( structHistogram.imageColorPlane % 256 );
			arrayHeaderHistogram[27]=( structHistogram.imageColorPlane / 256 );
			arrayHeaderHistogram[28]=( structHistogram.imageBitsPerPixel % 256 );
			arrayHeaderHistogram[29]=( structHistogram.imageBitsPerPixel / 256 );
			arrayHeaderHistogram[30]=( structHistogram.imageCompressionMethod % 256 );
			arrayHeaderHistogram[31]=( ( structHistogram.imageCompressionMethod / 256 ) % 256 );
			arrayHeaderHistogram[32]=( ( ( structHistogram.imageCompressionMethod / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[33]=( ( ( structHistogram.imageCompressionMethod / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[34]=( structHistogram.imageSizeOfImage % 256 );
			arrayHeaderHistogram[35]=( ( structHistogram.imageSizeOfImage / 256 ) % 256 );
			arrayHeaderHistogram[36]=( ( ( structHistogram.imageSizeOfImage / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[37]=( ( ( structHistogram.imageSizeOfImage / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[38]=( structHistogram.imageHPperM % 256 );
			arrayHeaderHistogram[39]=( ( structHistogram.imageHPperM / 256 ) % 256 );
			arrayHeaderHistogram[40]=( ( ( structHistogram.imageHPperM / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[41]=( ( ( structHistogram.imageHPperM / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[42]=( structHistogram.imageVPperM % 256 );
			arrayHeaderHistogram[43]=( ( structHistogram.imageVPperM / 256 ) % 256 );
			arrayHeaderHistogram[44]=( ( ( structHistogram.imageVPperM / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[45]=( ( ( structHistogram.imageVPperM / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[46]=( structHistogram.imageUsedColors % 256 );
			arrayHeaderHistogram[47]=( ( structHistogram.imageUsedColors / 256 ) % 256 );
			arrayHeaderHistogram[48]=( ( ( structHistogram.imageUsedColors / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[49]=( ( ( structHistogram.imageUsedColors / 256 ) / 256 ) / 256 );
			arrayHeaderHistogram[50]=( structHistogram.imageImportantColors % 256 );
			arrayHeaderHistogram[51]=( ( structHistogram.imageImportantColors / 256 ) % 256 );
			arrayHeaderHistogram[52]=( ( ( structHistogram.imageImportantColors / 256 ) / 256 ) % 256 );
			arrayHeaderHistogram[53]=( ( ( structHistogram.imageImportantColors / 256 ) / 256 ) / 256 );

			for (int i=0; i<54; i++)
			{
				fprintf(pointerHistogram, "%c", arrayHeaderHistogram[i]);		
			}
			for (int i=0; i<1024; i++)
			{
				fprintf(pointerHistogram, "%c", palleteGrey[i]);		
			}

			for (int i=1; i<257; i++)
			{
				dataHistogram[1][i]= i - 1 ;
				dataHistogram[2][i]= i - 1 ;
				dataHistogram[3][i]= i - 1 ;
				dataHistogram[4][i]= i - 1 ;
				dataHistogram[5][i]= i - 1 ;
			}

			for (int i=1; i<257; i++)
			{
				for (int j=7; j<countScale[i-1]+7; j++)
				{
					dataHistogram[j][i]=0;
				}
			}
			
			for (int i=0; i<109; i++)
			{
				for (int j=0; j<260; j++)
				{
					fputc(dataHistogram[i][j],pointerHistogram);	
				}
			}
			fclose(pointerHistogram);
			printf("\n\n\n\n\nHISTOGRAM CREATED SUCCESSFULLY\n");
		}
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenMain();
	return;
}

void screenTransformation(void)
{
	char inputCharacter=0;
	system("cls");
	printf("\n\n\t\t\tTRANSFORMATION SCREEN");
	if (checkGrey==FALSE)
	{
		printf("\n\nNO GREY SCALE IMAGE!\nFIRST CONVERT TO GREY SCALE\n");
		printf("\n\nPress any key to return . . . ");
		_getch();
		screenMain();
		return;
	}
	else
	{
		printf("\n\n1)\tPress 'T' to translate the image");
		printf("\n2)\tPress 'S' to scale the image");
		printf("\n3)\tPress 'R' to rotate the image");
		printf("\n4)\tPress 'Z' to shear the image");
		printf("\n5)\tPress 'X' to return to the Main Screen");
		printf("\n\nENTER INPUT CHARACTER : ");
		cin>>inputCharacter;
		while ( (inputCharacter != 'Z') && (inputCharacter != 'R') && (inputCharacter != 'S') && (inputCharacter != 'T') && (inputCharacter != 'X') )
		{
			printf("\nWRONG INPUT!\nENTER INPUT CHARACTER : ");
			cin>>inputCharacter;
		}
		switch (inputCharacter)
		{
			case 'T':
				screenTranslation();
				break;
			case 'S':
				screenScaling();
				break;
			case 'R':
				screenRotation();
				break;
			case 'Z':
				screenShear();
				break;
			default:
				screenMain();
				break;
		}
	}
	return;
}

void screenTranslation(void)
{
	unsigned char arrayHeaderTranslation[54]={0};
	int parameterX=0, parameterY=0;
	char nameImageTranslation[50]={50};
	system("cls");
	printf("\n\n\t\t\tTRANSLATION SCREEN");
	printf("\n\nENTER NAME OF IMAGE TO BE WRITTEN : \n\t");
	for (int i=0;i<50;i++)
	{
		nameImageTranslation[i]=getch();
		printf("%c",nameImageTranslation[i]);
		if (nameImageTranslation[i]<33)
		{
			nameImageTranslation[i]=NULL;
			break;
		}
	}
	pointerImageTranslation=fopen(nameImageTranslation , "wb");
	if (pointerImageTranslation == NULL)
	{
		printf("\n\nUNABLE TO PERFORM TRANSLATION!");
	}
	else
	{
		printf("\n\nENTER TRANSLATION PARAMETERS : \n");
		printf("\tX OFFSET = ");
		cin>>parameterX;
		printf("\tY OFFSET = ");
		cin>>parameterY;
		bmpHeader structImageTranslation=structImageGreyScale;
		structImageTranslation.imageHeight += abs(parameterY);
		structImageTranslation.imageWidth += abs(parameterX);
		structImageTranslation.imageSizeOfImage = structImageTranslation.imageWidth * structImageTranslation.imageHeight;
		structImageTranslation.imageSize = structImageTranslation.imageSizeOfImage + 1078;
		unsigned char * arrayTranslation = new unsigned char[structImageTranslation.imageWidth*structImageTranslation.imageHeight];
		unsigned char ** dataImageTranslation = new unsigned char*[structImageTranslation.imageHeight];
		for (int i=0; i<structImageTranslation.imageHeight; i++)
		{
			dataImageTranslation[i] = arrayTranslation + structImageTranslation.imageWidth*i;
		}
		for (int i=0; i<structImageTranslation.imageHeight; i++)
		{
			for (int j=0; j<structImageTranslation.imageWidth; j++)
			{
				dataImageTranslation[i][j]=0;
			}
		}
		if (parameterX>=0 && parameterY<=0)
		{
			for (int i=0; i<structImageTranslation.imageHeight-abs(parameterY); i++)
			{
				for (int j=abs(parameterX); j<structImageTranslation.imageWidth; j++)
				{
					dataImageTranslation[i][j]=dataImageGrey[i][j-abs(parameterX)];
				}
			}
		}
		else if (parameterX>=0 && parameterY>=0)
		{
			for (int i=abs(parameterY); i<structImageTranslation.imageHeight; i++)
			{
				for (int j=abs(parameterX); j<structImageTranslation.imageWidth; j++)
				{
					dataImageTranslation[i][j]=dataImageGrey[i-abs(parameterY)][j-abs(parameterX)];
				}
			}
		}
		else if (parameterX<=0 && parameterY<=0)
		{
			for (int i=0; i<structImageTranslation.imageHeight-abs(parameterY); i++)
			{
				for (int j=0; j<structImageTranslation.imageWidth-abs(parameterX); j++)
				{
					dataImageTranslation[i][j]=dataImageGrey[i][j];
				}
			}
		}
		else if (parameterX<=0 && parameterY>=0)
		{
			for (int i=abs(parameterY); i<structImageTranslation.imageHeight; i++)
			{
				for (int j=0; j<structImageTranslation.imageWidth-abs(parameterX); j++)
				{
					dataImageTranslation[i][j]=dataImageGrey[i-abs(parameterY)][j];
				}
			}
		}


		arrayHeaderTranslation[0]=( structImageTranslation.imageType % 256 );
		arrayHeaderTranslation[1]=( structImageTranslation.imageType / 256 );
		arrayHeaderTranslation[2]=( structImageTranslation.imageSize % 256 );
		arrayHeaderTranslation[3]=( ( structImageTranslation.imageSize / 256 ) % 256 );
		arrayHeaderTranslation[4]=( ( ( structImageTranslation.imageSize / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[5]=( ( ( structImageTranslation.imageSize / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[6]=( structImageTranslation.imageReserved % 256 );
		arrayHeaderTranslation[7]=( ( structImageTranslation.imageReserved / 256 ) % 256 );
		arrayHeaderTranslation[8]=( ( ( structImageTranslation.imageReserved / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[9]=( ( ( structImageTranslation.imageReserved / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[10]=( structImageTranslation.imageOffset % 256 );
		arrayHeaderTranslation[11]=( ( structImageTranslation.imageOffset / 256 ) % 256 );
		arrayHeaderTranslation[12]=( ( ( structImageTranslation.imageOffset / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[13]=( ( ( structImageTranslation.imageOffset / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[14]=( structImageTranslation.imageHeaderSize % 256 );
		arrayHeaderTranslation[15]=( ( structImageTranslation.imageHeaderSize / 256 ) % 256 );
		arrayHeaderTranslation[16]=( ( ( structImageTranslation.imageHeaderSize / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[17]=( ( ( structImageTranslation.imageHeaderSize / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[18]=( structImageTranslation.imageWidth % 256 );
		arrayHeaderTranslation[19]=( ( structImageTranslation.imageWidth / 256 ) % 256 );
		arrayHeaderTranslation[20]=( ( ( structImageTranslation.imageWidth / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[21]=( ( ( structImageTranslation.imageWidth / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[22]=( structImageTranslation.imageHeight % 256 );
		arrayHeaderTranslation[23]=( ( structImageTranslation.imageHeight / 256 ) % 256 );
		arrayHeaderTranslation[24]=( ( ( structImageTranslation.imageHeight / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[25]=( ( ( structImageTranslation.imageHeight / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[26]=( structImageTranslation.imageColorPlane % 256 );
		arrayHeaderTranslation[27]=( structImageTranslation.imageColorPlane / 256 );
		arrayHeaderTranslation[28]=( structImageTranslation.imageBitsPerPixel % 256 );
		arrayHeaderTranslation[29]=( structImageTranslation.imageBitsPerPixel / 256 );
		arrayHeaderTranslation[30]=( structImageTranslation.imageCompressionMethod % 256 );
		arrayHeaderTranslation[31]=( ( structImageTranslation.imageCompressionMethod / 256 ) % 256 );
		arrayHeaderTranslation[32]=( ( ( structImageTranslation.imageCompressionMethod / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[33]=( ( ( structImageTranslation.imageCompressionMethod / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[34]=( structImageTranslation.imageSizeOfImage % 256 );
		arrayHeaderTranslation[35]=( ( structImageTranslation.imageSizeOfImage / 256 ) % 256 );
		arrayHeaderTranslation[36]=( ( ( structImageTranslation.imageSizeOfImage / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[37]=( ( ( structImageTranslation.imageSizeOfImage / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[38]=( structImageTranslation.imageHPperM % 256 );
		arrayHeaderTranslation[39]=( ( structImageTranslation.imageHPperM / 256 ) % 256 );
		arrayHeaderTranslation[40]=( ( ( structImageTranslation.imageHPperM / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[41]=( ( ( structImageTranslation.imageHPperM / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[42]=( structImageTranslation.imageVPperM % 256 );
		arrayHeaderTranslation[43]=( ( structImageTranslation.imageVPperM / 256 ) % 256 );
		arrayHeaderTranslation[44]=( ( ( structImageTranslation.imageVPperM / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[45]=( ( ( structImageTranslation.imageVPperM / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[46]=( structImageTranslation.imageUsedColors % 256 );
		arrayHeaderTranslation[47]=( ( structImageTranslation.imageUsedColors / 256 ) % 256 );
		arrayHeaderTranslation[48]=( ( ( structImageTranslation.imageUsedColors / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[49]=( ( ( structImageTranslation.imageUsedColors / 256 ) / 256 ) / 256 );
		arrayHeaderTranslation[50]=( structImageTranslation.imageImportantColors % 256 );
		arrayHeaderTranslation[51]=( ( structImageTranslation.imageImportantColors / 256 ) % 256 );
		arrayHeaderTranslation[52]=( ( ( structImageTranslation.imageImportantColors / 256 ) / 256 ) % 256 );
		arrayHeaderTranslation[53]=( ( ( structImageTranslation.imageImportantColors / 256 ) / 256 ) / 256 );

		for (int i=0; i<54; i++)
		{
			fprintf(pointerImageTranslation, "%c", arrayHeaderTranslation[i]);		
		}
		for (int i=0; i<1024; i++)
		{
			fprintf(pointerImageTranslation, "%c", palleteGrey[i]);		
		}
		for (int i=0; i<structImageTranslation.imageHeight; i++)
		{
			for (int j=0; j<structImageTranslation.imageWidth; j++)
			{
				fprintf(pointerImageTranslation, "%c", dataImageTranslation[i][j]);		
			}
		}
		delete [] arrayTranslation; 
		delete [] dataImageTranslation;
		fclose(pointerImageTranslation);
		printf("\n\nTRANSLATION APPLIED SUCCESSFULLY\n");
		printf("\n\nSHOWING IMAGE DETAILS :\n");
		printf("\n\tIMAGE SIZE = %d Bytes" , structImageTranslation.imageSize);
		printf("\n\tIMAGE WIDTH = %d" , structImageTranslation.imageWidth);
		printf("\n\tIMAGE HEIGHT = %d" , structImageTranslation.imageHeight);
		printf("\n\tIMAGE RESOLUTION = %d x %d" , structImageTranslation.imageWidth, structImageTranslation.imageHeight);
		printf("\n\tIMAGE COLOR = %d bit image" , structImageTranslation.imageBitsPerPixel);
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenTransformation();
	return;
}

void screenScaling(void)
{
	unsigned char arrayHeaderScaling[54]={0};
	float parameterS=0;
	char nameImageScaling[50]={50};
	system("cls");
	printf("\n\n\t\t\tSCALING SCREEN");
	printf("\n\nENTER NAME OF IMAGE TO BE WRITTEN : \n\t");
	for (int i=0;i<50;i++)
	{
		nameImageScaling[i]=getch();
		printf("%c",nameImageScaling[i]);
		if (nameImageScaling[i]<33)
		{
			nameImageScaling[i]=NULL;
			break;
		}
	}
	pointerImageScaling=fopen(nameImageScaling , "wb");
	if (pointerImageScaling == NULL)
	{
		printf("\n\nUNABLE TO PERFORM SCALING!");
	}
	else
	{
		printf("\n\nENTER SCALING PARAMETER : \n");
		printf("\tSCALE FACTOR = ");
		cin>>parameterS;

		bmpHeader structImageScaling=structImageGreyScale;
		structImageScaling.imageHeight *= parameterS;
		structImageScaling.imageWidth *= parameterS;
		structImageScaling.imageSizeOfImage = structImageScaling.imageWidth * structImageScaling.imageHeight;
		structImageScaling.imageSize = structImageScaling.imageSizeOfImage + 1078;
		unsigned char * arrayScaling = new unsigned char[structImageScaling.imageWidth*structImageScaling.imageHeight];
		unsigned char ** dataImageScaling = new unsigned char*[structImageScaling.imageHeight];
		for (int i=0; i<structImageScaling.imageHeight; i++)
		{
			dataImageScaling[i] = arrayScaling + structImageScaling.imageWidth*i;
		}
		bool * arrayCheck = new bool[structImageScaling.imageWidth*structImageScaling.imageHeight];
		bool ** dataCheck = new bool*[structImageScaling.imageHeight];
		for (int i=0; i<structImageScaling.imageHeight; i++)
		{
			dataCheck[i] = arrayCheck + structImageScaling.imageWidth*i;
		}
		for (int i=0; i<structImageScaling.imageHeight; i++)
		{
			for (int j=0; j<structImageScaling.imageWidth; j++)
			{
				dataImageScaling[i][j]=0;
			}
		}
		for (int i=0; i<structImageScaling.imageHeight; i++)
		{
			for (int j=0; j<structImageScaling.imageWidth; j++)
			{
				dataCheck[i][j]=FALSE;
			}
		}
		if (parameterS==1)
		{
			for (int i=0; i<structImageScaling.imageHeight; i++)
			{
				for (int j=0; j<structImageScaling.imageWidth; j++)
				{
					dataImageScaling[i][j]=dataImageGrey[i][j];
				}
			}
		}
		else if (parameterS<1 & parameterS>0)
		{
			long k=0, l=0;
			for (long i=0; i<structImageScaling.imageHeight; i++)
			{
				l=0;
				if (k>=structImageGreyScale.imageHeight)
				{
					k=structImageGreyScale.imageHeight-1;
				}
				for (long j=0; j<structImageScaling.imageWidth; j++)
				{
					if (l>=structImageGreyScale.imageWidth)
					{
						l=structImageGreyScale.imageWidth-1;
					}
					dataImageScaling[i][j]=dataImageGrey[k][l];
					l+=(1/parameterS);
				}
				k+=(1/parameterS);
			}
		}
		else if (parameterS>1)
		{
			long k=0, l=0;
			for (long i=0; i<structImageGreyScale.imageHeight; i++, k+=parameterS)
			{
				l=0;
				for (long j=0; j<structImageGreyScale.imageWidth; j++, l+=parameterS)
				{
					dataCheck[k][l]=TRUE;
					dataImageScaling[k][l]=dataImageGrey[i][j];
				}
			}
			int temp=0, count=0, m=0;
			for (long i=0; i<structImageScaling.imageHeight; i++)
			{
				for (long j=0; j<structImageScaling.imageWidth; j++)
				{
					if (dataCheck[i][j]==FALSE)
					{
						temp=0;
						count=0;
						m=i+1;
						while(m<structImageScaling.imageHeight)
						{
							if (dataCheck[m][j]==TRUE)
							{
								temp+=dataImageScaling[m][j];
								count++;
								break;
							}
							m++;
						}
						m=j+1;
						while(m<structImageScaling.imageWidth)
						{
							if (dataCheck[i][m]==TRUE)
							{
								temp+=dataImageScaling[i][m];
								count++;
								break;
							}
							m++;
						}
						m=i-1;
						while(m>=0)
						{
							if (dataCheck[m][j]==TRUE)
							{
								temp+=dataImageScaling[m][j];
								count++;
								break;
							}
							m--;
						}
						m=j-1;
						while(m>=0)
						{
							if (dataCheck[i][m]==TRUE)
							{
								temp+=dataImageScaling[i][m];
								count++;
								break;
							}
							m--;
						}
						dataImageScaling[i][j]=temp/count;
						dataCheck[i][j]=TRUE;
					}
				}
			}
		}

		arrayHeaderScaling[0]=( structImageScaling.imageType % 256 );
		arrayHeaderScaling[1]=( structImageScaling.imageType / 256 );
		arrayHeaderScaling[2]=( structImageScaling.imageSize % 256 );
		arrayHeaderScaling[3]=( ( structImageScaling.imageSize / 256 ) % 256 );
		arrayHeaderScaling[4]=( ( ( structImageScaling.imageSize / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[5]=( ( ( structImageScaling.imageSize / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[6]=( structImageScaling.imageReserved % 256 );
		arrayHeaderScaling[7]=( ( structImageScaling.imageReserved / 256 ) % 256 );
		arrayHeaderScaling[8]=( ( ( structImageScaling.imageReserved / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[9]=( ( ( structImageScaling.imageReserved / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[10]=( structImageScaling.imageOffset % 256 );
		arrayHeaderScaling[11]=( ( structImageScaling.imageOffset / 256 ) % 256 );
		arrayHeaderScaling[12]=( ( ( structImageScaling.imageOffset / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[13]=( ( ( structImageScaling.imageOffset / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[14]=( structImageScaling.imageHeaderSize % 256 );
		arrayHeaderScaling[15]=( ( structImageScaling.imageHeaderSize / 256 ) % 256 );
		arrayHeaderScaling[16]=( ( ( structImageScaling.imageHeaderSize / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[17]=( ( ( structImageScaling.imageHeaderSize / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[18]=( structImageScaling.imageWidth % 256 );
		arrayHeaderScaling[19]=( ( structImageScaling.imageWidth / 256 ) % 256 );
		arrayHeaderScaling[20]=( ( ( structImageScaling.imageWidth / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[21]=( ( ( structImageScaling.imageWidth / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[22]=( structImageScaling.imageHeight % 256 );
		arrayHeaderScaling[23]=( ( structImageScaling.imageHeight / 256 ) % 256 );
		arrayHeaderScaling[24]=( ( ( structImageScaling.imageHeight / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[25]=( ( ( structImageScaling.imageHeight / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[26]=( structImageScaling.imageColorPlane % 256 );
		arrayHeaderScaling[27]=( structImageScaling.imageColorPlane / 256 );
		arrayHeaderScaling[28]=( structImageScaling.imageBitsPerPixel % 256 );
		arrayHeaderScaling[29]=( structImageScaling.imageBitsPerPixel / 256 );
		arrayHeaderScaling[30]=( structImageScaling.imageCompressionMethod % 256 );
		arrayHeaderScaling[31]=( ( structImageScaling.imageCompressionMethod / 256 ) % 256 );
		arrayHeaderScaling[32]=( ( ( structImageScaling.imageCompressionMethod / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[33]=( ( ( structImageScaling.imageCompressionMethod / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[34]=( structImageScaling.imageSizeOfImage % 256 );
		arrayHeaderScaling[35]=( ( structImageScaling.imageSizeOfImage / 256 ) % 256 );
		arrayHeaderScaling[36]=( ( ( structImageScaling.imageSizeOfImage / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[37]=( ( ( structImageScaling.imageSizeOfImage / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[38]=( structImageScaling.imageHPperM % 256 );
		arrayHeaderScaling[39]=( ( structImageScaling.imageHPperM / 256 ) % 256 );
		arrayHeaderScaling[40]=( ( ( structImageScaling.imageHPperM / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[41]=( ( ( structImageScaling.imageHPperM / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[42]=( structImageScaling.imageVPperM % 256 );
		arrayHeaderScaling[43]=( ( structImageScaling.imageVPperM / 256 ) % 256 );
		arrayHeaderScaling[44]=( ( ( structImageScaling.imageVPperM / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[45]=( ( ( structImageScaling.imageVPperM / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[46]=( structImageScaling.imageUsedColors % 256 );
		arrayHeaderScaling[47]=( ( structImageScaling.imageUsedColors / 256 ) % 256 );
		arrayHeaderScaling[48]=( ( ( structImageScaling.imageUsedColors / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[49]=( ( ( structImageScaling.imageUsedColors / 256 ) / 256 ) / 256 );
		arrayHeaderScaling[50]=( structImageScaling.imageImportantColors % 256 );
		arrayHeaderScaling[51]=( ( structImageScaling.imageImportantColors / 256 ) % 256 );
		arrayHeaderScaling[52]=( ( ( structImageScaling.imageImportantColors / 256 ) / 256 ) % 256 );
		arrayHeaderScaling[53]=( ( ( structImageScaling.imageImportantColors / 256 ) / 256 ) / 256 );

		for (int i=0; i<54; i++)
		{
			fprintf(pointerImageScaling, "%c", arrayHeaderScaling[i]);		
		}
		for (int i=0; i<1024; i++)
		{
			fprintf(pointerImageScaling, "%c", palleteGrey[i]);		
		}
		for (int i=0; i<structImageScaling.imageHeight; i++)
		{
			for (int j=0; j<structImageScaling.imageWidth; j++)
			{
				fprintf(pointerImageScaling, "%c", dataImageScaling[i][j]);		
			}
		}
		delete [] arrayScaling;
		delete [] dataImageScaling;
		delete [] arrayCheck;
		delete [] dataCheck;
		fclose(pointerImageScaling);
		printf("\n\nSCALING APPLIED SUCCESSFULLY\n");
		printf("\n\nSHOWING IMAGE DETAILS :\n");
		printf("\n\tIMAGE SIZE = %d Bytes" , structImageScaling.imageSize);
		printf("\n\tIMAGE WIDTH = %d" , structImageScaling.imageWidth);
		printf("\n\tIMAGE HEIGHT = %d" , structImageScaling.imageHeight);
		printf("\n\tIMAGE RESOLUTION = %d x %d" , structImageScaling.imageWidth, structImageScaling.imageHeight);
		printf("\n\tIMAGE COLOR = %d bit image" , structImageScaling.imageBitsPerPixel);
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenTransformation();
	return;
}

void screenRotation(void)
{
	unsigned char arrayHeaderRotation[54]={0};
	int parameterR=0;
	char nameImageRotation[50]={50};
	system("cls");
	printf("\n\n\t\t\tROTATION SCREEN");
	printf("\n\nENTER NAME OF IMAGE TO BE WRITTEN : \n\t");
	for (int i=0;i<50;i++)
	{
		nameImageRotation[i]=getch();
		printf("%c",nameImageRotation[i]);
		if (nameImageRotation[i]<33)
		{
			nameImageRotation[i]=NULL;
			break;
		}
	}
	pointerImageRotation=fopen(nameImageRotation , "wb");
	if (pointerImageRotation == NULL)
	{
		printf("\n\nUNABLE TO PERFORM ROTATION!");
	}
	else
	{
		printf("\n\nENTER ROTATION PARAMETER : \n");
		printf("\tROTATION ANGLE = ");
		cin>>parameterR;

		int centerY=structImageGreyScale.imageHeight/2;
		int centerX=structImageGreyScale.imageWidth/2;

		float angleR=(parameterR*3.142)/180;
		float a0=cos(angleR);
		float b0=sin(angleR);

		int big=structImageGreyScale.imageHeight;
		if (structImageGreyScale.imageWidth>big)
		{
			big = structImageGreyScale.imageWidth;
		}
		big*=1.5;

		bmpHeader structImageRotation=structImageGreyScale;
		structImageRotation.imageHeight =big;
		structImageRotation.imageWidth = big;
		structImageRotation.imageSizeOfImage = structImageRotation.imageWidth * structImageRotation.imageHeight;
		structImageRotation.imageSize = structImageRotation.imageSizeOfImage + 1078;

		unsigned char * arrayRotation = new unsigned char[structImageRotation.imageWidth*structImageRotation.imageHeight];
		unsigned char ** dataImageRotation = new unsigned char*[structImageRotation.imageHeight];
		for (int i=0; i<structImageRotation.imageHeight; i++)
		{
			dataImageRotation[i] = arrayRotation + structImageRotation.imageWidth*i;
		}
		for (int i=0; i<structImageRotation.imageHeight; i++)
		{
			for (int j=0; j<structImageRotation.imageWidth; j++)
			{
				dataImageRotation[i][j]=255;
			}
		}
		bool * arrayCheck = new bool[structImageRotation.imageWidth*structImageRotation.imageHeight];
		bool ** dataCheck = new bool*[structImageRotation.imageHeight];
		for (int i=0; i<structImageRotation.imageHeight; i++)
		{
			dataCheck[i] = arrayCheck + structImageRotation.imageWidth*i;
		}
		for (int i=0; i<structImageRotation.imageHeight; i++)
		{
			for (int j=0; j<structImageRotation.imageWidth; j++)
			{
				dataCheck[i][j]=FALSE;
			}
		}

		int newX, newY, newC;
		newC=big/2;
		for (int i=0; i<structImageGreyScale.imageHeight; i++)
		{
			for (int j=0; j<structImageGreyScale.imageWidth; j++)
			{
				newY=(int)( newC + ( ( i - centerY ) * b0 ) + ( ( j - centerX ) * a0 ) ); 
				newX=(int)( newC + ( ( i - centerY ) * a0 ) - ( ( j - centerX ) * b0 ) ); 
				dataImageRotation[newX][newY]=dataImageGrey[i][j];
				dataCheck[newX][newY]=TRUE;
			}
		}

		int temp=0, count=0, m=0;
		for (long i=3; i<(structImageRotation.imageHeight-3); i++)
		{
			for (long j=3; j<(structImageRotation.imageWidth-3); j++)
			{
				if (dataCheck[i][j]==FALSE)
				{
					temp=0;
					count=0;
					m=i+1;
					while(m<i+3)
					{
						if (dataCheck[m][j]==TRUE)
						{
							temp+=dataImageRotation[m][j];
							count++;
							break;
						}
						m++;
					}
					m=j+1;
					while(m<j+3)
					{
						if (dataCheck[i][m]==TRUE)
						{
							temp+=dataImageRotation[i][m];
							count++;
							break;
						}
						m++;
					}
					m=i-1;
					while(m>=i-3)
					{
						if (dataCheck[m][j]==TRUE)
						{
							temp+=dataImageRotation[m][j];
							count++;
							break;
						}
						m--;
					}
					m=j-1;
					while(m>=j-3)
					{
						if (dataCheck[i][m]==TRUE)
						{

							temp+=dataImageRotation[i][m];
							count++;
							break;
						}
						m--;
					}
					if (count>0)
					{
						dataImageRotation[i][j]=temp/count;
					}
				}
			}
		}



		arrayHeaderRotation[0]=( structImageRotation.imageType % 256 );
		arrayHeaderRotation[1]=( structImageRotation.imageType / 256 );
		arrayHeaderRotation[2]=( structImageRotation.imageSize % 256 );
		arrayHeaderRotation[3]=( ( structImageRotation.imageSize / 256 ) % 256 );
		arrayHeaderRotation[4]=( ( ( structImageRotation.imageSize / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[5]=( ( ( structImageRotation.imageSize / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[6]=( structImageRotation.imageReserved % 256 );
		arrayHeaderRotation[7]=( ( structImageRotation.imageReserved / 256 ) % 256 );
		arrayHeaderRotation[8]=( ( ( structImageRotation.imageReserved / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[9]=( ( ( structImageRotation.imageReserved / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[10]=( structImageRotation.imageOffset % 256 );
		arrayHeaderRotation[11]=( ( structImageRotation.imageOffset / 256 ) % 256 );
		arrayHeaderRotation[12]=( ( ( structImageRotation.imageOffset / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[13]=( ( ( structImageRotation.imageOffset / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[14]=( structImageRotation.imageHeaderSize % 256 );
		arrayHeaderRotation[15]=( ( structImageRotation.imageHeaderSize / 256 ) % 256 );
		arrayHeaderRotation[16]=( ( ( structImageRotation.imageHeaderSize / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[17]=( ( ( structImageRotation.imageHeaderSize / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[18]=( structImageRotation.imageWidth % 256 );
		arrayHeaderRotation[19]=( ( structImageRotation.imageWidth / 256 ) % 256 );
		arrayHeaderRotation[20]=( ( ( structImageRotation.imageWidth / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[21]=( ( ( structImageRotation.imageWidth / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[22]=( structImageRotation.imageHeight % 256 );
		arrayHeaderRotation[23]=( ( structImageRotation.imageHeight / 256 ) % 256 );
		arrayHeaderRotation[24]=( ( ( structImageRotation.imageHeight / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[25]=( ( ( structImageRotation.imageHeight / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[26]=( structImageRotation.imageColorPlane % 256 );
		arrayHeaderRotation[27]=( structImageRotation.imageColorPlane / 256 );
		arrayHeaderRotation[28]=( structImageRotation.imageBitsPerPixel % 256 );
		arrayHeaderRotation[29]=( structImageRotation.imageBitsPerPixel / 256 );
		arrayHeaderRotation[30]=( structImageRotation.imageCompressionMethod % 256 );
		arrayHeaderRotation[31]=( ( structImageRotation.imageCompressionMethod / 256 ) % 256 );
		arrayHeaderRotation[32]=( ( ( structImageRotation.imageCompressionMethod / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[33]=( ( ( structImageRotation.imageCompressionMethod / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[34]=( structImageRotation.imageSizeOfImage % 256 );
		arrayHeaderRotation[35]=( ( structImageRotation.imageSizeOfImage / 256 ) % 256 );
		arrayHeaderRotation[36]=( ( ( structImageRotation.imageSizeOfImage / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[37]=( ( ( structImageRotation.imageSizeOfImage / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[38]=( structImageRotation.imageHPperM % 256 );
		arrayHeaderRotation[39]=( ( structImageRotation.imageHPperM / 256 ) % 256 );
		arrayHeaderRotation[40]=( ( ( structImageRotation.imageHPperM / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[41]=( ( ( structImageRotation.imageHPperM / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[42]=( structImageRotation.imageVPperM % 256 );
		arrayHeaderRotation[43]=( ( structImageRotation.imageVPperM / 256 ) % 256 );
		arrayHeaderRotation[44]=( ( ( structImageRotation.imageVPperM / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[45]=( ( ( structImageRotation.imageVPperM / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[46]=( structImageRotation.imageUsedColors % 256 );
		arrayHeaderRotation[47]=( ( structImageRotation.imageUsedColors / 256 ) % 256 );
		arrayHeaderRotation[48]=( ( ( structImageRotation.imageUsedColors / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[49]=( ( ( structImageRotation.imageUsedColors / 256 ) / 256 ) / 256 );
		arrayHeaderRotation[50]=( structImageRotation.imageImportantColors % 256 );
		arrayHeaderRotation[51]=( ( structImageRotation.imageImportantColors / 256 ) % 256 );
		arrayHeaderRotation[52]=( ( ( structImageRotation.imageImportantColors / 256 ) / 256 ) % 256 );
		arrayHeaderRotation[53]=( ( ( structImageRotation.imageImportantColors / 256 ) / 256 ) / 256 );

		for (int i=0; i<54; i++)
		{
			fprintf(pointerImageRotation, "%c", arrayHeaderRotation[i]);		
		}
		for (int i=0; i<1024; i++)
		{
			fprintf(pointerImageRotation, "%c", palleteGrey[i]);		
		}
		for (int i=0; i<structImageRotation.imageHeight; i++)
		{
			for (int j=0; j<structImageRotation.imageWidth; j++)
			{
				fprintf(pointerImageRotation, "%c", dataImageRotation[i][j]);		
			}
		}
		delete [] arrayRotation;
		delete [] dataImageRotation;
		delete [] arrayCheck;
		delete [] dataCheck;
		fclose(pointerImageRotation);
		printf("\n\nROTATION APPLIED SUCCESSFULLY\n");
		printf("\n\nSHOWING IMAGE DETAILS :\n");
		printf("\n\tIMAGE SIZE = %d Bytes" , structImageRotation.imageSize);
		printf("\n\tIMAGE WIDTH = %d" , structImageRotation.imageWidth);
		printf("\n\tIMAGE HEIGHT = %d" , structImageRotation.imageHeight);
		printf("\n\tIMAGE RESOLUTION = %d x %d" , structImageRotation.imageWidth, structImageRotation.imageHeight);
		printf("\n\tIMAGE COLOR = %d bit image" , structImageRotation.imageBitsPerPixel);
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenTransformation();
	return;
}

void screenShear(void)
{
	unsigned char arrayHeaderShear[54]={0};
	int parameterZ=0;
	char nameImageShear[50]={50};
	system("cls");
	printf("\n\n\t\t\tSHEAR SCREEN");
	printf("\n\nENTER NAME OF IMAGE TO BE WRITTEN : \n\t");
	for (int i=0;i<50;i++)
	{
		nameImageShear[i]=getch();
		printf("%c",nameImageShear[i]);
		if (nameImageShear[i]<33)
		{
			nameImageShear[i]=NULL;
			break;
		}
	}
	pointerImageShear=fopen(nameImageShear , "wb");
	if (pointerImageShear == NULL)
	{
		printf("\n\nUNABLE TO PERFORM SHEAR!");
	}
	else
	{
		printf("\n\nENTER SHEAR PARAMETER : \n");
		printf("\tSHEAR ANGLE = ");
		cin>>parameterZ;

		float angleShear=(parameterZ*3.142)/180;
		angleShear=tan(angleShear);

		bmpHeader structImageShear=structImageGreyScale;
	//	structImageShear.imageHeight+=2;
		structImageShear.imageWidth += (angleShear*structImageShear.imageHeight);
		structImageShear.imageSizeOfImage = structImageShear.imageWidth * structImageShear.imageHeight;
		structImageShear.imageSize = structImageShear.imageSizeOfImage + 1078;
		unsigned char * arrayShear = new unsigned char[structImageShear.imageWidth*structImageShear.imageHeight];
		unsigned char ** dataImageShear = new unsigned char*[structImageShear.imageHeight];
		for (int i=0; i<structImageShear.imageHeight; i++)
		{
			dataImageShear[i] = arrayShear + structImageShear.imageWidth*i;
		}
		for (int i=0; i<structImageShear.imageHeight; i++)
		{
			for (int j=0; j<structImageShear.imageWidth; j++)
			{
				dataImageShear[i][j]=0;
			}
		}
		int n=0;
		for (int i=0; i<structImageGreyScale.imageHeight; i++)
		{
			n=(int)(i*angleShear);
			for (int j=0; j<structImageGreyScale.imageWidth; j++)
			{
				dataImageShear[i][n]=dataImageGrey[i][j];
				n++;
			}
		}

		arrayHeaderShear[0]=( structImageShear.imageType % 256 );
		arrayHeaderShear[1]=( structImageShear.imageType / 256 );
		arrayHeaderShear[2]=( structImageShear.imageSize % 256 );
		arrayHeaderShear[3]=( ( structImageShear.imageSize / 256 ) % 256 );
		arrayHeaderShear[4]=( ( ( structImageShear.imageSize / 256 ) / 256 ) % 256 );
		arrayHeaderShear[5]=( ( ( structImageShear.imageSize / 256 ) / 256 ) / 256 );
		arrayHeaderShear[6]=( structImageShear.imageReserved % 256 );
		arrayHeaderShear[7]=( ( structImageShear.imageReserved / 256 ) % 256 );
		arrayHeaderShear[8]=( ( ( structImageShear.imageReserved / 256 ) / 256 ) % 256 );
		arrayHeaderShear[9]=( ( ( structImageShear.imageReserved / 256 ) / 256 ) / 256 );
		arrayHeaderShear[10]=( structImageShear.imageOffset % 256 );
		arrayHeaderShear[11]=( ( structImageShear.imageOffset / 256 ) % 256 );
		arrayHeaderShear[12]=( ( ( structImageShear.imageOffset / 256 ) / 256 ) % 256 );
		arrayHeaderShear[13]=( ( ( structImageShear.imageOffset / 256 ) / 256 ) / 256 );
		arrayHeaderShear[14]=( structImageShear.imageHeaderSize % 256 );
		arrayHeaderShear[15]=( ( structImageShear.imageHeaderSize / 256 ) % 256 );
		arrayHeaderShear[16]=( ( ( structImageShear.imageHeaderSize / 256 ) / 256 ) % 256 );
		arrayHeaderShear[17]=( ( ( structImageShear.imageHeaderSize / 256 ) / 256 ) / 256 );
		arrayHeaderShear[18]=( structImageShear.imageWidth % 256 );
		arrayHeaderShear[19]=( ( structImageShear.imageWidth / 256 ) % 256 );
		arrayHeaderShear[20]=( ( ( structImageShear.imageWidth / 256 ) / 256 ) % 256 );
		arrayHeaderShear[21]=( ( ( structImageShear.imageWidth / 256 ) / 256 ) / 256 );
		arrayHeaderShear[22]=( structImageShear.imageHeight % 256 );
		arrayHeaderShear[23]=( ( structImageShear.imageHeight / 256 ) % 256 );
		arrayHeaderShear[24]=( ( ( structImageShear.imageHeight / 256 ) / 256 ) % 256 );
		arrayHeaderShear[25]=( ( ( structImageShear.imageHeight / 256 ) / 256 ) / 256 );
		arrayHeaderShear[26]=( structImageShear.imageColorPlane % 256 );
		arrayHeaderShear[27]=( structImageShear.imageColorPlane / 256 );
		arrayHeaderShear[28]=( structImageShear.imageBitsPerPixel % 256 );
		arrayHeaderShear[29]=( structImageShear.imageBitsPerPixel / 256 );
		arrayHeaderShear[30]=( structImageShear.imageCompressionMethod % 256 );
		arrayHeaderShear[31]=( ( structImageShear.imageCompressionMethod / 256 ) % 256 );
		arrayHeaderShear[32]=( ( ( structImageShear.imageCompressionMethod / 256 ) / 256 ) % 256 );
		arrayHeaderShear[33]=( ( ( structImageShear.imageCompressionMethod / 256 ) / 256 ) / 256 );
		arrayHeaderShear[34]=( structImageShear.imageSizeOfImage % 256 );
		arrayHeaderShear[35]=( ( structImageShear.imageSizeOfImage / 256 ) % 256 );
		arrayHeaderShear[36]=( ( ( structImageShear.imageSizeOfImage / 256 ) / 256 ) % 256 );
		arrayHeaderShear[37]=( ( ( structImageShear.imageSizeOfImage / 256 ) / 256 ) / 256 );
		arrayHeaderShear[38]=( structImageShear.imageHPperM % 256 );
		arrayHeaderShear[39]=( ( structImageShear.imageHPperM / 256 ) % 256 );
		arrayHeaderShear[40]=( ( ( structImageShear.imageHPperM / 256 ) / 256 ) % 256 );
		arrayHeaderShear[41]=( ( ( structImageShear.imageHPperM / 256 ) / 256 ) / 256 );
		arrayHeaderShear[42]=( structImageShear.imageVPperM % 256 );
		arrayHeaderShear[43]=( ( structImageShear.imageVPperM / 256 ) % 256 );
		arrayHeaderShear[44]=( ( ( structImageShear.imageVPperM / 256 ) / 256 ) % 256 );
		arrayHeaderShear[45]=( ( ( structImageShear.imageVPperM / 256 ) / 256 ) / 256 );
		arrayHeaderShear[46]=( structImageShear.imageUsedColors % 256 );
		arrayHeaderShear[47]=( ( structImageShear.imageUsedColors / 256 ) % 256 );
		arrayHeaderShear[48]=( ( ( structImageShear.imageUsedColors / 256 ) / 256 ) % 256 );
		arrayHeaderShear[49]=( ( ( structImageShear.imageUsedColors / 256 ) / 256 ) / 256 );
		arrayHeaderShear[50]=( structImageShear.imageImportantColors % 256 );
		arrayHeaderShear[51]=( ( structImageShear.imageImportantColors / 256 ) % 256 );
		arrayHeaderShear[52]=( ( ( structImageShear.imageImportantColors / 256 ) / 256 ) % 256 );
		arrayHeaderShear[53]=( ( ( structImageShear.imageImportantColors / 256 ) / 256 ) / 256 );

		for (int i=0; i<54; i++)
		{
			fprintf(pointerImageShear, "%c", arrayHeaderShear[i]);		
		}
		for (int i=0; i<1024; i++)
		{
			fprintf(pointerImageShear, "%c", palleteGrey[i]);		
		}
		for (int i=0; i<structImageShear.imageHeight; i++)
		{
			for (int j=0; j<structImageShear.imageWidth; j++)
			{
				fprintf(pointerImageShear, "%c", dataImageShear[i][j]);		
			}
		}
		delete [] arrayShear;
		delete [] dataImageShear;
		fclose(pointerImageShear);
		printf("\n\nSHEAR APPLIED SUCCESSFULLY\n");
		printf("\n\nSHOWING IMAGE DETAILS :\n");
		printf("\n\tIMAGE SIZE = %d Bytes" , structImageShear.imageSize);
		printf("\n\tIMAGE WIDTH = %d" , structImageShear.imageWidth);
		printf("\n\tIMAGE HEIGHT = %d" , structImageShear.imageHeight);
		printf("\n\tIMAGE RESOLUTION = %d x %d" , structImageShear.imageWidth, structImageShear.imageHeight);
		printf("\n\tIMAGE COLOR = %d bit image" , structImageShear.imageBitsPerPixel);
	}
	printf("\n\nPress any key to return . . . ");
	_getch();
	screenTransformation();
	return;
}