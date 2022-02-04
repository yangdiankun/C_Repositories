
#ifndef __DLIST_H
#define __DLIST_H

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
typedef struct _dlist_node
{
    struct _dlist_node * p_prev;
    struct _dlist_node * p_next;
}dlist_node_t;

/* Pointer of linked list node
 */
typedef dlist_node_t * pdlist_node_t;

/* Linked list data structures of the head node
 */
typedef dlist_node_t dlist_head_t;

/* Head pointer of linked list node
 */
typedef dlist_node_t * pdlist_head_t;

/* Pointer of linked list node processing function
 */
typedef int (* dlist_node_process_t)(void *p_arg, pdlist_node_t p_node);



int dlist_create(const pdlist_head_t p_head);
int dlist_add_tail(pdlist_head_t p_head, pdlist_node_t p_node);
int dlist_add_head(pdlist_head_t p_head, pdlist_node_t p_node);
int dlist_add_pos(pdlist_head_t p_head, pdlist_node_t p_pos, pdlist_node_t p_node);
int dlist_node_delete(pdlist_head_t p_head, pdlist_node_t p_pos);
int dlist_foreach(pdlist_head_t p_head, dlist_node_process_t pfn_node_process, void *p_arg);

pdlist_node_t dlist_prev_get(pdlist_head_t p_head, pdlist_node_t p_pos);
pdlist_node_t dlist_next_get(pdlist_head_t p_head, pdlist_node_t p_pos);
pdlist_node_t dlist_tail_get(pdlist_head_t p_head);
pdlist_node_t dlist_begin_get(pdlist_head_t p_head);
pdlist_node_t dlist_end_get(pdlist_head_t p_head);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DLIST_H */