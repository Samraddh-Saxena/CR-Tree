#ifndef __RTREE_H
#define __RTREE_H
#include <stdio.h>
#include "Def.h"
#include "RList.h"
#include "PQueue.h"
#include "km.h"


void print_vector(double *vector, int vector_size);
void print_observations(double **observations, int observations_size, int vector_size);
void print_clusters(double ***clusters, int k, int observations_size, int vector_size);
int compare_clusters(const int *cluster_map1, const int *cluster_map2, int clusters_size);

double ***km(double **observations, int k, int observations_size, int vector_size);
double *centroid(double **observations, int observations_size, int vector_size);
double *vsum(const double *vector1, const double *vector2, int vector_size);
double *vsub(const double *vector1, const double *vector2, int vector_size);
double innerprod(const double *vector1, const double *vector2, int vector_size);
double norm(const double *vector, int vector_size);

int rand_num(int size);

double **initialize(double **observations, int k, int observations_size, int vector_size);
int *partition(double **observations, double **cs, int k, int observations_size, int vector_size);
double **re_centroids(int *clusters_map, double **observations, int k, int observations_size, int vector_size);
double ***map_clusters(int *clusters_map, double **observations, int k, int observations_size, int vector_size);
double **map_cluster(const int *clusters_map, double **observations, int c, int observations_size, int vector_size);



Region RinitRgnRect(Dimension iBottomLeft, Dimension iTopRight);
void RsetRect(RLstNd lstNd, RTreeNode tnInfo);

RTreeNode RinitExtNd(Data dataClstElem);
RTreeNode RinitIntNd(Dimension iBottomLeft, Dimension iTopRight);

Boolean RexpansionArea(Region rgnRect, RTreeNode tnInfo, Double ptrDMinExp, Region rgnNewRect);
double Rarea(Region rgnRect);

RLstNd RpickChild(RHdrNd ptrChildLst, RTreeNode tnInfo);
void RpickSeeds(RHdrNd ptrChildList, RLstNd *lstNdChildOne, RLstNd *lstNdChildTwo);
void RsplitNode(RLstNd ptrChild);

Boolean RinsertTree(RHdrNd hdrNdTree, RTreeNode tnInfo);
RHdrNd RbuildRTree(DataHdr dataHdrLst);

RHdrNd RcreateRoot(RHdrNd hdrNdTree);

void RprintTree(RHdrNd hdrNdTree);

unsigned int RgetNeighborHood(RHdrNd hdrNdTree, Data dataNdTemp);
double RfindDist(DataPoint iDataOne, DataPoint iDataTwo);
unsigned int RfindRecords(RHdrNd hdrNdTree, Region rgnRect, Data dataNdTemp);

Boolean RisContains(Region rgnRect, DataPoint iData);
Boolean RisOverLap(Region rgnRectOne, Region rgnRectTwo);

void RappendRTree(RHdrNd hdrNdTree, DataHdr dataHdrLst);
void freeRTree(RHdrNd hdrNdTree);


Data RgetOneNN(RHdrNd hdrNdTree, Data dataPoint, DataHdr dataList);
Data * RgetKNN(RHdrNd hdrNdTree, Data dataPoint, DataHdr dataList, int k);
double calculateMinDistance(Data datapoint, Region region);
double calculateDistance(DataPoint iDataOne, DataPoint iDataTwo);
// void tester();
void CRsplitNode(RLstNd ptrChild);
#endif
