#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void processPacket(const char* packet, const sockaddr_in& clientAddress) {
    // Process the received packet
    std::string request(packet);
    std::cout << "Received packet: " << request << std::endl;

    // Implement your logic to handle the received packet
    // ...

    // Prepare the response message
    std::string response;
    if (request == "ID;") {
        // Discovery message
        response = "ID;MODEL=m;SERIAL=n;";
    } else if (request.find("TEST;CMD=START") != std::string::npos) {
        // Test start command
        response = "TEST;RESULT STARTED;";
    } else if (request.find("TEST;CMD=STOP") != std::string::npos) {
        // Test stop command
        response = "TEST;RESULT STOPPED;";
    } else {
        // Unknown message, ignore
        return;
    }

    // Send the response to the client
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    sendto(socketDescriptor, response.c_str(), response.size(), 0,
           (struct sockaddr*)&clientAddress, sizeof(clientAddress));
    close(socketDescriptor);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./device_simulator <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);

    // Create a UDP socket
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // Bind the socket to the specified port
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(socketDescriptor, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    // Listen for incoming packets
    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    while (true) {
        // Receive packet from the client
        ssize_t numBytesReceived = recvfrom(socketDescriptor, buffer, sizeof(buffer), 0,
                                            (struct sockaddr*)&clientAddress, &clientAddressLength);
        if (numBytesReceived <= 0) {
            std::cerr << "Error receiving packet" << std::endl;
            continue;
        }

        // Process the received packet
        processPacket(buffer, clientAddress);
    }

    // Close the socket
    close(socketDescriptor);

    return 0;
}
