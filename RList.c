#include "RList.h"

RHdrNd RinitHdrNd()
{   
	RHdrNd HdrNdLst = (RHdrNd)malloc(sizeof(struct RhdrNd));
	assert(HdrNdLst!=NULL);    

	HdrNdLst->uiCnt = 0;
	HdrNdLst->ptrFirstNd = NULL;
	HdrNdLst->ptrParentNd = NULL;
	
	return HdrNdLst;
}

RLstNd RinitLstNd(RTreeNode tnInfo)
{   
	RLstNd LstNdElem = (RLstNd)malloc(sizeof(struct RlstNd));
	assert(LstNdElem!=NULL);	

	LstNdElem->tnInfo = tnInfo;
	LstNdElem->ptrChildLst = NULL;
	LstNdElem->ptrNextNd = NULL;
	
	return LstNdElem;	
}

void RinsertLstElem(RHdrNd HdrNdLst, RTreeNode tnInfo)
{	
	RinsertLstNd(HdrNdLst, RinitLstNd(tnInfo));
	return;
}

void RinsertLstNd(RHdrNd HdrNdLst, RLstNd LstNdElem)
{   
	if(LstNdElem == NULL || HdrNdLst == NULL)
		return;
    LstNdElem->ptrNextNd = HdrNdLst->ptrFirstNd;
	HdrNdLst->ptrFirstNd = LstNdElem;
	HdrNdLst->uiCnt++;
	
	return;
}

Boolean RisLstEmpty(RHdrNd HdrNdLst)
{   
	return(HdrNdLst->ptrFirstNd == NULL || HdrNdLst->uiCnt == 0) ? TRUE : FALSE;
}

RLstNd RdeleteLstElem(RHdrNd HdrNdLst, RTreeNode tnInfo)
{
    if(RisLstEmpty(HdrNdLst))
    return NULL;
  RTreeNode tnInfoTemp = NULL;
  Boolean bIsFound = FALSE;
  RLstNd LstNdTemp = HdrNdLst->ptrFirstNd;
  if(LstNdTemp->tnInfo == tnInfo)
    { return RdeleteLstFirst(HdrNdLst);
        /*
    HdrNdLst->ptrFirstNd = LstNdTemp->ptrNextNd;
    LstNdTemp->ptrNextNd = NULL;
    HdrNdLst->uiCnt--;
    tnInfoTemp = LstNdTemp->tnInfo;
    LstNdTemp->tnInfo = NULL;
    free( LstNdTemp );
    return tnInfoTemp;
        */
  }

  while(LstNdTemp->ptrNextNd != NULL)
    {   if(LstNdTemp->ptrNextNd->tnInfo == tnInfo)
        {   bIsFound = TRUE;
      // LstNdTemp = deleteNextNd(HdrNdLst, LstNdTemp);
      // break;     
      return RdeleteNextNd(HdrNdLst, LstNdTemp);
    }   
    LstNdTemp = LstNdTemp->ptrNextNd;
  }
  
    //tnInfoTemp = LstNdTemp->tnInfo;
    //LstNdTemp->tnInfo = NULL;
    //free( LstNdTemp );
    //return (bIsFound)?LstNdTemp:NULL;
  return NULL;
}

RLstNd RdeleteLstFirst(RHdrNd HdrNdLst)
{   
	if(RisLstEmpty(HdrNdLst))
		return NULL;
	RTreeNode tnInfoTemp = NULL;
	RLstNd lstNdTemp = HdrNdLst->ptrFirstNd;

	HdrNdLst->ptrFirstNd = lstNdTemp->ptrNextNd;
	HdrNdLst->uiCnt--;
	lstNdTemp->ptrNextNd = NULL;

		
	return lstNdTemp;
}

RLstNd RdeleteNextNd(RHdrNd HdrNdLst, RLstNd LstNdElem)
{   
	if(RisLstEmpty(HdrNdLst) || LstNdElem == NULL || LstNdElem->ptrNextNd == NULL)	
		return;

	RLstNd LstNdTemp = LstNdElem->ptrNextNd;
    LstNdElem->ptrNextNd = LstNdTemp->ptrNextNd;
	LstNdTemp->ptrNextNd = NULL;	
	HdrNdLst->uiCnt--;

	return LstNdTemp;
}


RNbHdr RinitNbHdr()
{
    RNbHdr nbHdrInfo = (RNbHdr)malloc(sizeof(struct RnbHdr));
    if(nbHdrInfo == NULL)
        return NULL;

    nbHdrInfo->nbhCnt = 0;
    //nbHdrInfo->nbFirst =(NB)malloc(sizeof(struct nb)*size_data) ;
    nbHdrInfo->nbFirst =NULL;
    nbHdrInfo->nbLast = NULL;

    return nbHdrInfo;
}

Boolean RisNbLstEmpty(RNbHdr nbHdrInfo)
{    return(nbHdrInfo == NULL || nbHdrInfo->nbhCnt == 0) ? TRUE : FALSE;
}

void RinsertNeighbors(Data dataTemp, Data dataClstElem, double dist)
{
//NbHdr nbHdrInfo = (NbHdr)malloc(sizeof(NbHdr));
   RNbHdr nbHdrInfo = dataTemp->neighbors;
    RNB newNb;
    if(RisNbLstEmpty(nbHdrInfo))
    {   newNb = (RNB)malloc(sizeof(struct Rnb));

        newNb->n = dataClstElem->iNum;
        newNb->dist = dist;
        newNb->nbNext = NULL;

        nbHdrInfo->nbFirst = newNb;
        nbHdrInfo->nbLast = newNb;   
    }
    else
    {   newNb = (RNB)malloc(sizeof(struct Rnb));
        newNb->n = dataClstElem->iNum;
        newNb->dist = dist;
        newNb->nbNext = NULL;

        nbHdrInfo->nbLast->nbNext = newNb;
        nbHdrInfo->nbLast = newNb;

    }
    dataTemp->neighbors->nbhCnt++;
    return;  
}

void RprintNbhLst(RNbHdr nbHdrInfo,FILE *fglobal)
{
    
   if(RisNbLstEmpty(nbHdrInfo))
        return;
    //printf("++++++++++CALL TO PRINTing THE representative  LIST +++++++++++++++++++\n");
    int iCnt = 0;
    RNB nbTemp = nbHdrInfo->nbFirst;

    while(nbTemp != NULL)
    {   //printf("++++++++++CALL TO PRINT THE LIST__________+++++++++++++++++++\n");
        printf("\nN = %d \t dist = %f", nbTemp->n, nbTemp->dist);
        nbTemp = nbTemp->nbNext;
   }
   return;
}

void RfreeNeighborhood(Data dataTemp)
{
	RNB nb_temp = dataTemp->neighbors->nbFirst,nb_next;
    while(nb_temp!=NULL)
    {
        nb_next=nb_temp->nbNext;
        free(nb_temp);
        nb_temp=nb_next;
    }
    free(dataTemp->neighbors);
	return;

}




