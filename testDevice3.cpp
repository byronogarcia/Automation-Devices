#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void processPacket(const char* packet, const sockaddr_in& clientAddress) {
    // Parse the packet and extract necessary information
    std::string request(packet);
    std::cout << "Received packet: " << request << std::endl;

    // Implement your logic to handle different packet types and generate responses
    // based on the provided packet descriptions

    // Example: Respond to a discovery message
    if (request == "ID;") {
        std::string response = "ID;MODEL=m;SERIAL=n;";

        // Create a UDP socket for sending the response
        int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

        // Send the response back to the client
        sendto(socketDescriptor, response.c_str(), response.length(), 0,
               (struct sockaddr*)&clientAddress, sizeof(clientAddress));

        // Close the socket
        close(socketDescriptor);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);

    // Create a UDP socket for receiving packets
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    // Set up the server address to bind the socket
    struct sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(port);

    // Bind the socket to the server address
    bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Receive and process packets
    char buffer[BUFFER_SIZE];
    struct sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    while (true) {
        // Receive a packet
        ssize_t receivedBytes = recvfrom(socketDescriptor, buffer, BUFFER_SIZE, 0,
                                         (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (receivedBytes > 0) {
            // Process the received packet
            processPacket(buffer, clientAddress);
        }
    }

    // Close the socket
    close(socketDescriptor);

    return 0;
}
