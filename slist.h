
#ifndef __SLIST_H
#define __SLIST_H

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


/* Linked list node data structure
 */
typedef struct _slist_node
{
    struct _slist_node * p_next;
}slist_node_t;

/* Pointer of linked list node
 */
typedef slist_node_t * pslist_node_t;

/* Linked list data structures of the head node
 */
typedef slist_node_t slist_head_t;

/* Head pointer of linked list node
 */
typedef slist_node_t * pslist_head_t;

/* Pointer of linked list node processing function
 */
typedef int (* slist_node_process_t)(void *p_arg, pslist_node_t p_node);




int slist_create(const pslist_head_t p_head);
// int slist_node_initial(const pslist_head_t p_head, pslist_node_t p_node);
int slist_add_tail(const pslist_head_t p_head, pslist_node_t p_node);
int slist_add_head(const pslist_head_t p_head, pslist_node_t p_node);
int slist_add_pos(const pslist_head_t p_head, pslist_node_t p_pos, pslist_node_t p_node);
int slist_node_delete(const pslist_head_t p_head, pslist_node_t p_pos);
int slist_foreach(const pslist_head_t p_head, slist_node_process_t pfn_node_process, void *p_arg);


pslist_node_t slist_prev_get(const pslist_head_t p_head, const pslist_node_t p_pos);
pslist_node_t slist_next_get(const pslist_head_t p_head, const pslist_node_t p_pos);
pslist_node_t slist_begin_get(const pslist_head_t p_head);
pslist_node_t slist_tail_get(const pslist_head_t p_head);
pslist_node_t slist_end_get(const pslist_head_t p_head);




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SLIST_H */