#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *next;
} node_t;

void insert_beginning(node_t **head, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("Error: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->val = val;
    new_node->next = *head;
    *head = new_node;
}

void insert_node(node_t *node, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("Error: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->val = val;
    new_node->next = node->next;
    node->next = new_node;
}

void insert_end(node_t **head, int val)
{
    node_t *new_node = malloc(sizeof(node_t));
    if(new_node == NULL)
    {
        printf("Error: Failed to malloc due to insufficient memory\n");
        exit(1);
    }
    new_node->next = NULL;
    new_node->val = val;

    if(*head == NULL)
    {
        *head = new_node;
        return;
    }
    
    //Note that head is being passed in as a pointer to the address of the node
    //So we have to dereference it first to get to the address of the node
    node_t *curr = *head;
    while(curr->next != NULL) //We use curr->next because we want to have the last element
    {
        curr = curr->next;
    }
    //At this point, curr holds the address of the last node of our list
    //And curr->next points to NULL
    //Therefore, all we have to do is to point the next to our new node
    curr->next = new_node;
}

void insert_sorted(node_t **head, int val)
{
    if(*head == NULL || (*head)->val >= val)
    {
        insert_beginning(head, val);
        return;
    }
    
    node_t *curr = *head;
    while(curr->next != NULL) //Loop until we're at the last element
    {
        if(curr->next->val >= val)
        {
            break;
        }
        curr = curr->next;
    }
    
    insert_node(curr, val);
}

void delete_node(node_t **head, int val)
{
    //If our list is empty, handle the case gracefully
    if(*head == NULL) return;
    
    //If we're trying to remove the head of our list
    if((*head)->val == val)
    {
        node_t *to_remove = *head;
        *head = (*head)->next;
        free(to_remove);
        return;
    }
    
    node_t *curr = *head;
    while(curr->next != NULL)
    {
        if(curr->next->val == val)
        {
            node_t *to_remove = curr->next;
            curr->next = curr->next->next;
            free(to_remove);
            return;
        }
        curr = curr->next;
    }
}

void deallocate_list(node_t **head)
{
    node_t *curr = *head;
    while(curr != Note)
    {
        node_t *temp = curr;
        curr = curr->next;
        free(temp);
    }
    *head = NULL;
}

void reverse_list(node_t **head)
{
    node_t *prev = NULL;
    node_t *curr = *head;
    node_t *next;
    
    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

//Since we're not making any changes to the linked list itself
//We don't need a double pointer to head - we can do just fine with a single pointer
int detect_loop(node_t *head)
{
    node_t *fast = head;
    node_t *slow = head;
    while(slow != NULL && fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return 1;
    }
    return 0;
}

//Again, we don't need a double pointer since we're not modifying the head itself
//but rather just getting some inormation out of our linked list
int count_elements(node_t *head)
{
    int count = 0;
    for(node_t *curr = head; curr != NULL; curr = curr->next)
    {
        count++;
    }
    return count;
}

int main()
{
    node_t root = NULL;
    
    insert_end(&root, 1);
    insert_end(&root, 3);
    insert_end(&root, 4);
    insert_node(root, 2);
    
    node_t curr = head;
    while(curr != NULL)
    {
        printf("%d\n", curr->val);
        curr = curr->next;
    }
    
    deallocate_list(&head);
    
    return 0;
}
