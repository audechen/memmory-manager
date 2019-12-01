#ifndef _YAMM_H_
#define _YAMM_H_

#define USED 1
#define FREE 0

#define ERROR -1
#define OK     0

#define MAX_NODE_NUM 1024

typedef struct __MM_NODE
{
    unsigned long long startAddr;
    unsigned long long blockSize;
    int isUsed;
    struct __MM_NODE* prev;
    struct __MM_NODE* next;
}MM_NODE;

typedef struct __MM_LIST
{
    MM_NODE* head;
    MM_NODE* tail;
}MM_LIST;

#endif