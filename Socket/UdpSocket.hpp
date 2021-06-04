/**
*   UDP Socket Interface allows either client or server configuration
*   To support TCP and UDP
*
*   Author: Andrew Burger
*/

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <assert.h>
#include <cstring>
#include <mutex>

enum class SockConfiguration {SERVER, CLIENT, ERROR};

class UdpSocket {
    public:
        virtual ~UdpSocket() = default;

        /**
        *   @return true if successful
        */
        virtual bool bind() = 0;

        /**
        *   @return true if successful
        */
        virtual bool listen() = 0;

        /**
        *   @return true if successful
        */
        virtual bool sendto() = 0;

        /**
        *   @return true if successful
        */
        virtual bool recvfrom() = 0;

        /**
        *   @return true if successful
        */
        virtual bool close() = 0;

    private:
};