#pragma once
#include <iostream>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "UdpSocket.hpp"

class UdpSocketImpl : UdpSocket {
    public:
        static constexpr size_t default_max_line = 1024;
        static constexpr size_t default_port = 8075;
        static constexpr auto default_address = INADDR_ANY;

        UdpSocketImpl();
        ~UdpSocketImpl();

        UdpSocketImpl(UdpSocketImpl &) = delete;
        UdpSocketImpl & operator=(UdpSocketImpl &) = delete;

        UdpSocketImpl(
            bool is_server,
            size_t port,
            size_t max_line,
            std::string server_address
        );

        virtual void init() override;

        virtual bool send(
            const std::string msg,
            const std::string address
        ) override;

        virtual std::tuple<std::string&, bool>
        receive(
            std::string &received_msg,
            const std::string address
        ) override;

        virtual bool shutdown() override;

    private:
        bool is_server_{false};
        size_t port_{default_port};
        size_t max_line_{default_max_line};
        struct sockaddr_in server_address_{};
        int sock_fd_;
        char *receive_buffer_;
        SockError error_state_{SockError::NONE};
        std::mutex mutex_;

        virtual void init_client() override;
        virtual void init_server() override;

        virtual bool send_client(
            const std::string msg,
            const std::string address
        ) override;

        virtual bool send_server(
            const std::string msg,
            const std::string address
        ) override;

        virtual bool receive_client(
            std::string &received_msg,
            const std::string address
        ) override;

        virtual bool receive_server(
            std::string &received_msg,
            const std::string address
        ) override;
};
