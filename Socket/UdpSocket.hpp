/**
*   UDP Socket Interface allows either client or server configuration
*   supports IPV4 only.
*
*   Author: Andrew Burger
*/

#pragma once
#include <string>
#include <string_view>
#include <tuple>

enum class SockError {SOCK_CREATION_FAIL, BIND_FAIL, SEND_FAIL, RECEIVE_FAIL};

class UdpSocket {
    public:
        virtual ~UdpSocket() = default;

        /**
        *   @brief  choose between init client or server
        *   @return None
        */
        virtual void init() = 0;

        /**
         * @return None
         */
        virtual void init_client() = 0;

        /**
         * @return None
         */
        virtual void init_server() = 0;

        /**
        *   @brief         send message
        *   @param msg     message to send
        *   @param address address to send messages to
        *   @return        true if successful
        */
        virtual bool send(
            const std::string msg,
            const std::string address
        ) = 0;

        /**
        *   @brief         send message from client to server
        *   @param msg     message to send
        *   @param address address to send messages to
        *   @return        true if successful
        */
        virtual bool send_client(
            const std::string msg,
            const std::string address
        ) = 0;

        /**
        *   @brief         send message from server to client
        *   @param msg     message to send
        *   @param address address to send messages to
        *   @return        true if successful
        */
        virtual bool send_server(
            const std::string msg,
            const std::string address
        ) = 0;

        /**
        *   @brief          receive message
        *   @param  msg     message from socket
        *   @param  address address to receive messages from
        *   @return         std::tuple<std::string&, bool>
        *                   std::string is message from socket
        *                   bool is signaling if the string is valid
        */
        virtual std::tuple<std::string&, bool>
        receive(std::string &received_msg, const std::string address) = 0;

        /**
        *   @brief          receive message as a client
        *   @param  msg     message from socket
        *   @param  address address to receive messages from
        *   @return         true if successful
        */
        virtual bool receive_client(
            std::string &received_msg,
            const std::string address
        ) = 0;

        /**
        *   @brief          receive message as a server
        *   @param  msg     message from socket
        *   @param  address address to receive messages from
        *   @return         true if successful
        */
        virtual bool receive_server(
            std::string &received_msg,
            const std::string address
        ) = 0;

        /**
        *   @brief  close socket
        *   @return true if successful
        */
        virtual bool close() = 0;
};
