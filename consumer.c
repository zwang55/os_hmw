#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <time.h>

#define SHARED_MEMORY "/shared_memory"
#define SEM_FULL "/sem_full"
#define SEM_EMPTY "/sem_empty"
#define SEM_MUTEX "/sem_mutex"

int *table;

sem_t *full, *empty, *mutex;

int get_item_from_table() {
    sem_wait(full);
    sem_wait(mutex);

    int item = table[0];
    printf("Got item %d from table\n", item);

    sem_post(mutex);
    sem_post(empty);

    return item;
}

void consume(int item) {
    printf("Consumed item %d\n", item);
    sleep(1); // Sleep for a second to simulate consumption time
}

int main() {
    srand(time(0) + 1); // seed the random number generator with a slightly different value

    // Initialize shared memory
    int shm_fd = shm_open(SHARED_MEMORY, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(int));
    table = (int *)mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Initialize semaphores
    full = sem_open(SEM_FULL, O_CREAT, 0666, 0);
    empty = sem_open(SEM_EMPTY, O_CREAT, 0666, 2);
    mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);

    while (1) {
        int item = get_item_from_table();
        consume(item);
        sleep(rand() % 3); // Random sleep to simulate variable consumption time
    }

    // Cleanup (this won't be reached, but good to have)
    sem_close(full);
    sem_close(empty);
    sem_close(mutex);
    sem_unlink(SEM_FULL);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_MUTEX);
    shm_unlink(SHARED_MEMORY);
    return 0;
}

