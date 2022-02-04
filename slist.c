/*
 * Copyright (C), 0000
 * FileName: slist.c
 * Description: 
 * Change Logs: 
    |Date           |Author       |Notes     |version
    |2012-01-31     |yangdiankun  |XXX       |1.0.0
   Note: Single list
 */
#include "slist.h"




/*
// Example:
    slist_head_t head_node;
    slist_create(&head_node);
*/
int slist_create(const pslist_head_t p_head)
{
    if (p_head == NULL)
    {
        return -1;
    }

    p_head->p_next = NULL;

    return 0;
}

/*
// Nodes must be initialized before use
// Example:
    typdef struct _node_data
    {
        slist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data;
    slist_node_initial(&head_node, &node_data.node);
*/
// int slist_node_initial(const pslist_head_t p_head, pslist_node_t p_node)
// {
//     p_node->p_next = NULL;

//     return 0;
// }


/*
// Example:
    typdef struct _node_data
    {
        slist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data; // Nodes to be added to the linked list
    slist_add_tail(&head_node, &node_data.node);
*/
int slist_add_tail(const pslist_head_t p_head, pslist_node_t p_node)
{
    pslist_node_t p_tmp;

    if (p_node == NULL)
    {
        return -1;
    }

    p_tmp = slist_tail_get(p_head);

    if (p_tmp != NULL)
    {
        p_tmp->p_next = p_node;
        p_node->p_next = NULL;
        return 0;
    }
    return -1;
}

/*
// Example:
    typdef struct _node_data
    {
        slist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data; // Nodes to be added to the linked list
    slist_add_head(&head_node, &node_data.node);
*/
int slist_add_head(const pslist_head_t p_head, pslist_node_t p_node)
{
    if ((p_head == NULL) || (p_node ==NULL))
    {
        return -1;
    }

    p_node->p_next = p_head->p_next;
    p_head->p_next = p_node;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        slist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t node_data;      // Nodes to be added to the linked list
    node_data_t list_node_data; // Nodes in linked list
    slist_add_pos(&head_node, &list_node_data.node, &node_data.node);
*/
int slist_add_pos(const pslist_head_t p_head, pslist_node_t p_pos, pslist_node_t p_node)
{
    if ((p_head == NULL) || (p_pos == NULL) || (p_node == NULL))
    {
        return -1;
    }

    p_node->p_next = p_pos->p_next;
    p_pos->p_next = p_node;

    return 0;
}

/*
// Example:
    typdef struct _node_data
    {
        slist_node_t node;
        int a;
        char b;
    }node_data_t;
    node_data_t list_node_data; // Nodes in linked list
    slist_node_delete(&head_node, &list_node_data.node);
*/
int slist_node_delete(const pslist_head_t p_head, pslist_node_t p_pos)
{
    pslist_node_t p_tmp = slist_prev_get(p_head, p_pos);

    if (p_tmp != NULL)
    {
        p_tmp->p_next = p_pos->p_next;
        p_pos->p_next = NULL;
        return 0;
    }
    return -1;
}

/*
// Example:
    typedef struct _slist_int{
        slist_node_t node;
        int data;
    }slist_int_t;

    int slist_node_process(void * p_arg, slist_node_t * p_node)
    {
        if (p_node == NULL)
        {
            return -1;
        }

        printf(printf("%d ", ((slist_int_t *)p_node)->data));

        return 0;
    }

    int main ()
    {
        slist_head_t head;
        slist_int_t node1, node2, node3;

        node1.data = 10;
        node2.data = 20;
        node3.data = 30;

        slist_create(&head);
        slist_add_tail(&head, &(node1.node));
        slist_add_tail(&head, &(node2.node));
        slist_add_head(&head, &(node3.node));

        slist_foreach(&head, slist_node_process, NULL);

        return 0;
    }
*/
int slist_foreach(const pslist_head_t p_head, slist_node_process_t pfn_node_process, void *p_arg)
{
    pslist_node_t p_tmp;
    int ret;

    if ((p_head == NULL) || (pfn_node_process == NULL))
    {
        return -1;
    }

    p_tmp = p_head->p_next;
    while (p_tmp != NULL)
    {
        ret = pfn_node_process(p_arg, p_tmp);
        if (ret < 0)
        {
            return ret;
        }

        p_tmp = p_tmp->p_next;
    }

    return 0;
}


pslist_node_t slist_prev_get(const pslist_head_t p_head, const pslist_node_t p_pos)
{
    pslist_node_t p_tmp;

    if ((p_head == NULL) || (p_pos == NULL))
    {
        return NULL;
    }

    p_tmp = p_head;
    while ((p_tmp->p_next != NULL) && (p_tmp->p_next != p_pos))
    {
        p_tmp = p_tmp->p_next;
    }

    return p_tmp;
}


pslist_node_t slist_next_get(const pslist_head_t p_head, const pslist_node_t p_pos)
{
    return p_pos == NULL ? NULL : p_pos->p_next;
}


pslist_node_t slist_begin_get(const pslist_head_t p_head)
{
    return slist_next_get(p_head, p_head);
}


pslist_node_t slist_tail_get(const pslist_head_t p_head)
{
    pslist_node_t p_tmp;

    if (p_head == NULL)
    {
        return NULL;
    }

    p_tmp = p_head;
    while (p_tmp->p_next != NULL)
    {
        p_tmp = p_tmp->p_next;
    }

    return p_tmp;
}


pslist_node_t slist_end_get(const pslist_head_t p_head)
{
    return NULL;
}





//git pull origin re_dev:lo_dev
//git push origin lo_dev:re_dev