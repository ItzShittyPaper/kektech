
#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include "libs.h"

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0
#define VECTOR_INIT(vec) kVector vec;\
 kVector_init(&vec)

typedef struct kPair
{
    void* first;
    void* second;
} kPair;

//Store and track the stored data, max amount is 2 billion items roughly.
typedef struct kVectorList
{
    void** items;
    int capacity;
    int total;
} kVectorList;

//structure contain the function pointer
typedef struct kVector
{
    kVectorList vectorList;
    //function pointers
    int (*kVectorTotal)(kVector*);
    int (*kVectorResize)(kVector*, int);
    int (*kVectorAdd)(kVector*, void*);
    int (*kVectorSet)(kVector*, int, void*);
    void* (*kVectorGet)(kVector*, int);
    int (*kVectorDelete)(kVector*, int);
    int (*kVectorFree)(kVector*);
} kVector;

int vectorTotal(kVector* v)
{
    int totalCount = UNDEFINE;
    if (v)
    {
        totalCount = v->vectorList.total;
    }
    return totalCount;
}
int vectorResize(kVector* v, int capacity)
{
    int  status = UNDEFINE;
    if (v)
    {
        void** items = (void**)realloc(v->vectorList.items, sizeof(void*) * capacity);
        if (items)
        {
            v->vectorList.items = items;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }
    return status;
}
int vectorPushBack(kVector* v, void* item)
{
    int status = UNDEFINE;
    if (v)
    {
        if (v->vectorList.capacity == v->vectorList.total)
        {
            status = vectorResize(v, v->vectorList.capacity * 2);
            if (status != UNDEFINE)
            {
                v->vectorList.items[v->vectorList.total++] = item;
            }
        }
        else
        {
            v->vectorList.items[v->vectorList.total++] = item;
            status = SUCCESS;
        }
    }
    return status;
}
int vectorSet(kVector* v, int index, void* item)
{
    int  status = UNDEFINE;
    if (v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
            v->vectorList.items[index] = item;
            status = SUCCESS;
        }
    }
    return status;
}
void* vectorGet(kVector* v, int index)
{
    void* readData = NULL;
    if (v)
    {
        if ((index >= 0) && (index < v->vectorList.total))
        {
            readData = v->vectorList.items[index];
        }
    }
    return readData;
}
int vectorDelete(kVector* v, int index)
{
    int  status = UNDEFINE;
    int i = 0;
    if (v)
    {
        if ((index < 0) || (index >= v->vectorList.total))
            return status;
        v->vectorList.items[index] = NULL;
        for (i = index; (i < v->vectorList.total - 1); ++i)
        {
            v->vectorList.items[i] = v->vectorList.items[i + 1];
            v->vectorList.items[i + 1] = NULL;
        }
        v->vectorList.total--;
        if ((v->vectorList.total > 0) && ((v->vectorList.total) == (v->vectorList.capacity / 4)))
        {
            vectorResize(v, v->vectorList.capacity / 2);
        }
        status = SUCCESS;
    }
    return status;
}
int vectorFree(kVector* v)
{
    int  status = UNDEFINE;
    if (v)
    {
        free(v->vectorList.items);
        v->vectorList.items = NULL;
        status = SUCCESS;
    }
    return status;
}

void kVector_init(kVector* v)
{
    //init function pointers
    v->kVectorTotal = vectorTotal;
    v->kVectorResize = vectorResize;
    v->kVectorAdd = vectorPushBack;
    v->kVectorSet = vectorSet;
    v->kVectorGet = vectorGet;
    v->kVectorFree = vectorFree;
    v->kVectorDelete = vectorDelete;
    //initialize the capacity and allocate the memory
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total = 0;
    v->vectorList.items = (void**)malloc(sizeof(void*) * v->vectorList.capacity);
}

#endif // VECTOR_H_INCLUDED 
