#include "values.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char _notificationCommand[80];

_Bool getCommand(char *output) {
    char folder[MAX_PATH_LENGTH];
    if (!getFolder(folder)) return 0;

    sprintf(output, "afplay %s/funk.mp3", folder);
    return 1;
}

void playSound() {
    char command[80];
    if (getCommand(command))
        system(command);
    else
        fprintf(stderr, "Error getting command\n");
}

void displayNotification() {
    sprintf(_notificationCommand,
            "osascript -e 'display notification \"Timer finished!\" with title \"Stopwatch\"'");

    system(_notificationCommand);
}
