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

//Todo: Implement Below member functions

void UdpSocketImpl::init() {}

bool UdpSocketImpl::send(
    std::string_view msg,
    std::string_view address) {return false;}

bool UdpSocketImpl::receive(
    std::string &msg,
    std::string_view address) {return false;}

bool UdpSocketImpl::close() {return false;}

void UdpSocketImpl::init_client() {}

void UdpSocketImpl::init_server() {}
