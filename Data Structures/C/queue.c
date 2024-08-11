#include <stdio.h>

#define SIZE 256

int queue[SIZE];
int count = 0;

void insert_queue(int val)
{
    if (count == SIZE)
    {
        // We have reached the end of the queue
        fprintf(stderr, "No more space in the queue\n");
        return;
    }
    queue[count] = val;
    count++;
}

void remove_queue()
{
    if (!count)
    {
        // We have nothing in the queue
        fprintf(stderr, "No elements in the queue\n");
        return;
    }
    for (int i = 0; i < count - 1; i++)
    {
        queue[i] = queue[i + 1];
    }
    count--;
}

int main()
{
    return 0;
}
