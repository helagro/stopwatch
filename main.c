#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SECONDS_SLEEP 1
#define MAX_SECS      359999

unsigned int i;

void printPadded(unsigned char num) {
    if (num < 10) {
        putchar('0');
        putchar(num + '0');
    } else {
        printf("%hhu", num);
    }
}

void printTime() {
    printPadded(i / 3600);   // hours
    putchar(':');
    printPadded((i / 60) % 60);   // minutes
    putchar(':');
    printPadded(i % 60);   // seconds
    putchar(' ');
    fflush(stdout);
}

void printFinal() {
    printf("\033[2K\033[G");   // clears line
    printTime();
    printf("\nMinutes: %u\n", i / 60);
}

void *timer(void *arg) {
    for (i = 0; i < MAX_SECS; i++) {
        printTime();

        sleep(SECONDS_SLEEP);
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

    if (pthread_create(&thread, NULL, timer, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    listenForQuit();

    printFinal();
    return 0;
}