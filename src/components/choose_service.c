#include <stdio.h>
#include <string.h>

#include "components.h"

void list_services() { // listing Services (and accepts the interface string)
    printf("1. WPA-2 Handshake Capture and Cracker");
}

void choose_service(char *interface) {
    list_services();

    char command_buffer[100];
    take_input(command_buffer, sizeof(command_buffer), "Input a digit: ");

    // Working on cases
    if (command_buffer[0] == '1') {
        printf("You have chosen WPA-2 Handshake Capture and cracker");
    }
}

