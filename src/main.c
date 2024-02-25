#include "stopwatch.c"
#include "timer.c"
#include "utils.c"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void listenForQuit() {
    char c;

    do {
        c = getchar();
    } while (c != 'q' && c != EOF);
}

int main(int argc, char *argv[]) {
    pthread_t thread;
    time(&start);
    char *time;
    void *(*fun)(void *);

    switch (argc) {
        case 1:
            fun = stopwatch;
            break;
        case 2:
            fun = timer;
            time = argv[1];
            break;
        default:
            fprintf(stderr, "No argument for stopwatch, one argument for timer\n");
            return 1;
    }

    if (pthread_create(&thread, NULL, fun, time)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    listenForQuit();

    printFinal();
    return 0;
}