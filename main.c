#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int i;

void printPadded(unsigned char num) {
    if (num < 10) putchar('0');

    printf("%hhu", num);
}

void printTime() {
    printPadded(i / 3600);   // hours
    printf(":");
    printPadded((i / 60) % 60);   // minutes
    printf(":");
    printPadded(i % 60);   // seconds
    printf(" ");
    fflush(stdout);
}

void printFinal() {
    printf("\033[2K\033[G");   // clears line
    printTime();
    printf("\nMinutes: %u\n", i / 60);
}

void *runTimer(void *arg) {
    for (i = 0; i < 216000; i++) {
        printTime();

        sleep(0);
        printf("\033[2K\033[G");   // clears line
    }

    printFinal();
    exit(0);

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

    printFinal();

    return 0;
}