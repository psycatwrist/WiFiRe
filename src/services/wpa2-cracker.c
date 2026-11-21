#include <stdio.h>
#include <string.h>

#include "components.h"

int configure_capture_filter(pcap_t *handle) { // Function to apply filters to frames

    struct bpf_program filter; // A structure that holdes compiled BPF filters

    const char *filter_exp =
        "type mgt subtype beacon or type data"; // Epression to be compiled

    if (pcap_compile( // Compiling to BPF (returns 0 on success, -1 otherwise)
            handle,
            &filter,
            filter_exp,
            1,
            PCAP_NETMASK_UNKNOWN
        ) == -1) {

        fprintf(stderr, "Filter compilation failed: %s\n",
                pcap_geterr(handle)); // Getting error by handle

        return 1;
    }

    if (pcap_setfilter(handle, &filter) == -1) { // Applying filter (returns 0 on success, -1 otherwise)

        fprintf(stderr, "Applying filter failed: %s\n",
                pcap_geterr(handle));

        pcap_freecode(&filter); // Used to free allocated memory. The filters still persist
        return 1;
    }

    pcap_freecode(&filter);

    return 0;
}

void packet_handler(
    u_char *user,
    const struct pcap_pkthdr *header,
    const u_char *packet
) {
    static int packet_number = 0;

    packet_number++;

    printf("\n========== PACKET %d ==========\n", packet_number);

    printf("Captured length: %u bytes\n", header->caplen);
    printf("Original length: %u bytes\n", header->len);

    printf("Timestamp: %ld.%06ld\n",
           (long)header->ts.tv_sec,
           (long)header->ts.tv_usec);

    printf("\nRaw packet (hexadecimal):\n");

    for (unsigned int i = 0; i < header->caplen; i++) {

        printf("%02X ", packet[i]);

        if ((i + 1) % 16 == 0)
            printf("\n");
    }

    printf("\n==============================\n");
}


pcap_t *open_interface(const char *interface_name) {
    char errbuf[PCAP_ERRBUF_SIZE];
    
    pcap_t *handle = pcap_create(interface_name, errbuf); // Opening a device which returns a handle

    if (handle == NULL) {
        fprintf(stderr, "Couldn't open handle: %s\n", errbuf);
        return NULL;
    }

    if (pcap_set_snaplen(handle, 65535) != 0 || // Configuring the handle with promiscuous mode, timeout and buffer length to store each packet
        pcap_set_promisc(handle, 1) != 0 ||
        pcap_set_timeout(handle, 1000) != 0) {

        fprintf(stderr, "Could not configure capture: %s\n",
                pcap_geterr(handle));

        pcap_close(handle);
        return NULL;
    }

    int status = pcap_activate(handle); // Activating the handle (returns 0 on success, -1 on failure, >0 for warnings)

    if (status < 0) {
        fprintf(stderr, "Could not activate interface: %s\n",
                pcap_geterr(handle));

        pcap_close(handle);
        return NULL; // Activation failed, return NULL
    }

    if (status > 0) {
        fprintf(stderr, "Warning: %s\n", pcap_geterr(handle));
    }

    if (configure_capture_filter(handle) != 0) { // Applying actual filters
        pcap_close(handle);
        return NULL;
    } else {
        int result = pcap_loop(handle, 10, packet_handler, NULL); // Listening for packets

        if (result == -1) {
            fprintf(stderr, "Error occurred while capturing packets: %s\n",
                    pcap_geterr(handle));
            pcap_close(handle);
            return NULL;
        }
    }

    return handle;
}
