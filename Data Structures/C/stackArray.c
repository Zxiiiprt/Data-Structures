#include <stdio.h>

#define MAX_SIZE 256

int stack[MAX_SIZE];
//int top = -1; //Empty stack

void push(int *stack, int top, int val)
{
    if(top == MAX_SIZE-1) //We have a Stack Overflow
    {
        fprintf(stderr, "Error: Stack Overflow\n");
        return;
    }
    top++;
    stack[top] = val;
}

void pop(int *stack, int top)
{
    if(top == -1)
    {
        fprintf(stderr, "Error: Stack is already Empty\n");
        return;
    }
    top--;
}

int peek(int *stack, int top)
{
    return (stack[top]);
}

int main()
{
    return 0;
}
