#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

//using namespace std;

struct TestDevice {
    std::string model;
    std::string serial;
    int test_duration;
    int status_rate;
    bool test_running;
};

void handleDiscovery(int sockfd, const sockaddr_in& client_addr) {
    std::string response = "ID;MODEL=TestModel;SERIAL=12345;";
    sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

void handleStartTest(int sockfd, const sockaddr_in& client_addr, TestDevice& device, const std::string& message) {
    size_t duration_pos = message.find("DURATION=");
    size_t rate_pos = message.find("RATE=");
    if (duration_pos == std::string::npos || rate_pos == std::string::npos) {
        std::string response = "TEST;RESULT=error;MSG=Invalid command;";
        sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        return;
    }

    int duration = std::stoi(message.substr(duration_pos + 9, rate_pos - (duration_pos + 9)));
    int rate = std::stoi(message.substr(rate_pos + 5));

    device.test_duration = duration;
    device.status_rate = rate;
    device.test_running = true;

    std::string response = "TEST;RESULT=STARTED;";
    sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

void handleStopTest(int sockfd, const sockaddr_in& client_addr, TestDevice& device) {
    if (!device.test_running) {
        std::string response = "TEST;RESULT=error;MSG=No test running;";
        sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        return;
    }

    device.test_running = false;

    std::string response = "TEST;RESULT=STOPPED;";
    sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

void handleStatus(int sockfd, const sockaddr_in& client_addr, TestDevice& device) {
    if (!device.test_running) {
        std::string response = "STATUS;STATE=IDLE;";
        sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
        return;
    }

    int time_ms = (device.test_duration - device.status_rate) * 1000;
    int mv = 0;  // Replace with actual measured millivolts value
    int ma = 0;  // Replace with actual measured milliamps value

    std::string response = "STATUS;TIME=" + std::to_string(time_ms) + ";MV=" + std::to_string(mv) + ";MA=" + std::to_string(ma) + ";";
    sendto(sockfd, response.c_str(), response.length(), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
        return 1;
    }

    int port = std::stoi(argv[1]);

    int sockfd;
    struct sockaddr_in server_addr{}, client_addr{};
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    TestDevice device;
    device.model = "TestModel";
    device.serial = "12345";
    device.test_running = false;

    std::cout << "Test Device Simulator is running on port " << port << std::endl;

    while (true) {
        socklen_t addr_len = sizeof(client_addr);

        ssize_t recv_len = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &addr_len);

        if (recv_len < 0) {
            std::cerr << "Failed to receive data" << std::endl;
            continue;
        }

        buffer[recv_len] = '\0';
        std::string message(buffer);

        if (message == "ID;") {
            handleDiscovery(sockfd, client_addr);
        } else if (message.find("TEST;CMD=START;") == 0) {
            handleStartTest(sockfd, client_addr, device, message);
        } else if (message == "TEST;CMD=STOP;") {
            handleStopTest(sockfd, client_addr, device);
        } else if (message == "STATUS;") {
            handleStatus(sockfd, client_addr, device);
        } else {
            // Unknown message, ignore
        }
    }

    close(sockfd);

    return 0;
}
