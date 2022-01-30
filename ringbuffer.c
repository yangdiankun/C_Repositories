


#include "ringbuffer.h"




// not overwritable


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

unsigned char rbIsFull(pRB_t rb)
{
	return rb->bufCounter == rb->bufCapacity;
}

unsigned char rbIsEmpty(pRB_t rb)
{
	return rb->bufCounter == 0;
}

unsigned int rbCanReadBytes(pRB_t rb)
{
	if (rb->rbStatus != RB_INITIALED)
	{
		return 0;
	}
	
	return rb->bufCounter;
}
	
unsigned int rbCanWriteBytes(pRB_t rb)
{
	if (rb->rbStatus != RB_INITIALED)
	{
		return 0;
	}
	
	return rb->bufCapacity - rb->bufCounter;
}

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


