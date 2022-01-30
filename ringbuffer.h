

#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

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


typedef enum
{
	RB_UNINITIAL = 0,
	RB_INITIALED = 0xAA,
}rbState_t;

typedef struct
{
	unsigned char * pRead;
	unsigned char * pWrite;
	unsigned char * rbBufOrigin;
	unsigned int bufCounter;
	unsigned int bufCapacity;
	rbState_t rbStatus;
}rbTCB_t;

typedef rbTCB_t * pRB_t;




int rbCreate(pRB_t rb, unsigned char * pRbBuf, unsigned int bufSize);

int rbDelet(pRB_t rb);

int rbReadOneByte(pRB_t rb, unsigned char * pData);

int rbWriteOneByte(pRB_t rb, unsigned char pData);

unsigned int rbCanReadBytes(pRB_t rb);

unsigned int rbCanWriteBytes(pRB_t rb);

unsigned char rbIsFull(pRB_t rb);

unsigned char rbIsEmpty(pRB_t rb);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __RINGBUFFER_H */

