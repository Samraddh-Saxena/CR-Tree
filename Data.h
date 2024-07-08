#ifndef __DATA_H
#define __DATA_H
#include <stdio.h>
#include "Def.h"

DataHdr initDataHdr(int size_data);
void insertDataLstElem(DataHdr dataHdrInfo, DataPoint iData);
DataHdr readData(char *strFileName);
void printDataLst(DataHdr dataHdrInfo);
void printData(Data dataPoint);
Boolean isDataLstEmpty(DataHdr dataHdrInfo);
void freeDataList(DataHdr dataList1);
void writeDataListToFile(DataHdr dataList1, char * fileName);

#endif