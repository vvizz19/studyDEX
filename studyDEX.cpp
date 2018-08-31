#include <stdio.h>
#include <memory.h>
#include "studyDEX.h"

int main(int argc, char* argv[])
{
	struct DexHeader stDexHeader = {0};
	FILE*	pDexFile = NULL;		// pointer of DEX file
	char*	strFileContent = NULL;	// content of DEX file
	long	lFileSize = 0;			// file size of DEX file
	long	lFileReaded = 0;		// the real size of read file
	int		i = 0;

	if (NULL != (pDexFile = fopen(".\\test.dex", "rb")))
	{
		fseek(pDexFile, 0, SEEK_END);	// move the file pointer to end of file 
		lFileSize = ftell(pDexFile);	// get the file size (Bytes)
		fseek(pDexFile, 0, SEEK_SET);	// move the file pointer to begin of file

		printf("DEX file size = %d Bytes.\n", lFileSize);

		strFileContent = new char[lFileSize + 1];	// malloc the memory to save the file content 
		memset(strFileContent, 0, lFileSize+1);
		lFileReaded = fread(strFileContent, sizeof(char), lFileSize, pDexFile);	// read file 
		if (lFileSize != lFileReaded)
		{
			printf("\n\n**** ****\nfread is failed.%d, %d, error:%d \n**** ****\n\n", lFileSize, lFileReaded, feof(pDexFile));
		}

	
		printf("\n\n ---- ---- ---- ----\n\n");
	

		// read the dex header - default size: 0x70
		fseek(pDexFile, 0, SEEK_SET);						// move file pointer to begin of file
		fread(&stDexHeader, sizeof(char), 0x70, pDexFile);	// read file - DEX Header
		
		printf("magic:\t\t ");
		for (i = 0; i < 8; ++i)
		{
			printf("%02X ", stDexHeader.magic[i]);
		}

		printf("\nchecksum:\t 0x%08X", stDexHeader.checksum);
				
		printf("\nsignature:\t ");
		for (i = 0; i < 20; ++i)
		{
			printf("%02X ", stDexHeader.signature[i]);
		}

		printf("\nfileSize:\t 0x%0X - %d(Ê®½øÖÆ)", stDexHeader.fileSize, stDexHeader.fileSize);

		printf("\nheaderSize:\t 0x%0X", stDexHeader.headerSize);

		printf("\nendianTag:\t ");
		for(i = 0; i < 4; ++i)
		{
			printf("%02X ", (unsigned char)(stDexHeader.endianTag >> (i*8)));
		}

		printf("\nlinkSize:\t 0x%08X", stDexHeader.linkSize);
		printf("\nlinkOff:\t 0x%08X", stDexHeader.linkOff);
		
		printf("\nmapOff:\t\t 0x%08X", stDexHeader.mapOff);
		
		printf("\nstringIdsSize:\t 0x%08X", stDexHeader.stringIdsSize);
		printf("\nstringIdsOff:\t 0x%08X", stDexHeader.stringIdsOff);
		
		printf("\ntypeIdsSize:\t 0x%08X", stDexHeader.typeIdsSize);
		printf("\ntypeIdsOff:\t 0x%08X", stDexHeader.typeIdsOff);
		
		printf("\nprotoIdsSize:\t 0x%08X", stDexHeader.protoIdsSize);
		printf("\nprotoIdsOff:\t 0x%08X", stDexHeader.protoIdsOff);
		
		printf("\nfieldIdsSize:\t 0x%08X", stDexHeader.fieldIdsSize);
		printf("\nfieldIdsOff:\t 0x%08X", stDexHeader.fieldIdsOff);
		
		printf("\nmethodIdsSize:\t 0x%08X", stDexHeader.methodIdsSize);
		printf("\nmethodIdsOff:\t 0x%08X", stDexHeader.methodIdsOff);
		
		printf("\nclassDefsSize:\t 0x%08X", stDexHeader.classDefsSize);
		printf("\nclassDefsOff:\t 0x%08X", stDexHeader.classDefsOff);
		
		printf("\ndataSize:\t 0x%08X", stDexHeader.dataSize);
		printf("\ndataOff:\t 0x%08X", stDexHeader.dataOff);


		printf("\n\n");
	}
	
	if (NULL != pDexFile)
	{
		fclose(pDexFile);
		pDexFile = NULL;
	}

	return 0;
}