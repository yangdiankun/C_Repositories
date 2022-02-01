/*
 * Copyright (C), 0000
 * FileName: queue.c
 * Description: 
 * Change Logs: 
    |Date           |Author       |Notes     |version
    |2012-01-31     |yangdiankun  |XXX       |1.0.0
 */
#include "ringbuffer.h"

// not overwritable



/*
Example:
unsigned char rbBuf[10];
rbTCB_t ringBuffer;
rbCreate(&ringBuffer, rbBuf, sizeof(rbBuf));
*/
int rbCreate(pRB_t rb, unsigned char * pRbBuf, unsigned int bufSize)
{
	if ((rb == NULL) || (pRbBuf == NULL))
	{
		return -1;
	}
	
	rb->pRead = pRbBuf;
	rb->pWrite = pRbBuf;
	rb->rbBufOrigin = pRbBuf;
	rb->bufCapacity = bufSize;
	rb->rbStatus = RB_INITIALED;
	
	return 0;
}

/*
Example:
rbDelete(&ringBuffer);
*/
int rbDelete(pRB_t rb)
{
	if (rb == NULL)
	{
		return -1;
	}
	
	rb->pRead = NULL;
	rb->pWrite = NULL;
	rb->rbBufOrigin = NULL;
	rb->bufCapacity = 0;
	rb->rbStatus = RB_UNINITIAL;
	
	return 0;
}

/*
Example:
rbIsFull(&ringBuffer);
*/
unsigned char rbIsFull(pRB_t rb)
{
	return rb->bufCounter == rb->bufCapacity;
}

/*
Example:
rbIsEmpty(&ringBuffer);
*/
unsigned char rbIsEmpty(pRB_t rb)
{
	return rb->bufCounter == 0;
}

/*
Example:
rbCanReadBytes(&ringBuffer);
*/
unsigned int rbCanReadBytes(pRB_t rb)
{
	if (rb->rbStatus != RB_INITIALED)
	{
		return 0;
	}
	
	return rb->bufCounter;
}

/*
Example:
rbCanWriteBytes(&ringBuffer);
*/	
unsigned int rbCanWriteBytes(pRB_t rb)
{
	if (rb->rbStatus != RB_INITIALED)
	{
		return 0;
	}
	
	return rb->bufCapacity - rb->bufCounter;
}

/*
Example:
unsigned char readData;
rbReadOneByte(&ringBuffer, &readData);
*/	
int rbReadOneByte(pRB_t rb, unsigned char * pData)
{
	if ((rb->rbStatus != RB_INITIALED) || (rbIsEmpty(rb) == TRUE))
	{
		return -1;
	}
	
	rb->bufCounter--;
	
	*pData = *rb->pRead++;
	
	if (rb->pRead == rb->rbBufOrigin + rb->bufCapacity)
	{
		rb->pRead = rb->rbBufOrigin;
	}
	
	return 0;
}

/*
Example:
unsigned char writeData;
rbWriteOneByte(&ringBuffer, writeData);
*/
int rbWriteOneByte(pRB_t rb, unsigned char data)
{
	if ((rb->rbStatus != RB_INITIALED) || (rbIsFull(rb) == TRUE))
	{
		return -1;
	}
	
	rb->bufCounter++;
	
	*rb->pWrite++ = data;
	
	if (rb->pWrite == rb->rbBufOrigin + rb->bufCapacity)
	{
		rb->pWrite = rb->rbBufOrigin;
	}
	
	return 0;
}


