#include "PQueue.h"

int compare_pq(PQElement data1,PQElement data2)
{
    if(data1->distance < data2->distance)
        return 1;
    else
        return 0;   
}

PQueue *pqueue_new(int (*cmp)(PQElement d1,PQElement  d2),
                   size_t capacity) {
    PQueue *res = NULL;
    NP_CHECK(cmp);
    res = malloc(sizeof(*res));
    NP_CHECK(res);
    res->cmp = cmp;
    /* The inner representation of data inside the queue is an array of void* */
    res->data = malloc(capacity * sizeof(*(res->data)));
    NP_CHECK(res->data);
    res->size = 0;
    res->capacity = capacity;
    return (res);
}

/**
* De-allocates memory for a given Priority Queue structure .
*/
void pqueue_delete(PQueue *q) {
    if (NULL == q) {
        DEBUG("Priority Queue is already NULL. Nothing to free.");
        return;
    }
    free(q->data);
    free(q);
    return;
}

/**
* Adds a new element to the Priority Queue .
*/
void pqueue_enqueue(PQueue *q, const void *data) 
{
    size_t i;
    void *tmp = NULL;
    NP_CHECK(q);
    if (q->size >= q->capacity) {
        DEBUG("Priority Queue is full. Cannot add another element .");
        printf("q->size=%d\t q->capacity=%d data=%d\n",(int)q->size,(int)q->capacity,((Data)data)->iNum);
        return;
    }
    /* Adds element last */
    q->data[q->size] = (void*) data;
    i = q->size;
    q->size++;
    //     printf("q->size : %d\n", q->size);
    /* The new element is swapped with its parent as long as its
    precedence is higher */
    while(i > 0 && q->cmp(q->data[i], q->data[PARENT(i)]) > 0) {
        tmp = q->data[i];
        q->data[i] = q->data[PARENT(i)];
        q->data[PARENT(i)] = tmp;
        i = PARENT(i);
    }

    return;
}

/**
* Returns the element with the biggest priority from the queue .
*/
void *pqueue_dequeue(PQueue *q) 
{
    void *data = NULL;
    NP_CHECK(q);
    if (q->size < 1) {         /* Priority Queue is empty */         DEBUG("Priority Queue underflow . Cannot remove another element .");         return NULL;     }     data = q->data[0];
    q->data[0] = q->data[q->size-1];
    q->size--;
    /* Restore heap property */
    pqueue_heapify(q, 0);
    return (data);
}
void *pqueue_top(PQueue *q) {
    void *data = NULL;
    NP_CHECK(q);
    if (q->size < 1) {         /* Priority Queue is empty */         DEBUG("Priority Queue underflow . Cannot remove another element .");         return NULL;     }   
    data = q->data[0];
    //q->data[0] = q->data[q->size-1];
    //q->size--;
    /* Restore heap property */
    //pqueue_heapify(q, 0);
    return (data);
}
/**
* Turn an "almost-heap" into a heap .
*/
void pqueue_heapify(PQueue *q, size_t idx) 
{
    /* left index, right index, largest */
    void *tmp = NULL;
    size_t l_idx, r_idx, lrg_idx;
    NP_CHECK(q);

    l_idx = LEFT(idx);
    r_idx = RIGHT(idx);

    /* Left child exists, compare left child with its parent */
    if (l_idx < q->size && q->cmp(q->data[l_idx], q->data[idx]) > 0) {
        lrg_idx = l_idx;
    } else {
        lrg_idx = idx;
    }

    /* Right child exists, compare right child with the largest element */
    if (r_idx < q->size && q->cmp(q->data[r_idx], q->data[lrg_idx]) > 0) {
        lrg_idx = r_idx;
    }

    /* At this point largest element was determined */
    if (lrg_idx != idx) {
        /* Swap between the index at the largest element */
        tmp = q->data[lrg_idx];
        q->data[lrg_idx] = q->data[idx];
        q->data[idx] = tmp;
        /* Heapify again */
        pqueue_heapify(q, lrg_idx);
    }

    return;
}

// void print_pqueue(PQueue *pq)
// {
//     PQElement dequeued;

//     while(pq->size!=0)
//     {
//         dequeued = pqueue_dequeue(pq);
//         if (dequeued->nodeType == NODE)
//         {
//             printf("\n");
//             RprintRegion(dequeued->element->nodePtr->ptrParentNd->tnInfo->tdInfo->rgnRect);
//             printf("      and Distance is : %lf", dequeued->distance);

//         }
//         else
//         {
//             printf("\n");
//             printData(dequeued->element->dataElem);
//             printf("      and Distance is : %lf", dequeued->distance);

//         }
//     }
// }

void freePQueue(PQueue * pq)
{
    int i = 0;

    for(i=0;i<pq->size;i++)
    {
        free(((PQElement)(pq->data[i]))->element);
        free(((PQElement)(pq->data[i])));
    }

    pqueue_delete(pq);

    return;
}

void freePQElement(PQElement pqElem)
{
    free(pqElem->element);
    free(pqElem);

    return;
}
