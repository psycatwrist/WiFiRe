#include <stdio.h>
#include <string.h>

#include "components.h" // Header files for components

int main(void) {
    list_interfaces(); // Starting and listing avaliable interfaces
    
    char command_buffer[100]; // Declaring command buffer
    take_input(command_buffer, sizeof(command_buffer), "Input the name: "); // Asking for input
    
    choose_service(command_buffer); // Choosing Service

    return 0;
}