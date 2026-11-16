#include <stdio.h>
#include <string.h>

#include "components.h"

void take_input(char *command, size_t size, char *msg) {
    
    printf("\n> %s", msg);
    if (fgets(command, size, stdin) == NULL) {
        command[0] = '\0';
        return;
    }

    command[strcspn(command, "\n")] = '\0';
}