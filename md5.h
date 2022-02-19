
#ifndef __MD5_H
#define __MD5_h

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



typedef struct _md5_ctx
{
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];
}md5_ctx_t;


#define F(x, y, z)           ((x & y) | (~x & z))
#define G(x, y, z)           ((x & z) | (y & ~z))
#define H(x, y, z)           (x ^ y ^ z)
#define I(x, y, z)           (y ^ (x | ~z))
#define ROTATE_LEFT(x, n)    ((x << n) | (x >> (32-n)))

#define FF(a, b, c, d, x, s, ac) \
{ \
	a += F(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

#define GG(a, b, c, d, x, s, ac) \
{ \
	a += G(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}
#define HH(a, b, c, d, x, s, ac) \
{ \
	a += H(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}
#define II(a, b, c, d, x, s, ac) \
{ \
	a += I(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}





#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __MD5_H */
