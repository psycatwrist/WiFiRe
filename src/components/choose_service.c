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
        printf("You have chosen WPA-2 Handshake Capture and cracker\n");
        pcap_t *handle = open_interface(interface);

        if (handle == NULL) {
            printf("Failed to open interface.\n");
        } else {
            printf("Interface opened successfully!\n");
            printf("Handle: %p\n", (void *)handle);
        }
    }
}

