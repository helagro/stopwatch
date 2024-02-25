#pragma once

#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

time_t start;

void printPadded(unsigned char num) {
    if (num < 10) {
        putchar('0');
        putchar(num + '0');
    } else {
        printf("%hhu", num);
    }
}

unsigned int sec() {
    return time(NULL) - start;
}

void printTime(unsigned int offset) {
    unsigned int s = abs(((int) offset) - ((int) sec()));

    printPadded(s / 3600);   // hours
    putchar(':');
    printPadded((s / 60) % 60);   // minutes
    putchar(':');
    printPadded(s % 60);   // seconds
    putchar(' ');
    fflush(stdout);
}

time_t sleepTime() {
    return time(NULL) % 1000;
}

char getFolder(char *output) {
    const int s = MAX_PATH_LENGTH;

    if (_NSGetExecutablePath(output, &s) == 0) {
        unsigned int i = 0;

        for (; i < s && output[i] != '\0'; i++)
            ;

        for (; i > 0; i--) {
            if (output[i] == '/') {
                output[i] = '\0';
                return 1;
            }
        }
    }

    fprintf(stderr, "Error getting folder\n");
    return 0;
}
