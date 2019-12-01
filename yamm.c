#include <stdlib.h>
#include "yamm.h"

#define DEBUG 1

char* userdata = NULL;
MM_LIST* mmList = NULL;

int yammInit(int size)
{
    int i = 0;
    MM_NODE* mmNode = NULL;

    if (size <= 0) {
#if DEBUG
        printf("yammInit: wrong size(%d)\n", size);
#endif
        return ERROR;
    }
    if (userdata != NULL && mmList != NULL) {
#if DEBUG
        printf("yammInit: system initialization completed\n");
#endif
        return OK;
    }

    if (userdata == NULL) {
        userdata = (char* )malloc(sizeof(char) * size);
        if (userdata == NULL) {
#if DEBUG
            printf("yammInit: user memmory create failed\n");
#endif
            return ERROR;
        }
        memset(userdata, 0, sizeof(char) * size);
    }

    if (mmList == NULL) {
        mmList = malloc(sizeof(MM_LIST));
        if (mmList == NULL) {
#if DEBUG
            printf("yammInit: mm list create failed\n");
#endif
            return ERROR;
        }
        memset(mmList, 0, sizeof(mmList));
        for (i = 0; i < MAX_NODE_NUM; i++) {
            mmNode = malloc(sizeof(MM_NODE));
            if (mmNode == NULL) {
#if DEBUG
            printf("yammInit: manager memmory create failed in node %d\n", i);
#endif
            return ERROR;
            }
            memset(mmNode, 0, sizeof(MM_NODE));
            if (mmList->head != NULL) {
                mmList->head->prev = mmNode;
                mmNode->next = mmList->head;
            }
            mmList->head = mmNode;
        }
    }

    mmList->head->startAddr = userdata;
    mmList->head->blockSize = size;
    mmList->head->isUsed = FREE;
    mmList->tail = mmList->head->next;

    return OK;
}

void* yammAlloc(int size)
{
    void* allocAddr = NULL;
    MM_NODE* mmNode = mmList->head;

    if (size <= 0) {
#if DEBUG
        printf("yammAlloc: wrong size(%d)\n", size);
#endif
        return NULL;
    }
    if (userdata == NULL || mmList == NULL) {
#if DEBUG
        printf("yammAlloc: system not initialized\n");
#endif
    }

    while (mmNode->blockSize != 0) {
        if (mmNode->isUsed == FREE && mmNode->blockSize >= size) {
            mmNode->isUsed = USED;
            allocAddr = (void* )mmNode->startAddr;
            //TODO
        }
        mmNode = mmNode->next;
    }

    return allocAddr;
}

void yammFree(void* ptr)
{
    MM_NODE* mmNode = mmList->head;

    if (ptr == NULL) {
#if DEBUG
        printf("yammFree: can not free NULL\n");
#endif
        return;
    }
    if (userdata == NULL || mmList == NULL) {
#if DEBUG
        printf("yammFree: system not initialized\n");
#endif
        return;
    }

    while(mmNode->startAddr != 0) {
        
    }
}