#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 3;   // buffer size
int x = 0;

// wait operation
void wait(int *s)
{
    (*s)--;
}

// signal operation
void signal(int *s)
{
    (*s)++;
}

// producer
void producer()
{
    wait(&empty);
    wait(&mutex);

    x++;
    printf("Producer has produced: Item %d\n", x);

    signal(&mutex);
    signal(&full);
}

// consumer
void consumer()
{
    wait(&full);
    wait(&mutex);

    printf("Consumer has consumed: Item %d\n", x);
    x--;

    signal(&mutex);
    signal(&empty);
}

int main()
{
    int choice;

    while (1)
    {
        printf("\nEnter 1.Producer 2.Consumer 3.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (empty == 0)
                printf("Buffer is full!\n");
            else
                producer();
            break;

        case 2:
            if (full == 0)
                printf("Buffer is empty!\n");
            else
                consumer();
            break;

        case 3:
            exit(0);
        }
    }
}
