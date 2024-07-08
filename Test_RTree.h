#pragma once
#include "Data.h"
#include "RList.h"
#include "RTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void runTestNbh(DataHdr dataList1, RHdrNd rTree1);
void runTestOneNN(DataHdr dataList1, RHdrNd rTree1);
void runTestKNN(DataHdr dataList1, RHdrNd rTree1, int k);
void runTestKNNOnSample(DataHdr dataList1, DataHdr sampledDataList, RHdrNd rTree1, int k);
Data bruteForceOneNN(DataHdr dataList1, Data dataPoint);
Data * bruteForceKNN(DataHdr dataList1, Data dataPoint, int k);
int updateKNNList(Data * KNNList, Data datapoint, Data toBeInsertedPoint, int * listSizePtr, int k);
void CompareOneNN(Data first, Data second, Data dataPoint);
void CompareKNN(Data* first, Data* second, Data dataPoint, int k);
void printKNNList(Data * KNNList, Data dataPoint, int k);

