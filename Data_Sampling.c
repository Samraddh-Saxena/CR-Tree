#include "Data_Sampling.h"

DataHdr sampleData(DataHdr dataList1, double percent)
{
	double fraction = (double) (percent / 100);

	int noOfPoints = (int)floor((fraction * (dataList1->uiCnt)));
	int ctr = 0; int x;

	DataHdr tempDataList = initDataHdr(noOfPoints);
	DataPoint dataPointTemp = NULL;
	int randomNo;
	int counterArray[noOfPoints];
	int counterArraySize =0;
	Boolean flag;
	int tempCtr;
	int iDim;
    
    if(tempDataList == NULL)
        return NULL;

    srand (time(NULL));

    while(ctr < dataList1->uiCnt && counterArraySize <= noOfPoints)
    {   
    	// generate a random index

    	randomNo = rand() % dataList1->uiCnt;

    	// check whether the index generated is not repeating    	
    	
    	if (isFoundInArray(counterArray,counterArraySize,randomNo) == TRUE)
    	{
    		flag = TRUE;
    		while(flag == TRUE)
    		{
    			randomNo = (randomNo + 1) % dataList1->uiCnt;
    			if(isFoundInArray(counterArray,counterArraySize,randomNo) == FALSE)
    			{
    				flag = FALSE;
    				break;
    			}
    		}
    		
    	}

    	counterArray[counterArraySize] = randomNo;
    	counterArraySize++;

    	dataPointTemp = (DataPoint)malloc(DIMENSION *sizeof(dataPoint));

        for(iDim = 0; iDim < DIMENSION; iDim++)
        	dataPointTemp[iDim] = dataList1->dataClstElem[randomNo].iData[iDim];
        
        insertDataLstElem(tempDataList, dataPointTemp);
        ctr++;
    }

    return tempDataList;
}

Boolean isFoundInArray(int array [], int arraySize, int index)
{
	int x = 0; int flag = 0;

	for(x = 0; x < arraySize; x++)
	{
		if(array[x] == index)
		{
			flag = 1;
			break;
		}

	}

	if (flag == 1)
		return TRUE;
	else
		return FALSE;

}