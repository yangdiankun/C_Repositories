


#include "queue.h"

// not overwritable




int queueCreate(pQueue_t queue, void * pQueuebuf, unsigned int bufElementNumber, unsigned int bufElementSize)
{
	if ((queue == NULL) || (pQueuebuf == NULL))
	{
		return -1;
	}
		
	queue->pFront = (unsigned char *)pQueuebuf;
	queue->pRear = (unsigned char *)pQueuebuf;
	queue->pBufOrigin = (unsigned char *)pQueuebuf;
	
	queue->bufElementNumber = bufElementNumber;
	queue->bufElementCnt = 0;
	queue->bufElementSize = bufElementSize;

	queue->queueStatus = QUE_INITIALED;
	
	return 0;
}

int queueDelete(pQueue_t queue)
{
	if (queue == NULL)
	{
		return -1;
	}
		
	queue->pFront = NULL;
	queue->pRear = NULL;
	queue->pBufOrigin = NULL;
	queue->bufElementNumber = 0;
	queue->bufElementCnt = 0;
	queue->bufElementSize = 0;
	queue->queueStatus = QUE_UNINITIAL;
	
	return 0;
}

unsigned char queueIsFull(pQueue_t queue)
{
	return queue->bufElementCnt == queue->bufElementNumber;
}

unsigned char queueIsEmpty(pQueue_t queue)
{
	return queue->bufElementCnt == 0;
}

unsigned int queueCanOut(pQueue_t queue)
{
	return queue->bufElementCnt;
}

unsigned int queueCanIn(pQueue_t queue)
{
	return queue->bufElementNumber - queue->bufElementCnt;
}

int inQueue(pQueue_t queue, void * elementData)
{
	unsigned int i;
	unsigned char *pIn;
	
	if ((queue->queueStatus != QUE_INITIALED) || (queueIsFull(queue)))
	{
		return -1;
	}
	
	queue->bufElementCnt++;
	
	pIn = (unsigned char *)elementData;
	for (i = 0; i < queue->bufElementSize; i++)
	{
		*queue->pRear++ = *pIn++;
	}
	
	if (queue->pRear == (queue->bufElementNumber * queue->bufElementSize + queue->pBufOrigin))
	{
		queue->pRear = queue->pBufOrigin;
	}
	
	return 0;
}

int outQueue(pQueue_t queue, void * elementData)
{
	unsigned int i;
	unsigned char *pOut;
	
	if ((queue->queueStatus != QUE_INITIALED) || (queueIsEmpty(queue)))
	{
		return -1;
	}
	
	queue->bufElementCnt--;
	
	pOut = (unsigned char *)elementData;
	for (i = 0; i < queue->bufElementSize; i++)
	{
		*pOut++ = *queue->pFront++;
	}
	
	if (queue->pFront == (queue->bufElementNumber * queue->bufElementSize + queue->pBufOrigin))
	{
		queue->pFront = queue->pBufOrigin;
	}
	
	return 0;
}









