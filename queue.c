/*
 * Copyright (C), 0000
 * FileName: queue.c
 * Description: 
 * Change Logs: 
    |Date           |Author       |Notes     |version
    |2012-01-31     |yangdiankun  |XXX       |1.0.0
 */
#include "queue.h"

// not overwritable



/*
Example:
struct QueueBuf_t queueBuf[10];
QueueTCB_t queue;
queueCreate(&queue, queueBuf, sizeof(queueBuf) / sizeof(queueBuf[0]), sizeof(queueBuf[0]));
*/
int queueCreate(pQueue_t queue, void * pQueuebuf, unsigned int queElementNumber, unsigned int queElementSize)
{
	if ((queue == NULL) || (pQueuebuf == NULL))
	{
		return -1;
	}
		
	queue->pFront = (unsigned char *)pQueuebuf;
	queue->pRear = (unsigned char *)pQueuebuf;
	queue->pBufOrigin = (unsigned char *)pQueuebuf;
	
	queue->queElementNumber = queElementNumber;
	queue->queElementCnt = 0;
	queue->queElementSize = queElementSize;

	queue->queueStatus = QUE_INITIALED;
	
	return 0;
}

/*
Example:
queueDelete(&queue);
*/
int queueDelete(pQueue_t queue)
{
	if (queue == NULL)
	{
		return -1;
	}
		
	queue->pFront = NULL;
	queue->pRear = NULL;
	queue->pBufOrigin = NULL;
	queue->queElementNumber = 0;
	queue->queElementCnt = 0;
	queue->queElementSize = 0;
	queue->queueStatus = QUE_UNINITIAL;
	
	return 0;
}

/*
Example:
queueIsFull(&queue);
*/
unsigned char queueIsFull(pQueue_t queue)
{
	return queue->queElementCnt == queue->queElementNumber;
}

/*
Example:
queueIsEmpty(&queue);
*/
unsigned char queueIsEmpty(pQueue_t queue)
{
	return queue->queElementCnt == 0;
}

/*
Example:
queueCanOut(&queue);
*/
unsigned int queueCanOut(pQueue_t queue)
{
	return queue->queElementCnt;
}

/*
Example:
queueCanIn(&queue);
*/
unsigned int queueCanIn(pQueue_t queue)
{
	return queue->queElementNumber - queue->queElementCnt;
}

/*
Example:
struct QueueBuf_t inQueueData;
inQueue(&queue, &inQueueData);
*/
int inQueue(pQueue_t queue, const void * elementData)
{
	unsigned int i;
	unsigned char *pIn;
	
	if ((queue->queueStatus != QUE_INITIALED) || (queueIsFull(queue)))
	{
		return -1;
	}
	
	queue->queElementCnt++;
	
	pIn = (unsigned char *)elementData;
	for (i = 0; i < queue->queElementSize; i++)
	{
		*queue->pRear++ = *pIn++;
	}
	
	if (queue->pRear == (queue->queElementNumber * queue->queElementSize + queue->pBufOrigin))
	{
		queue->pRear = queue->pBufOrigin;
	}
	
	return 0;
}

/*
Example:
struct QueueBuf_t outQueueData;
inQueue(&queue, &outQueueData);
*/
int outQueue(pQueue_t queue, void * elementData)
{
	unsigned int i;
	unsigned char *pOut;
	
	if ((queue->queueStatus != QUE_INITIALED) || (queueIsEmpty(queue)))
	{
		return -1;
	}
	
	queue->queElementCnt--;
	
	pOut = (unsigned char *)elementData;
	for (i = 0; i < queue->queElementSize; i++)
	{
		*pOut++ = *queue->pFront++;
	}
	
	if (queue->pFront == (queue->queElementNumber * queue->queElementSize + queue->pBufOrigin))
	{
		queue->pFront = queue->pBufOrigin;
	}
	
	return 0;
}









