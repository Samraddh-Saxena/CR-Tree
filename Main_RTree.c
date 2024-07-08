#include "Data.h"
#include "RList.h"
#include "Test_RTree.h"
#include "Data_Sampling.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{	

	//./output $path1$1 output_$1\_EPS=$Epsilon\_MINPOINTS=$MINPOINTS.txt $m $M $Epsilon $MINPOINTS $UNDEFINED

	EPS = atof(argv[5]);
	// EPS=0.5;
	//printf("EPS is %lf\n", EPS);
	MINPOINTS = atoi(argv[6]);
	// MINPOINTS=1;
	RMINENTRIES = atoi(argv[3]);
	// RMINENTRIES=2;
	//printf("RMINENTRIES is %d\n", RMINENTRIES);
	RMAXENTRIES = atoi(argv[4]);
	// RMAXENTRIES=4;
	//printf("RMAXENTRIES is %d\n", RMAXENTRIES);
	UNDEFINED = atoi(argv[7]);
	// UNDEFINED=9;

	int k = atoi(argv[8]);
	// int k= 6;

	char * QT = (char *)argv[10];
	// char* QT= "NBHQUERY";

	//printf("k is %d\n", k);

	int percent = atoi(argv[9]);

	// declarations for dataList and RTree
	
	DataHdr dataList1;
	DataHdr sampledDataList;


	// int noOfPoints,i,iCnt;
	// dataList1 = readData("3D_spatial_network_transformed_dense_cells_more_than_3000pts_increased_to_10000pts_withNBH_increased"); //passing filename
	dataList1 = readData(argv[1]); //passing filename
	// dataList1 = readData("3D_spatial_network_transformed");
	//printDataLst(dataList1);

	sampledDataList = readData(argv[9]);
		// sampledDataList= readData("3D_spatial_network_transformed");

	sampledDataList = sampleData(dataList1,percent);

	//printf("%d\n", sampledDataList->uiCnt);
	//printDataLst(sampledDataList);

	// writeDataListToFile(sampledDataList, "3D_spatial_network_transformed_75percent.txt", percent);

	RHdrNd rTree1 = (RHdrNd) RbuildRTree(dataList1);
	RprintTree(rTree1);
	printf("CRTree Building successfully completed\n");

	// tester();
	// printf("it worked\n");
	// runTestOneNN(dataList1,rTree1);
	//runTestKNN(dataList1,rTree1,k);

	//runTestKNNOnSample(dataList1,sampledDataList,rTree1,4);

	if(strcmp(QT,"NBHQUERY")==0)
	{
		printf("\nGoing for NBH QUERY\n");
		runTestNbh(sampledDataList,rTree1);

	}
	else if(strcmp(QT,"KNNQUERY")==0)
	{
		//printf("\nGoing for KNN QUERY\n");
		runTestKNNOnSample(dataList1,sampledDataList,rTree1,4);
	}
	

	// freeRTree(rTree1);
	// freeDataList(dataList1);
	// freeDataList(sampledDataList);

    return (0);
}
