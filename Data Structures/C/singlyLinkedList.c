#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

void insert_head(node_t **head, int value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("ERROR 101: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = *head;
    *head = new_node;
}

void insert_tail(node_t **head, int value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("ERROR 101: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->next = NULL;
    new_node->value = value;
    
    //If this is the first item of the list
    if(*head == NULL)
    {
        *head = new_node;
        return;
    }
    
    //Traverse through the list
    node_t *curr = *head;
    while(curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = new_node;
}

void insert_node(node_t *node, int value)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("ERROR 101: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->value = value;
    new_node->next = node->next;
    node->next = new_node;
}

//This function inserts in a sorted manner
//assuming the list is already sorted
void insert_sorted(node_t **head, int value)
{
    //If the list is empty or if the value is less than head
    if(*head == NULL || (*head)->value >= value)
    {
        insert_head(head, value);
        return;
    }
    
    //Check all other cases
    node_t *curr = *head;
    while(curr->next != NULL)
    {
        if(curr->value < value && curr->next->value >= value)
        {
//            insert_node(curr, value);
//            return;
            break;
        }
        curr = curr->next
    }
    //If the value is higher, it's the tail
    insert_node(curr, value);
}

void delete_node(node_t **head, int value)
{
    //If our list is empty, just return
    if(*head == NULL) return;
    
    //If we're trying to remove head
    if((*head)->value == value)
    {
        node_t *remove = *head;
        *head = (*head)->next;
        free(remove);
        return;
    }
    
    //All other cases
    for(node_t *curr = *head; curr->next != NULL; curr = curr->next)
    {
        if(curr->next->value == value)
        {
            node_t *remove = curr->next;
            curr->next = curr->next->next;
            free(remove);
            return;
        }
    }
}

void reverse_list(node_t **head)
{
    node_t *prev = NULL;
    node_t *curr = *head;
    
    while(curr != NULL)
    {
        node_t *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

int detect_loop(node_t *head)
{
    node_t *slow = head;
    node_t *fast = head;
    while(slow != NULL && fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast)
        {
            printf("There's a loop in the list\n");
            return 1;
        }
    }
}

int count_elements(node_t *head)
{
    int count = 0;
    for(node_t *curr = head; curr != NULL; curr = curr->next)
    {
        count++;
    }
    return count;
}

void deallocate_list(node_t **head)
{
    node_t *curr = *head;
    while(curr != NULL)
    {
        node_t *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

int main()
{
    //Create head node
    node_t *head = NULL;
    //Insert head
    insert_head(&head, 1);
    //Insert at the end of the list
    insert_tail(&head, 2);
    insert_tail(&head, 4);
    insert_tail(&head, 5);
    //Insert in the middle of the list
    insert_node(head->next->next, 3);
    
    //Print list by traversal
    for(node_t *curr = head; curr != NULL; curr = curr->next;)
    {
        printf("%d\n", curr->value);
    }
    
    //Deallocate entire list
    deallocate_list(&head);
    return 0;
}
