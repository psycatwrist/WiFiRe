#include <stdio.h>
#include <string.h>
#include <pcap/pcap.h> // pcap header for interface discovery and more

#include "components.h" // Common header file for general components

#define VERSION "alpha"

void start(void) {
    printf("Welcome to WiFiRe version %s\n\n", VERSION);
    printf("Please choose a WiFi interface that supports monitor-mode\n");
}

int list_interfaces(void) {
    start(); // Displaying version information

    pcap_if_t *alldevs; // To store the address of the beginning of the returned Linked-List
    pcap_if_t *dev; // To go through each list item using for loop

    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1) { // pcap_findalldevs attempts to find interfaces and returns -1 if fails
        fprintf(stderr, "Error: %s\n", errbuf);
        return 1; // Returning 1 to OS (Which traditionally represents that the program has been unsucccesful)
    }

    int index = 1;

    for (dev = alldevs; dev != NULL; dev = dev->next) {

        if (!(dev->flags & PCAP_IF_WIRELESS)) { // Passing over interfaces that aren't wireless
            continue;
        }

        printf("(%d) Interface name: %s\n", index, dev->name);

        if (dev->description)
            printf("%s\n", dev->description);

        printf("\n");

        index++;
    }

    pcap_freealldevs(alldevs); // To free memory
    return 0;
}