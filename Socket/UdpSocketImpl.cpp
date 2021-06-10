#include <cstring>
#include <string.h>
#include <unistd.h>
#include "UdpSocket.hpp"
#include "UdpSocketImpl.hpp"

UdpSocketImpl::UdpSocketImpl(
        SockConfiguration config,
        size_t port,
        size_t max_line,
        std::string server_address) :
        config_{config},
        port_{port},
        max_line_{max_line}
{
    receive_buffer_ = new char[max_line_];

    server_address_.sin_family = AF_INET; // IPV4
    server_address_.sin_port = htons(port_);
    server_address_.sin_addr.s_addr =
            inet_addr(server_address.c_str());

    init();
}

UdpSocketImpl::UdpSocketImpl() {
    receive_buffer_ = new char[max_line_];

    server_address_.sin_family = AF_INET; // IPV4
    server_address_.sin_port = htons(port_);
    server_address_.sin_addr.s_addr = default_address;

    init();
}

UdpSocketImpl::~UdpSocketImpl() {
    delete receive_buffer_;
}

void UdpSocketImpl::init() {

    if (config_ == SockConfiguration::SERVER) {
        init_server();
    }
    else {
        init_client();
    }
}

void UdpSocketImpl::init_client() {

    if ((sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
          throw SockError::SOCK_CREATION_FAIL;
    }
}

void UdpSocketImpl::init_server() {

    if ((sock_fd_ = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        throw SockError::SOCK_CREATION_FAIL;
    }

    if (bind(sock_fd_, (const sockaddr *)&server_address_,
        sizeof(server_address_)) < 0)
    {
        throw SockError::BIND_FAIL;
    }
}

bool UdpSocketImpl::send(
                        const std::string msg,
                        const std::string address
                    )
{
    std::lock_guard<std::mutex> lock(mutex_);

    bool success = false;

    if (config_ == SockConfiguration::SERVER) {
        success = send_server(msg, address);
    }
    else {
        success = send_client(msg, address);
    }

    return success;
}

bool UdpSocketImpl::send_client(
                        const std::string msg,
                        const std::string address
                    )
{
    std::lock_guard<std::mutex> lock(mutex_);

    ssize_t len = sizeof(server_address_);

    if ((sendto(sock_fd_, (const void *)msg.c_str(),
        msg.size(), 0, (const sockaddr *)&server_address_,
        len)) < 0)
    {
        return false;
    }

    return true;
}

bool UdpSocketImpl::send_server(
                        const std::string msg,
                        const std::string address
                    )
{
    // Todo: implement me
    std::lock_guard<std::mutex> lock(mutex_);
    return false;
}

std::tuple<std::string&, bool>
UdpSocketImpl::receive(std::string &msg, const std::string address) {

    std::lock_guard<std::mutex> lock(mutex_);

    bool success = false;

    if (config_ == SockConfiguration::SERVER) {
        success = receive_server(msg, address);
    }
    else {
        success = receive_client(msg, address);
    }

    return std::make_tuple(std::ref(msg), success);
}

bool UdpSocketImpl::receive_client(
                        std::string &msg,
                        const std::string address
                    )
{
    // Todo: implement me
    std::lock_guard<std::mutex> lock(mutex_);
    return false;
}

bool UdpSocketImpl::receive_server(
                        std::string &msg,
                        const std::string address
                    )
{
    // Todo: implement me
    std::lock_guard<std::mutex> lock(mutex_);
    return false;
}

bool UdpSocketImpl::close() {
    // Todo: implement me
    std::lock_guard<std::mutex> lock(mutex_);
    return false;
}
