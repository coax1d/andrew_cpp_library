#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static constexpr size_t MAX_LINE = 1024;
static constexpr size_t PORT = 8075;

int main(void) {

    int sock_fd;
    char buffer[MAX_LINE];
    const char *hello_msg = "Hello from client";
    struct sockaddr_in server_address{};

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        // do some error
    }

    server_address.sin_family = AF_INET; // IPV4
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // recv/send messages now
    ssize_t len, n;

    len = sizeof(server_address);

    sendto(sock_fd, (const void *)hello_msg, strlen(hello_msg),
        0, (const sockaddr *)&server_address, len);

    std::cout << "Sent Message to client" << std::endl;

    n = recvfrom(sock_fd, (void *)buffer, MAX_LINE, 0,
        (struct sockaddr *)&server_address, (socklen_t *)&len);

    buffer[n] = '\0';

    std::cout << "Server : " << buffer << std::endl;

    return 0;
}
