#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

unsigned long i;

void printPadded(unsigned long num) {
    if (num < 10) {
        printf("0");
    }

    printf("%lu", num);
}

void printTime() {
    unsigned long hours = i / 3600;
    unsigned long minutes = (i / 60) % 60;
    unsigned long secs = i % 60;

    printPadded(hours);
    printf(":");
    printPadded(minutes);
    printf(":");
    printPadded(secs);
    printf(" ");
    fflush(stdout);
}

void *runTimer(void *arg) {
    for (i = 0; i < 216000; i++) {
        printTime();

        sleep(1);

        printf("\033[2K\033[G");
    }

    return NULL;
}

void listenForQuit() {
    char c;

    do {
        c = getchar();
    } while (c != 'q' && c != EOF);
}

int main() {
    pthread_t thread;

    if (pthread_create(&thread, NULL, runTimer, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    listenForQuit();

    printf("\033[2K\033[G");
    printTime();
    printf("\nMinutes: %lu\n", i / 60);

    return 0;
}