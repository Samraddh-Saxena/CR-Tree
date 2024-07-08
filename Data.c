#include <stdlib.h>
#include "Data.h"

void insertDataLstElem(DataHdr dataHdrInfo, DataPoint iData)
{
    //return insertDataLstNd(dataHdrInfo, initData(iData));
    Data dataClstElem = dataHdrInfo->dataClstElem + dataHdrInfo->uiCnt;

    //dataClstElem->timestamp = 0;//addded by RBK
    dataClstElem->iData = iData;
    //dataClstElem->core_distance = UNDEFINED;
    //dataClstElem->reachability_distance = UNDEFINED;
    dataHdrInfo->uiCnt++;
    dataClstElem->iNum=dataHdrInfo->uiCnt;
    //dataClstElem->isProcessed = FALSE;
    //dataClstElem->core_tag = FALSE;
    //dataClstElem->neighbors = NULL;

    return;

}

// initializes data header of size size
DataHdr initDataHdr(int size)
{   DataHdr dataHdrInfo = (DataHdr)malloc(sizeof(struct dataHdr));
    assert(dataHdrInfo!=NULL);

    // if(dataHdrInfo == NULL)
    //     return NULL;

    dataHdrInfo->uiCnt = 0;
    dataHdrInfo->dataClstElem=(Data)malloc(sizeof(struct data)*size);
    assert(dataHdrInfo->dataClstElem!=NULL);
    return dataHdrInfo;
}


DataHdr readData(char *strFileName)
{   // read data from the file
    int iCnt = 0;
    int iDim = 0;
    int count=1;
    int noOfPoints;
    if(strFileName == NULL)
        return NULL;

    FILE *filP = fopen(strFileName, "r");

    if(filP == NULL)
        return NULL;
    //DataPoint *ptrData = (DataPoint *) malloc( iNumber * sizeof(DataPoint) );
    DataPoint dataPointTemp = NULL;
    fscanf(filP,"%d",&noOfPoints);
    fscanf(filP,"%d",&DIMENSION);
    DataHdr dataList = initDataHdr(noOfPoints);

    if(dataList == NULL)
        return NULL;
    while(!feof(filP))
    {   dataPointTemp = (DataPoint)malloc(DIMENSION *sizeof(dataPoint));

        for(iDim = 0; iDim < DIMENSION - 1; iDim++)
            fscanf(filP, "%lf"DELIM, &dataPointTemp[iDim]);

        fscanf(filP, "%lf\n", &dataPointTemp[iDim]);      
        insertDataLstElem(dataList, dataPointTemp);
    }

    fclose(filP);

    return dataList;
}


void printDataLst(DataHdr dataHdrInfo)
{    //printf("++++++++++CALL TO PRINT THE LIST__________+++++++++++++++++++\n");
    if(isDataLstEmpty(dataHdrInfo))
        return;
    //printf("++++++++++CALL TO PRINTing THE representative  LIST +++++++++++++++++++\n");
    int iCnt = 0,j;
    //DataNd dataTemp = dataHdrInfo->dataFirstNd;
    for(j=0;j<dataHdrInfo->uiCnt;j++)
    {
        printf("RecNum %d\t",dataHdrInfo->dataClstElem[j].iNum);
        for(iCnt = 0; iCnt < DIMENSION; iCnt++ )
            printf("%lf ", dataHdrInfo->dataClstElem[j].iData[iCnt] );
        printf("\n");

    }

  return;
}

void printData(Data dataPoint)
{
    printf("RecNum %d\t",dataPoint->iNum);
    int iCnt=0;
        for(iCnt = 0; iCnt < DIMENSION; iCnt++)
            printf("%lf ", dataPoint->iData[iCnt] );

    return;
}

Boolean isDataLstEmpty(DataHdr dataHdrInfo)
{
    return(dataHdrInfo == NULL || dataHdrInfo->uiCnt == 0) ? TRUE : FALSE;
}

void freeDataList(DataHdr dataList1)
{
    int i;
    for(i=0;i<dataList1->uiCnt;i++)
        free((dataList1->dataClstElem+i)->iData);
    free(dataList1->dataClstElem);
    free(dataList1);

    return;
}

void writeDataListToFile(DataHdr dataList1, char * fileName)
{
    
    FILE *filP = fopen(fileName, "w");

    int i =0; int j=0;

    fprintf(filP, "%d\n", dataList1->uiCnt);
    fprintf(filP, "%d\n", DIMENSION);

    for(i=0;i<dataList1->uiCnt;i++)
    {
        for (j = 0; j < DIMENSION; j++)
        {
            fprintf(filP, "%lf", dataList1->dataClstElem[i].iData[j]);
            if(j!=(DIMENSION-1))
            {
                fprintf(filP," ");
            }
        }

        fprintf(filP,"\n");
    }

    fclose(filP);

    return;

}
