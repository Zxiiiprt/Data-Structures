#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
    struct node *prev;
} node_t;

void init(node_t **head, node_t **tail, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        exit(1);
        return;
    }
    new_node->val = val;
    new_node->prev = NULL;
    new_node->next = NULL;
    
    *head = new_node;
    *tail = new_node;
}

void insert_beginning(node_t **head, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        fprintf(stderr, "Failed to malloc\n");
        exit(1);
        return;
    }
    
    new_node->val = val;
    new_node->prev = NULL;
    new_node->next = *head;
    if(*head != NULL)
    {
        (*head)->prev = new_node;
    }
    *head = new_node;
}

void deallocate_list(node_t **head, node_t **tail)
{
    if(*head == NULL) return;
    node_t *curr = *head;
    while(curr->next != NULL)
    {
        curr = curr->next;
        free(curr->prev);
    }
    free(curr);
    *head = NULL;
    *tail = NULL;
}

void reverse_list(node_t **head, node_t **tail)
{
    node_t *curr = *head;
    
    while(curr != NULL)
    {
        node_t *next = curr->next;
        curr->next = curr->prev;
        curr = next;
    }
    node_t *temp = *head;
    *head = *tail;
    *tail = temp;
}
