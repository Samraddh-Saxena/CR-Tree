#pragma once
#include <stdio.h>
#include "Def.h"
#include "RTree.h"

int compare_pq(PQElement data1,PQElement data2);
PQueue *pqueue_new(int (*cmp)(PQElement d1,PQElement  d2), size_t capacity);
void pqueue_delete(PQueue *q);
void pqueue_enqueue(PQueue *q, const void *data);
void *pqueue_dequeue(PQueue *q);
void *pqueue_top(PQueue *q);
void pqueue_heapify(PQueue *q, size_t idx);
void freePQueue(PQueue * pq);
void freePQElement(PQElement pqElem);