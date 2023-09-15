#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"

#pragma warning ( disable : 4996 )

#define O 7
#define N 35

void PrintObjects(HeaderD* pStruct7);
int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode);
int CheckNewID(HeaderD* pStruct7, char* pNewID);
void CreateNewFirstHeader(HeaderD** pStruct, char* pNewID);
void CreateNewMiddleHeader(HeaderD* pStruct, char* pNewID);
void CreateNewLastHeader(HeaderD* pStruct, char* pNewID);

int main()
{
	HeaderD *pStruct7 = GetStruct7(O, N);

	PrintObjects(pStruct7);

	char pNewID[6] = {"Iok"};
	int NewCode = 13;  

	CheckNewID(pStruct7, pNewID);

	return 0;
}

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode)
{
	if (!CheckNewID(*pStruct7, pNewID))
	{
		return 0;
	}

	//check if header exists 
	
	
	//if doesnt exist fix the poistion 
	//create new header 

	//if exists 
	//check in what position it fits in 
	//create new object 

}

//checks if header exists, if not creats a new one 
HeaderD* FindHeader(HeaderD** pStruct, char* pNewID)
{
	HeaderD* pHeaderTemp = *pStruct;

	int counter = 0; 

	//some statements may not be needed, CHECK AND THINK EVERY LINE THROUGH AGAIN
	while (pHeaderTemp != NULL)
	{
		if ((int)pHeaderTemp->cBegin == (int)pNewID[0])
		{
			return pHeaderTemp;
		}
		else if ((!counter) && 
			((int)pHeaderTemp->cBegin != (int)pNewID[0]) &&
			((int)pHeaderTemp->cBegin - (int)pNewID[0] > 0))
		{
			CreateNewFirstHeader(pStruct, pNewID); 
			break;
		}
		else if ((pHeaderTemp->pNext == NULL) && 
			((int)pHeaderTemp->cBegin != (int)pNewID[0]))
		{
			CreateNewLastHeader(pHeaderTemp, pNewID); 
			break;
		}
		else if (((int)pHeaderTemp->cBegin - (int)pNewID[0] < 0) &&
			((int)pHeaderTemp->pNext->cBegin - (int)pNewID[0] > 0))
		{
			CreateNewMiddleHeader(pHeaderTemp, pNewID); 
			break; 
		}

		pHeaderTemp = pHeaderTemp->pNext;

		counter++; 
	}

	return pHeaderTemp; 
}

void CreateNewFirstHeader(HeaderD** pStruct, char* pNewID)
{
	HeaderD* pHeaderTemp = *pStruct; 
	HeaderD* pNewHeader = (HeaderD*)malloc(sizeof(HeaderD));

	if (pNewHeader == NULL)
	{
		exit(EXIT_FAILURE);
	}

	pNewHeader->cBegin = pNewID[0];// check if works 

	//think maybe you should use malloc for pObject already 
	pNewHeader->pNext = pHeaderTemp; 
	pNewHeader->pPrior = NULL;
	pNewHeader->pObject = NULL; 

	pStruct = &pNewHeader;
}

void CreateNewMiddleHeader(HeaderD* pStruct, char* pNewID)
{
	HeaderD* pHeaderTemp = pStruct;
	HeaderD* pNewHeader = (HeaderD*)malloc(sizeof(HeaderD));

	if (pNewHeader == NULL)
	{
		exit(EXIT_FAILURE);
	}

	pNewHeader->cBegin = pNewID[0];// check if works 
	//think maybe you should use malloc for pObject already 
	pNewHeader->pNext = pHeaderTemp->pNext;
	pNewHeader->pPrior = pHeaderTemp;
	pNewHeader->pObject = NULL;
}

void CreateNewLastHeader(HeaderD* pStruct, char* pNewID)
{
	HeaderD* pHeaderTemp = pStruct;
	HeaderD* pNewHeader = (HeaderD*)malloc(sizeof(HeaderD));

	if (pNewHeader == NULL)
	{
		exit(EXIT_FAILURE);
	}

	pNewHeader->cBegin = pNewID[0];// check if works 
	//think maybe you should use malloc for pObject already 
	pNewHeader->pNext = NULL;
	pNewHeader->pPrior = pHeaderTemp;
	pNewHeader->pObject = NULL;
}

int CheckNewID(HeaderD* pStruct7, char* pNewID) 
{
	//checks if first letter is uppercase
	if (((int)pNewID[0] - 90 > 0) || ((int)pNewID[0] - 65 < 0))
	{
		//printf("fail %d\n", (int)pNewID[0]);
		return 0;
	}

	//checks if other letters are lower case english letters 
	for (int i = 1; (unsigned)i < (unsigned)strlen(pNewID); i++)
	{
		if (((int)pNewID[i] - 122 > 0) || ((int)pNewID[i] - 97 < 0))
		{
			//printf("fail %d\n", (int)pNewID[i]);
			return 0; 
		}
	}

	HeaderD* pHeadTemp = pStruct7;//saves the pointer to the next header

	Object7* pObjTemp; 

	//check if ID allready exists 
	while (pHeadTemp != NULL)
	{
		if ((int)pHeadTemp->cBegin == (int)pNewID[0])
		{
			pObjTemp = (Object7*)pHeadTemp->pObject;

			while (pObjTemp != NULL)
			{
				if (!strcmp(pObjTemp->pID, pNewID))
				{
					//printf("DEBUG\n"); 
					return 0; 
				}

				pObjTemp = pObjTemp->pNext;
			}
		}

		//set temp as next header
		pHeadTemp = pHeadTemp->pNext;
	}

	return 1; 
}

void PrintObjects(HeaderD* pStruct7)
{
	int i = 1;
	HeaderD* pHeadTemp = pStruct7;//saves the pointer to the next header
	
	Object7* pObjTemp = (Object7*)pStruct7->pObject;

	while (pHeadTemp != NULL)
	{
		//print out character from header 
		printf("%c\n", pHeadTemp->cBegin);

		while (pObjTemp != NULL)
		{
			//print out all data from object 
			printf(" %d) %s %lu %02d %s %04d\n", i,
				pObjTemp->pID,
				pObjTemp->Code,
				pObjTemp->pDate2->Day,
				pObjTemp->pDate2->Month,
				pObjTemp->pDate2->Year);

			//get next object 
			pObjTemp = pObjTemp->pNext;
			i++;
		}

		//set temp as next header
		pHeadTemp = pHeadTemp->pNext;


		// maybe put in front of object check loop for smaller code 
		//check if next header exists 
		if (pHeadTemp != NULL)
		{
			pObjTemp = (Object7*)pHeadTemp->pObject;//find a new starting object from header
		}
	}
}