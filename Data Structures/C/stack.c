#include <stdio.h>

#define SIZE 256

int stack[SIZE];
int count = 0;

void push(int val)
{
    if(count == SIZE)
    {
        fprintf(stderr, "No space in the stack\n");
        return;
    }
    stack[count] = val;
    count++;
}

void pop()
{
    if(!count)
    {
        fprintf(stderr, "Stack is empty\n");
        return;
    }
    count--;
}
