#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define PORT 12345

void processPacket(const char* packet, const sockaddr_in& clientAddress) {
    // Parse the packet and extract necessary information
    std::string request(packet);
    std::cout << "Received packet: " << request << std::endl;

    // Check if it's a discovery message
    if (request == "ID;") {
        // Respond with model ID and serial number
        std::string response = "ID;MODEL=m;SERIAL=n;";

        // Create a UDP socket for sending the response
        int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

        // Send the response back to the client
        sendto(socketDescriptor, response.c_str(), response.length(), 0,
               (struct sockaddr*)&clientAddress, sizeof(clientAddress));

        // Close the socket
        close(socketDescriptor);
    }
    // Check if it's a test start command
    else if (request.find("TEST;CMD=START;DURATION=") == 0) {
        // Extract the duration value
        std::string::size_type durationPos = request.find("DURATION=") + 9;
        std::string::size_type durationEnd = request.find(';', durationPos);
        std::string durationStr = request.substr(durationPos, durationEnd - durationPos);
        int duration = std::stoi(durationStr);

        // Start the test and respond with the appropriate result
        std::string response;
        if (testRunning) {
            response = "TEST;RESULT=error;MSG=Test already running;";
        } else {
            startTest(duration);
            response = "TEST;RESULT=STARTED;";
        }

        // Create a UDP socket for sending the response
        int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

        // Send the response back to the client
        sendto(socketDescriptor, response.c_str(), response.length(), 0,
               (struct sockaddr*)&clientAddress, sizeof(clientAddress));

        // Close the socket
        close(socketDescriptor);
    }
    // Check if it's a test stop command
    else if (request == "TEST;CMD=STOP;") {
        // Stop the test and respond with the appropriate result
        std::string response;
        if (testRunning) {
            stopTest();
            response = "TEST;RESULT=STOPPED;";
        } else {
            response = "TEST;RESULT=error;MSG=No test running;";
        }

        // Create a UDP socket for sending the response
        int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

        // Send the response back to the client
        sendto(socketDescriptor, response.c_str(), response.length(), 0,
               (struct sockaddr*)&clientAddress, sizeof(clientAddress));

        // Close the socket
        close(socketDescriptor);
    }
}

void startTest(int duration) {
    // Implement your test start logic here
    // You can use the "duration" value as the test duration in seconds
    // Start a timer or perform any necessary actions to run the test
}

void stopTest() {
    // Implement your test stop logic here
    // Stop the test and perform any necessary cleanup
}

int main() {
    // Create a UDP socket for receiving packets
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);

    // Set up the server address to bind the socket
   
