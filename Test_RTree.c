#include "Test_RTree.h"

void runTestNbh(DataHdr dataList1, RHdrNd rTree1)
{	
	Data currData = dataList1->dataClstElem;
	int i = 0;
	for (i=0;i<dataList1->uiCnt;i++)
	{
		//printf("\nTesting for Point %d",i);
		int val = RgetNeighborHood(rTree1,currData+i);
		RfreeNeighborhood(currData+i);
	}
    return;
}


void runTestOneNN(DataHdr dataList1, RHdrNd rTree1)
{
	Data currData = dataList1->dataClstElem;
	Data NN, tempNN;
	int i = 0;

	// NN = (Data) RgetKNN(rTree1,currData+49,dataList1);
	// tempNN = (Data) bruteForceOneNN(dataList1,currData+49);
	// CompareOneNN(NN,tempNN,currData+49);


	for (i=0;i<dataList1->uiCnt;i++)
	{
		//printf("\nTesting for Point %d",i);
		//if(i==49)
			//getchar();
		NN = (Data) RgetOneNN(rTree1,currData+i,dataList1);
		//tempNN = (Data) bruteForceOneNN(dataList1,currData+i);

		//CompareOneNN(NN,tempNN,currData+i);
		
	}	

    return;
}

void runTestKNN(DataHdr dataList1, RHdrNd rTree1, int k)
{
	Data currData = dataList1->dataClstElem;
	Data *NN, *tempNN;
	int i = 0;

	// NN = (Data) RgetKNN(rTree1,currData+49,dataList1);
	// tempNN = (Data) bruteForceOneNN(dataList1,currData+49);
	// CompareOneNN(NN,tempNN,currData+49);


	for (i=0;i<dataList1->uiCnt;i++)
	{
		//printf("\nTesting for Point %d : ",i);
		//printData(currData+i);
		//if(i==49)
			//getchar();
		NN = (Data*) RgetKNN(rTree1,currData+i,dataList1,k);
		//printKNNList(NN,currData+i,k);
		//tempNN = (Data*) bruteForceKNN(dataList1,currData+i,k);
		//printKNNList(tempNN,currData+i,k);		

		//CompareKNN(NN,tempNN,currData+i,k);

		free(NN);
		//free(tempNN);
		
	}	

    return;
}

void runTestKNNOnSample(DataHdr dataList1, DataHdr sampledDataList, RHdrNd rTree1, int k)
{
	Data currData = sampledDataList->dataClstElem;
	Data *NN, *tempNN;
	int i = 0;

	// NN = (Data) RgetKNN(rTree1,currData+49,dataList1);
	// tempNN = (Data) bruteForceOneNN(dataList1,currData+49);
	// CompareOneNN(NN,tempNN,currData+49);


	for (i=0;i<sampledDataList->uiCnt;i++)
	{
		//printf("\nTesting for Point %d : ",i);
		//printData(currData+i);
		//if(i==49)
			//getchar();
		NN = (Data*) RgetKNN(rTree1,currData+i,dataList1,k);
		//printKNNList(NN,currData+i,k);
		//tempNN = (Data*) bruteForceKNN(dataList1,currData+i,k);
		//printKNNList(tempNN,currData+i,k);		

		//CompareKNN(NN,tempNN,currData+i,k);

		free(NN);
		//free(tempNN);
		
	}	

    return;
}

Data bruteForceOneNN(DataHdr dataList1, Data dataPoint)
{
	int i = 0;
	double dist=0;
	double globalDist = UNDEFINED;
	Data globalOneNN;
	for(i=0;i<dataList1->uiCnt;i++)
	{
		if(((dataList1->dataClstElem)+i)->iNum != dataPoint->iNum)
		{
			dist = calculateDistance(((dataList1->dataClstElem)+i)->iData,dataPoint->iData);
			if(dist<globalDist)
			{
				globalOneNN = (Data) ((dataList1->dataClstElem)+i);
				globalDist = dist;
			}
		}

	}

	return globalOneNN;
}

