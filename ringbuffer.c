/*
 * Copyright (C), 0000
 * FileName: queue.c
 * Description: 
 * Change Logs: 
    |Date           |Author       |Notes     |version
    |2012-01-31     |yangdiankun  |XXX       |1.0.0
   Note: The buffer is not overwritable
 */
#include "ringbuffer.h"




/*
// Example:
	unsigned char rbBuf[100];
	rbCB_t ringBuffer;
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
// Example:
	rbRemove(&ringBuffer);
*/
int rbRemove(pRB_t rb)
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
// Example:
	rbIsFull(&ringBuffer);
*/
unsigned char rbIsFull(pRB_t rb)
{
	return rb->bufCounter == rb->bufCapacity;
}

/*
// Example:
	rbIsEmpty(&ringBuffer);
*/
unsigned char rbIsEmpty(pRB_t rb)
{
	return rb->bufCounter == 0;
}

/*
// Example:
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
// Example:
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
// Example:
	unsigned char readData;
	rbReadOneByte(&ringBuffer, &readData);
*/	
int rbReadOneByte(pRB_t rb, unsigned char * pData)
{
	if ((rb->rbStatus != RB_INITIALED) || (rbIsEmpty(rb) == TRUE))
	{
		return -1;
	}
	
	*pData = *rb->pRead++;
	rb->bufCounter--;
	
	if (rb->pRead == rb->rbBufOrigin + rb->bufCapacity)
	{
		rb->pRead = rb->rbBufOrigin;
	}
	
	return 0;
}

/*
// Example:
	unsigned char readData[100];
	rbReadMultiBytes(&ringBuffer, &readData[0], 10);
*/	
int rbReadMultiBytes(pRB_t rb, unsigned char * pData, unsigned int dataSize)
{
	unsigned int validDataLen;

	if ((rb->rbStatus != RB_INITIALED) || (rbIsEmpty(rb) == TRUE))
	{
		return -1;
	}

	(dataSize > rb->bufCounter) ? 
	(validDataLen = rb->bufCounter) : (validDataLen = dataSize);

	while (validDataLen--)
	{
		*pData++ = *rb->pRead++;
		rb->bufCounter--;
		if (rb->pRead == rb->rbBufOrigin + rb->bufCapacity)
		{
			rb->pRead = rb->rbBufOrigin;
		}
	}
	return 0;
}

/*
// Example:
	unsigned char writeData;
	rbWriteOneByte(&ringBuffer, writeData);
*/
int rbWriteOneByte(pRB_t rb, unsigned char data)
{
	if ((rb->rbStatus != RB_INITIALED) || (rbIsFull(rb) == TRUE))
	{
		return -1;
	}
	
	*rb->pWrite++ = data;
	rb->bufCounter++;
	
	if (rb->pWrite == rb->rbBufOrigin + rb->bufCapacity)
	{
		rb->pWrite = rb->rbBufOrigin;
	}
	
	return 0;
}

/*
// Example:
	unsigned char writeData[100];
	rbWirteMultiBytes(&ringBuffer, &writeData[0], 10);
*/
int rbWirteMultiBytes(pRB_t rb, const unsigned char * data, unsigned int dataSize)
{
	unsigned int validDataLen;

	if ((rb->rbStatus != RB_INITIALED) || (rbIsFull(rb) == TRUE))
	{
		return -1;
	}

	(dataSize > rb->bufCapacity - rb->bufCounter) ? 
	(validDataLen = rb->bufCapacity - rb->bufCounter) : (validDataLen = dataSize);
	
	while (validDataLen--)
	{
		*rb->pWrite++ = *data++;
		rb->bufCounter++;
		if (rb->pWrite == rb->rbBufOrigin + rb->bufCapacity)
		{
			rb->pWrite = rb->rbBufOrigin;
		}
	}
	return 0;
}


