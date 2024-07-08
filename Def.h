#ifndef __DEF_H
#define __DEF_H
//#include<cpucyles.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<assert.h>
#include<math.h>


#define DELIM " " //Delimiter in the input file
#define LEFT(x) (2 * (x) + 1)
#define RIGHT(x) (2 * (x) + 2)
#define PARENT(x) ((x-1) / 2)

#define ASSERT(x) assert(x!=NULL)

double EPS;
double EPS1;
int MINPOINTS;
int UNDEFINED;
int DIMENSION;    //value for the number of dimensions
int RMINENTRIES;        //Minimum entries for node in RTree
int RMAXENTRIES;       //Maximum entries for node in RTree

typedef struct data *Data;  // Structure holding the data of each element
//typedef struct dataNd *DataNd;  // Node in the list of data elements
typedef struct dataHdr *DataHdr;// Head Node for the list of data elements
                                //to store neighbours
typedef double *DataPoint;    // type of pointer to data point
typedef double dataPoint;   // type of data point
typedef struct region *Region;  // type of pointer to structure for rectangle

typedef double *Dimension;  //type of pointer to one corner of rectangle
typedef double dimension; //type of corner of rectangle
typedef double *Double; //type of pointer to double
typedef int RecNum;

typedef struct RhdrNd *RHdrNd;  // Head Node for a list of children of RTree
typedef struct RlstNd *RLstNd;

typedef union RtreeData *RTreeData; // type of pointer to Data in tree node
typedef struct RtreeNode *RTreeNode;

typedef struct RnbHdr *RNbHdr;
typedef struct Rnb *RNB;

typedef struct KNNdistnode * KNNDistNode;

// common / generic definitions

typedef enum{
    INTNODE,
  EXTNODE
}NODETYPE;  // used to mark a node of RTree as internal or external

typedef enum{
  FALSE,      // 0
  TRUE      // 1
} Boolean;  

struct data{
  //int timestamp;
  DataPoint iData;  // data point
  //double core_distance;
  //double reachability_distance;
  RecNum iNum;
  //Boolean isProcessed;  
  //Boolean core_tag;
  RNbHdr neighbors;
};

struct dataHdr{     //header for data list
  unsigned int uiCnt;
  Data dataClstElem;
};

struct region{
    Dimension iBottomLeft;  // bottom left corner of rectangle
  Dimension iTopRight;  // top right corner of rectanngle
};

// the defs for R Tree
struct Rnb{
       int n;
       double dist;
       RNB nbNext;
};

struct RnbHdr{
       int nbhCnt;
       RNB nbFirst;
       RNB nbLast;
};

union RtreeData{
    Region rgnRect;   // pointer to rectangle incase of internal node
  Data dataClstElem;  //pointer to a Data in case of external node
};

struct RtreeNode{
    NODETYPE ndType;  //type of tree node (internal or external)
  RTreeData tdInfo;  //pointer to treedata structure
};

struct RhdrNd{     //node in data list
  unsigned int uiCnt; // Number of elements in the list
  RLstNd ptrFirstNd; // First node of the list
  RLstNd ptrParentNd;  // Parent node of the list
};

struct RlstNd{     //node of child list
  RTreeNode tnInfo;  // Data
  RHdrNd ptrChildLst;  // List of child nodes
  RLstNd ptrNextNd;  // Next node in the list
};

struct KNNdistnode{
  Data data;
  double distance;
};

#endif

#ifndef __PQUEUE__H__
#define __PQUEUE__H__

/**
* Debugging macro .
*
* Checks for a NULL pointer, and prints the error message, source file and
* line via 'stderr' .
* If the check fails the program exits with error code (-1) .
*/
#define NP_CHECK(ptr) \
    { \
        if (NULL == (ptr)) { \
            fprintf(stderr, "%s:%d NULL POINTER: %s n", \
                __FILE__, __LINE__, #ptr); \
            exit(-1); \
        } \
    } \

#define DEBUG(msg) fprintf(stderr, "%s:%d %s", __FILE__, __LINE__, (msg))

/**
* Priority Queue Structure
*/
typedef enum {NODE,DATA} PQNODETYPE;

// typedef struct pqIntNode *PQIntNode;
typedef struct pqElement *PQElement;
typedef union pqElementUnion *PQElementUnion;

// struct pqIntNode
// {
//     RhdrNd nodePtr;
//     Region mbr;
// };

union pqElementUnion
{
    RHdrNd nodePtr;
    Data dataElem;
};

struct pqElement
{
    double distance;   
    PQNODETYPE nodeType;
    PQElementUnion element;
};


typedef struct PQueue_s {
    /* The actual size of heap at a certain time */
    size_t size;
    /* The amount of allocated memory for the heap */
    size_t capacity;
    /* An array of (void*), the actual max-heap */
    void **data;
    /* A pointer to a comparator function, used to prioritize elements */
    int (*cmp)(PQElement d1, PQElement d2);
} PQueue;

/** Allocates memory for a new Priority Queue .
Needs a pointer to a comparator function, thus establishing priorities .
*/
// PQueue *pqueue_new(int (*cmp)(PQElement d1,  PQElement d2),
//                    size_t capacity);

// /** De-allocates memory for a given Priority Queue */
// void pqueue_delete(PQueue *q);

// * Add an element inside the Priority Queue 
// void pqueue_enqueue(PQueue *q, const void *PQElement);

// /** Removes the element with the greatest priority from within the Queue */
// void *pqueue_dequeue(PQueue *q); 

#endif