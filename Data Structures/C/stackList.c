#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *link;
} node_t;

node_t *top = NULL;

void push(int val)
{
    node_t *temp = malloc(sizeof(node_t));
    temp->val = val;
    temp->link = top;
    top = temp;
}

void pop()
{
    if (top == NULL)
    {
        fprintf(stderr, "ERROR: Stack is Empty!\n");
        return;
    }
    node_t *temp = top;
    top = top->link;
    free(temp);
}
