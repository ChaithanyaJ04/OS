#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 100

int total, hungry_count;
int positions[MAX];
sem_t sem;

void* philosopher_one(void* arg) {
    int pos = *(int*)arg;
    printf("P %d is waiting\n", pos);
    sem_wait(&sem);
    printf("P %d is granted to eat\n", pos);
    sleep(1);
    printf("P %d has finished eating\n", pos);
    sem_post(&sem);
    return NULL;
}

void run_scenario(int max_at_a_time) {
    pthread_t threads[MAX];

    sem_init(&sem, 0, max_at_a_time);

    for (int i = 0; i < hungry_count; i++)
        pthread_create(&threads[i], NULL, philosopher_one, &positions[i]);

    for (int i = 0; i < hungry_count; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&sem);
}

int main() {
    printf("Enter the total number of philosophers: ");
    scanf("%d", &total);

    printf("How many are hungry: ");
    scanf("%d", &hungry_count);

    for (int i = 0; i < hungry_count; i++) {
        printf("Enter philosopher %d position (1 to %d): ", i + 1, total);
        scanf("%d", &positions[i]);
    }

    int choice;
    do {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Allow one philosopher to eat at any time\n");
            run_scenario(1);
        } else if (choice == 2) {
            printf("Allow two philosophers to eat at any time\n");
            run_scenario(2);
        } else if (choice == 3) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice.\n");
        }
    } while (choice != 3);

    return 0;
}
