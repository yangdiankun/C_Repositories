/*
 * Copyright (C), 0000
 * FileName: dlist.c
 * Description: 
 * Change Logs: 
    |Date           |Author       |Notes     |version
    |2012-01-31     |yangdiankun  |XXX       |1.0.0
   Note: Single list
 */
#include "dlist.h"



/*
// Example:
    dlist_head_t head_node;
    dlist_create(&head_node);
*/
int dlist_create(const pdlist_head_t p_head)
{
    if (p_head == NULL)
    {
        return -1;
    }

    p_head->p_next = NULL;
    p_head->p_prev = NULL;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        dlist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data; // Nodes to be added to the linked list
    dlist_add_tail(&head_node, &node_data.node);
*/
int dlist_add_tail(pdlist_head_t p_head, pdlist_node_t p_node)
{
    if ((p_head == NULL) || (p_node == NULL))
    {
        return -1;
    }

    /*               |==> node ==>| 
       |=> head => tail --------->|
       |==========================|
    */
    p_head->p_prev->p_next = p_node;
    p_node->p_next = p_head;
    
    /*               |<== node <==| 
       |<= head <= tail <---------|
       |==========================|
    */
    p_head->p_prev = p_node;
    p_node->p_prev = p_head->p_prev;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        dlist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data; // Nodes to be added to the linked list
    dlist_add_head(&head_node, &node_data.node);
*/
int dlist_add_head(pdlist_head_t p_head, pdlist_node_t p_node)
{
    if ((p_head == NULL) || (p_node == NULL))
    {
        return -1;
    }

    // -->
    p_node->p_next = p_head->p_next;
    p_head->p_next = p_node;
    // <--
    p_head->p_next->p_prev = p_node;
    p_node->p_prev = p_head;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        dlist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data;      // Nodes to be added to the linked list
    node_data_t list_node_data; // Nodes in linked list
    dlist_add_pos(&head_node, &list_node_data.node, &node_data.node);
*/
int dlist_add_pos(pdlist_head_t p_head, pdlist_node_t p_pos, pdlist_node_t p_node)
{
    if ((p_head == NULL) || (p_node == NULL) || (p_pos == NULL))
    {
        return -1;
    }

 //   p_pos->p_prev->p_next = p_node;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        dlist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t list_node_data; // Nodes in linked list
    dlist_node_delete(&head_node, &list_node_data.node);
*/
int dlist_node_delete(pdlist_head_t p_head, pdlist_node_t p_pos)
{
    if ((p_pos == NULL) || (p_pos == NULL))
    {
        return -1;
    }

    p_pos->p_prev = p_pos->p_next;
    p_pos->p_next->p_prev = p_pos->p_prev;
    p_pos->p_next = NULL;
    p_pos->p_prev = NULL;

    return 0;
}

/*
// Example:
    typedef struct _dlist_int{
        dlist_node_t node;
        int data;
    }dlist_int_t;

    int dlist_node_process(void * p_arg, dlist_node_t * p_node)
    {
        if (p_node == NULL)
        {
            return -1;
        }

        printf(printf("%d ", ((dlist_int_t *)p_node)->data));

        return 0;
    }

    int main ()
    {
        dlist_head_t head;
        dlist_int_t node1, node2, node3;

        node1.data = 10;
        node2.data = 20;
        node3.data = 30;

        dlist_create(&head);
        dlist_add_tail(&head, &(node1.node));
        dlist_add_tail(&head, &(node2.node));
        dlist_add_head(&head, &(node3.node));

        dlist_foreach(&head, dlist_node_process, NULL);

        return 0;
    }
*/
int dlist_foreach(pdlist_head_t p_head, dlist_node_process_t pfn_node_process, void *p_arg)
{
    pdlist_node_t p_tmp;
    pdlist_node_t p_end;
    int ret;

    if ((p_head == NULL) || (pfn_node_process == NULL))
    {
        return -1;
    }

    p_tmp = p_head->p_next;
    p_end = p_head->p_prev;
    while (p_tmp != p_end)
    {
        ret = pfn_node_process(NULL, p_tmp);
        if (ret < 0)
        {
            return -1;
        }
        p_tmp = p_tmp->p_next;
    }
    return 0;
}

pdlist_node_t dlist_prev_get(pdlist_head_t p_head, pdlist_node_t p_pos)
{
    return p_pos == NULL ? NULL : p_pos->p_prev;
}

pdlist_node_t dlist_next_get(pdlist_head_t p_head, pdlist_node_t p_pos)
{
    return p_pos == NULL ? NULL : p_pos->p_next;
}

pdlist_node_t dlist_tail_get(pdlist_head_t p_head)
{
    return p_head == NULL ? NULL : p_head->p_prev;
}

pdlist_node_t dlist_begin_get(pdlist_head_t p_head)
{
    return p_head == NULL ? NULL : p_head->p_next;
}

pdlist_node_t dlist_end_get(pdlist_head_t p_head)
{
    return p_head == NULL ? NULL : p_head;
}