Data * bruteForceKNN(DataHdr dataList1, Data dataPoint, int k)
{
    Data * KNNList = (Data *) malloc(sizeof(Data)*k);
    int listSize=0; int x; int m; int pivot = 0;

    KNNDistNode KNNDistList = (KNNDistNode) malloc((sizeof(*KNNDistList)) * (dataList1->uiCnt));
    KNNDistNode tempDistNode = (KNNDistNode) malloc(sizeof(*KNNDistList));
    KNNDistNode tempDistNodePtr;
    double tempDist = UNDEFINED;

    for(x = 0; x < dataList1->uiCnt; x++)
    {
        KNNDistList[x].data = (dataList1->dataClstElem)+x;
        KNNDistList[x].distance = calculateDistance(((dataList1->dataClstElem)+x)->iData,dataPoint->iData);
    }

    // now sort

    for (x=0;x<(2*k);x++)
    {
    	tempDist = UNDEFINED;

        for(m=pivot;m<(dataList1->uiCnt);m++)
        {
            if(KNNDistList[m].distance < tempDist)
            {                
                tempDist = KNNDistList[m].distance;
                tempDistNodePtr = KNNDistList + m;
            }

        }

        // swapping
        tempDistNode->distance =  KNNDistList[pivot].distance;
        tempDistNode->data = KNNDistList[pivot].data;

        KNNDistList[pivot].distance = tempDistNodePtr->distance;
        KNNDistList[pivot].data = tempDistNodePtr->data;

        tempDistNodePtr->distance = tempDistNode->distance;
        tempDistNodePtr->data = tempDistNode->data;

        pivot++;        
    }

    // report KNN now
    x = 0; m =0;
    while((m<k) && (x < dataList1->uiCnt))
    {
        if(KNNDistList[x].data->iNum != dataPoint->iNum)
        {
        	KNNList[m] = KNNDistList[x].data;        	
        	m++;
        }
        
        x++;        
    }

    // int i = 0;
    // double dist=0;
    // double globalDist = UNDEFINED;  
    // for(i=0;i<dataList1->uiCnt;i++)
    // {
    //     if(((dataList1->dataClstElem)+i)->iNum != dataPoint->iNum)
    //     {
    //         dist = TcalculateDistance(((dataList1->dataClstElem)+i)->iData,dataPoint->iData);
    //         if(dist<globalDist || listSize < k)
    //         {               
    //             globalDist = updateKNNList(KNNList, dataPoint, (dataList1->dataClstElem)+i, &listSize, k);
    //         }
    //     }

    // }

    free(KNNDistList);
    free(tempDistNode);

    return KNNList;

}

int updateKNNList(Data * KNNList, Data datapoint, Data toBeInsertedPoint, int * listSizePtr, int k)
{
	//*listSizePtr++;

	int i =0,j=(*listSizePtr);
	
	if(*listSizePtr==0)
	{
		KNNList[0] = toBeInsertedPoint;
		(*listSizePtr)++;
		return calculateDistance(KNNList[0]->iData,datapoint->iData);

	}


	for(i=0;i<(*listSizePtr);i++)
	{
		if(calculateDistance(KNNList[i]->iData,datapoint->iData) > calculateDistance(toBeInsertedPoint->iData,datapoint->iData))
		{			
			break;
		}
	}

	if(i==j && j < k)
	{
		KNNList[j] = toBeInsertedPoint;
		(*listSizePtr)++;

		return calculateDistance(KNNList[(*listSizePtr)-1]->iData,datapoint->iData);

	}

	if((*listSizePtr) < k && i <= ((*listSizePtr)-1))
	{
		KNNList[j] = KNNList[j-1];
	}
	

	while(j-1>i)
	{
		// free jth list size ptr and then make this change
		KNNList[j-1] = KNNList[j-2];
		j--;
	}

	

	KNNList[i] = toBeInsertedPoint;
	if((*listSizePtr) < k )
	{
		(*listSizePtr)++;
	}
	

	return calculateDistance(KNNList[(*listSizePtr)-1]->iData,datapoint->iData);

}

void CompareOneNN(Data first, Data second, Data dataPoint)
{
	if(calculateDistance(first->iData,dataPoint->iData) != calculateDistance(second->iData,dataPoint->iData))
	{
		printf("mismatch in oneNN found for");

		printData(dataPoint);
		printf("\n");
		printData(first);
		printf("\n");
		printData(second);

		getchar();
	}

	return;

}

void CompareKNN(Data* first, Data* second, Data dataPoint, int k)
{
	int ctr = 0; int flag =0;

	while(ctr<k)
	{
		if(calculateDistance(first[ctr]->iData,dataPoint->iData) != calculateDistance(second[ctr]->iData,dataPoint->iData))
		{
			printf("\nmismatch in KNN found for");
			printData(dataPoint);
			printf("\n");
			flag=1;			
			break;			
		}
		ctr++;
	}

	if(flag == 1)
	{
		printKNNList(first,dataPoint,k);
		printKNNList(second,dataPoint,k);
		getchar();
	}

	return;
}

void printKNNList(Data * KNNList, Data dataPoint, int k)
{
	int ctr = 0;

	while(ctr<k)
	{
		printf("\n");
		printData(KNNList[ctr]);
		printf("\t %lf",calculateDistance(KNNList[ctr]->iData,dataPoint->iData));
		ctr++;
	}

	return;
}
