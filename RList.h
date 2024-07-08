#ifndef __LIST_H
#define __List_H
#include <stdio.h>
#include "Def.h"

RHdrNd RinitHdrNd();
RLstNd RinitLstNd(RTreeNode tnInfo);
void RinsertLstElem(RHdrNd HdrNdLst, RTreeNode tnInfo);
void RinsertLstNd(RHdrNd HdrNdLst, RLstNd LstNdElem);
Boolean RisLstEmpty(RHdrNd HdrNdLst);
RLstNd RdeleteLstElem(RHdrNd HdrNdLst, RTreeNode tnInfo);
RLstNd RdeleteLstFirst(RHdrNd HdrNdLst);
RLstNd RdeleteNextNd(RHdrNd HdrNdLst, RLstNd LstNdElem);
RNbHdr RinitNbHdr();
Boolean RisNbLstEmpty(RNbHdr nbHdrInfo);
void RinsertNeighbors(Data dataTemp, Data dataClstElem, double dist);
void RprintNbhLst(RNbHdr nbHdrInfo,FILE *fglobal);
void RfreeNeighborhood(Data dataTemp);

#endif
