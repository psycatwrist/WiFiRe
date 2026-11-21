
#ifndef WIFIRE_COMPONENTS_H
#define WIFIRE_COMPONENTS_H

#include <stddef.h>
#include <pcap/pcap.h>

// Network interface component
int list_interfaces(void);
void take_input(char *command, size_t size, char *msg);
void choose_service(char *interface);
pcap_t *open_interface(const char *interface_name);

#endif
