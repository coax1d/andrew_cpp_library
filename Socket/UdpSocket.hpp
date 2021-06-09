/**
*   UDP Socket Interface allows either client or server configuration
*   supports IPV4 only.
*
*   Author: Andrew Burger
*/

#pragma once
#include <string>
#include <string_view>

enum class SockConfiguration {SERVER, CLIENT};

class UdpSocket {
    public:
        virtual ~UdpSocket() = default;

        /**
        *   Description: choose between init client or server
        *   @return None
        */
        virtual void init() = 0;

        /**
        *   Description: send message
        *   @return true if successful
        */
        virtual bool send(std::string_view msg, std::string_view address) = 0;

        /**
        *   Description: recieve message
        *   @return true if successful
        */
        virtual bool receive(std::string &received_msg, std::string_view address) = 0;

        /**
        *   Description: close socket
        *   @return true if successful
        */
        virtual bool close() = 0;

        /**
         * @return None
         */
        virtual void init_client() = 0;

        /**
         * @return None
         */
        virtual void init_server() = 0;
};
