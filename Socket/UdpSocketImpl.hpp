#include <iostream>
#include <memory>
#include <utility>
#include <assert.h>
#include <cstring>
#include <mutex>
#include "UdpSocket.hpp"

class UdpSocketImpl : UdpSocket {
    public:

        virtual bool bind(int fd, const std::string address) override;
        virtual bool listen(int fd)                          override;
        virtual bool send(int fd, std::string &buffer)       override;
        virtual bool receive(int fd, std::string &buffer)    override;

    private:
        SockConfiguration config_type_{SockConfiguration::ERROR};
        size_t port_;
        std::string address_;
};