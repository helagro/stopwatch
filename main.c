#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char run = 1;

void printPadded(unsigned long num) {
    if (num < 10) {
        printf("0");
    }

    printf("%lu", num);
}

void printTime(unsigned long seconds) {
    unsigned long hours = seconds / 3600;
    unsigned long minutes = (seconds / 60) % 60;
    unsigned long secs = seconds % 60;

    printPadded(hours);
    printf(":");
    printPadded(minutes);
    printf(":");
    printPadded(secs);
    printf(" ");
    fflush(stdout);
}

void runTimer() {
    unsigned long i;

    for (i = 0; run && i < 216000; i++) {
        printTime(i);

        sleep(1);
        system("clear");
    }

    printTime(i);
    printf("\nMinutes: %lu\n", i / 60);
}

void *listenForQuit(void *arg) {
    char c;

    do {
        c = getchar();
    } while (c != 'q' && c != EOF);

    run = 0;

    return NULL;
}

int main() {
    pthread_t thread;

    if (pthread_create(&thread, NULL, listenForQuit, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    runTimer();

    return 0;
}