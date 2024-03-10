#include "notify.c"
#include "utils.c"
#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SECS 359999

unsigned int parseTime(char *time) {
    unsigned int secs = 0;
    char *end, *token = strtok(time, ":");

    while (token != NULL) {
        secs = secs * 60 + strtoul(token, &end, 10);
        if (*end != '\0' && *end != ':') {
            fprintf(stderr, "Invalid time format\n");
            exit(1);
        }

        token = strtok(NULL, ":");
    }

    return secs;
}

void *timer(void *arg) {
    char *time = (char *) arg;
    unsigned long secs = parseTime(time);

    for (unsigned int i = 0; i < secs; i = sec()) {
        printTime(secs);

        sleep(SECONDS_SLEEP);
        printf("\033[2K\033[G");   // clears line
    }

    printTime(secs);
    displayNotification();
    playSound();

    exit(0);

    return NULL;
}