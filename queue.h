

#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
	 
	 

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FLASE
#define FLASE    0
#endif

#ifndef NULL
#define NULL    (void *)0
#endif



//
typedef enum
{
	QUE_UNINITIAL = 0,
	QUE_INITIALED = 0xAA,
}QueState_t;

//
typedef struct
{
	unsigned char * pFront;
	unsigned char * pRear;
	unsigned char * pBufOrigin;
	unsigned int bufElementNumber;
	unsigned int bufElementSize;
	unsigned int bufElementCnt;
	QueState_t queueStatus;
}QueueTCB_t;

typedef QueueTCB_t *pQueue_t;



int queueCreate(pQueue_t queue, void * pQueuebuf, unsigned int bufElementNumber, unsigned int bufElementSize);
int queueDelete(pQueue_t queue);
unsigned int queueCanIn(pQueue_t queue);
unsigned int queueCanOut(pQueue_t queue);
int inQueue(pQueue_t queue, void * elementData);
int outQueue(pQueue_t queue, void * elementData);

unsigned char queueIsFull(pQueue_t queue);
unsigned char queueIsEmpty(pQueue_t queue);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __QUEUE_H */
