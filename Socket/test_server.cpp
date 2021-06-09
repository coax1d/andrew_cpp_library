#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static constexpr size_t MAX_LINE = 1024;
static constexpr size_t PORT = 8075;

int main(void) {

    int sock_fd;
    char buffer[MAX_LINE];
    const char *hello_msg = "Hello from serv";
    struct sockaddr_in server_address{}, client_address{};

    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        // do some error
    }

    server_address.sin_family = AF_INET; // IPV4
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    if (bind(sock_fd, (const sockaddr *)&server_address, sizeof(server_address))
            < 0)
    {
        //do some error
    }

    // recv/send messages now
    ssize_t len, n;

    len = sizeof(client_address);

    n = recvfrom(sock_fd, (void *)buffer, MAX_LINE, 0,
        (struct sockaddr *)&client_address, (socklen_t *)&len);

    buffer[n] = '\0';

    std::cout << "Client : " << buffer << std::endl;

    sendto(sock_fd, (const void *)hello_msg, strlen(hello_msg),
        0, (const sockaddr *)&client_address, len);

    std::cout << "Sent Message to client" << std::endl;

    return 0;
}
