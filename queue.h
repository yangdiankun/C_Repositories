

#ifndef __QUEUE_H
#define __QUEUE_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
	 
	 
	 
/* True is defined as 1 
 */
#ifndef TRUE
#define TRUE     1
#endif

/* False is defined as 0 
 */
#ifndef FALSE
#define FALSE    0
#endif

/* Null is defined as (void *)0
 */
#ifndef NULL
#define NULL    (void *)0
#endif



/* Enumeration of queue status
*/
typedef enum
{
	QUE_UNINITIAL = 0,       /* Uninitialized queue */
	QUE_INITIALED = 0xAA,    /* Initialized queue */
}QueState_t;

/* Structure of queue control block 
*/
typedef struct
{
	unsigned char * pFront;           /* Front address of the queue */
	unsigned char * pRear;            /* Rear address of the queue */
	unsigned char * pBufOrigin;       /* Origin address of queue */
	unsigned int queElementNumber;    /* Number of queue elements */
	unsigned int queElementSize;      /* Size of queue elements */
	unsigned int queElementCnt;       /* Counters for queue elements */
	QueState_t queueStatus;           /* Status of the queue */
}QueueTCB_t;

/* Pointer of queue control block
*/
typedef QueueTCB_t *pQueue_t;



int queueCreate(pQueue_t queue, void * pQueuebuf, unsigned int bufElementNumber, unsigned int bufElementSize);
int queueRemove(pQueue_t queue);
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
