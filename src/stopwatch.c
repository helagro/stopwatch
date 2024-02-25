#include "utils.c"
#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_SECS 359999

void printFinal() {
    printf("\033[2K\033[G");   // clears line
    printTime(0);
    printf("\nMinutes: %u\n", sec() / 60);
}

void *stopwatch(void *arg) {
    for (unsigned int i = 0; i < MAX_SECS; i++) {
        printTime(0);

        sleep(SECONDS_SLEEP);
        printf("\033[2K\033[G");   // clears line
    }

    printFinal();
    exit(0);

    return NULL;
}